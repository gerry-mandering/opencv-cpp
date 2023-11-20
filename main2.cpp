#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat getHistogramImage(const Mat &image) {
    // Number of bins
    int histSize = 256;

    // Set the ranges (for B,G,R)
    float range[] = { 0, 256 };
    const float* histRange = { range };

    Mat hist;
    calcHist(&image, 1, 0, Mat(), hist, 1, &histSize, &histRange, true, false);

    // Draw the histogram
    int hist_w = 512;
    int hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);

    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));

    // Normalize the result to [0, histImage.rows]
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    for (int i = 1; i < histSize; i++) {
        line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
             Point(bin_w * i, hist_h - cvRound(hist.at<float>(i))),
             Scalar(255, 0, 0), 2, 8, 0);
    }

    return histImage;
}

void getEqualizeHist(const Mat &src, Mat &dst) {
    // Check if the image is grayscale
    if (src.channels() != 1) {
        cerr << "myEqualizeHist: Source image should be grayscale" << endl;
        return;
    }

    // Initialize histogram array (256 levels)
    int hist[256] = {0};
    int numPixels = src.rows * src.cols;

    // Calculate the histogram
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            hist[(int)src.at<uchar>(y, x)]++;
        }
    }

    // Calculate the cumulative histogram (CDF)
    float cdf[256] = {0};
    cdf[0] = hist[0];
    for (int i = 1; i < 256; i++) {
        cdf[i] = cdf[i - 1] + hist[i];
    }

    // Normalize the CDF
    for (int i = 0; i < 256; i++) {
        cdf[i] = (cdf[i] - cdf[0]) / (numPixels - cdf[0]) * 255;
    }

    // Equalize the image
    dst = src.clone();
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            dst.at<uchar>(y, x) = (uchar)cvRound(cdf[src.at<uchar>(y, x)]);
        }
    }
}

// Function to calculate the histogram
void calcHist(const Mat &image, vector<int> &histogram) {
    histogram.assign(256, 0);
    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            histogram[(int)image.at<uchar>(y, x)]++;
        }
    }
}

// Function to calculate the Cumulative Distribution Function (CDF)
void calcCDF(const vector<int> &histogram, vector<float> &cdf) {
    int sum = 0;
    cdf.assign(256, 0);
    for (int i = 0; i < histogram.size(); i++) {
        sum += histogram[i];
        cdf[i] = sum;
    }
    float cdfMin = cdf[0];
    int total = sum;
    for (int i = 0; i < cdf.size(); i++) {
        cdf[i] = (cdf[i] - cdfMin) / (total - cdfMin);
    }
}

// Function to perform histogram matching
void matchHistograms(const Mat &src, const Mat &ref, Mat &dst) {
    // Calculate histograms and CDFs for source and reference images
    vector<int> histSrc, histRef;
    vector<float> cdfSrc, cdfRef;
    calcHist(src, histSrc);
    calcHist(ref, histRef);
    calcCDF(histSrc, cdfSrc);
    calcCDF(histRef, cdfRef);

    // Create a lookup table to map pixel values
    vector<uchar> lut(256);
    for (int i = 0; i < 256; i++) {
        int j = 0;
        float diff = abs(cdfSrc[i] - cdfRef[0]);
        for (int k = 1; k < 256; k++) {
            float newDiff = abs(cdfSrc[i] - cdfRef[k]);
            if (newDiff < diff) {
                diff = newDiff;
                j = k;
            }
        }
        lut[i] = (uchar)j;
    }

    // Apply the mapping to the source image
    dst = src.clone();
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            dst.at<uchar>(y, x) = lut[src.at<uchar>(y, x)];
        }
    }
}

int main(int argc, char** argv) {
    // Check for valid command line arguments, expecting an input image
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <Input image> <Ref image>" << endl;
        return -1;
    }

    // Load the image
    Mat src = imread(argv[1], IMREAD_GRAYSCALE);
    Mat ref = imread(argv[2], IMREAD_GRAYSCALE);

    // Check for invalid input
    if (src.empty() || ref.empty()) {
        cout << "Could not open or find the image!" << endl;
        return -1;
    }

    // Display the original image
    namedWindow("Original Image", WINDOW_AUTOSIZE);
    imshow("Original Image", src);

    // Display the histogram of the original image
    Mat originalHist = getHistogramImage(src);
    namedWindow("Original Histogram", WINDOW_AUTOSIZE);
    imshow("Original Histogram", originalHist);

    // Display the reference image
    namedWindow("Reference Image", WINDOW_AUTOSIZE);
    imshow("Reference Image", ref);

    // Display the histogram of the reference image
    Mat referenceHist = getHistogramImage(ref);
    namedWindow("Reference Histogram", WINDOW_AUTOSIZE);
    imshow("Reference Histogram", referenceHist);

    // Perform histogram matching
    Mat matched;
    matchHistograms(src, ref, matched);

    // Display the matched image
    namedWindow("Matched Image", WINDOW_AUTOSIZE);
    imshow("Matched Image", matched);

    // Display the histogram of the matched image
    Mat matchedHist = getHistogramImage(matched);
    namedWindow("Matched Histogram", WINDOW_AUTOSIZE);
    imshow("Matched Histogram", matchedHist);

    // Wait until user exits the program
    waitKey(0);

    return 0;
}