#include "opencv.hpp"

int main(int argc, char **argv) {

    if (argc != 4) {
        std::cout << "./executable filename column_size row_size" << std::endl;
        exit(0);
    }

    int col, row;
    char *filename;
    unsigned char **image, **output;

    srand (time(NULL));

    col = atoi(argv[2]);
    row = atoi(argv[3]);
    filename = argv[1];

    image = allocateImage(col, row);
    output = allocateImage(col, row);
    readImage(image, col, row, filename);

//    negative(image, output, col, row);
//    mosaic(image, output, col, row, 8);
//    binary(image, output, col, row);
    gammaCorrection(image, output, col, row, 0.45);
//    bitSlicing(image, output, col, row, 1);
//    combineBitSlicing(image, output, col, row, 7, 8);
//    noise(image, output, col, row);
//
//    int combineCount = 100;
//    combineNoise(image, output, col, row, combineCount);
//
//    double psnr = computePSNR(image, output, col, row);
//    std::cout << "PSNR of " << combineCount << " times combined Noisy Image: " << psnr << std::endl;
//
//    maskAnd(image, circleImage(col, row, 200), output, col, row);
//    maskOr(image, circleImage(col, row, 200), output, col, row);

    cv::Mat cvImg(row, col, CV_8UC(1));

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            cvImg.at<unsigned char>(i, j) = output[i][j];
        }
    }

    std::string outfile = std::string(filename) + "gammaInput.bmp";
    cv::imwrite(outfile, cvImg);

    return 0;
}
