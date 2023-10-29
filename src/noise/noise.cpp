//
// Created by 김민석 on 2023/10/28.
//

#include "../../opencv.hpp"

double uniform() {
    return ((double) (rand() & RAND_MAX) / RAND_MAX - 0.5);
}

double gaussian()
{
    static int ready = 0;
    static double gstore;
    double v1, v2, r, fac, gaus;

    if (ready == 0) {
        do {
            v1 = 2. * uniform();
            v2 = 2. * uniform();
            r = v1 * v1 + v2 * v2;
        } while (r > 1.0);

        fac = sqrt(-2. * log(r) / r);
        gstore = v1 * fac;
        gaus = v2 * fac;
        ready = 1;

    } else {
        ready = 0;
        gaus = gstore;
    }

    return (gaus);
}

void noise(unsigned char **image, unsigned char **output, int col, int row) {

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            output[i][j] = image[i][j] + (gaussian() * 60);
        }
    }
}

void combineNoise(unsigned char **image, unsigned char **output, int col, int row, int count) {

    int **imageSum = allocateIntImage(col, row);
    unsigned char **temp = allocateImage(col, row);

    for (int i = 0; i < count; ++i) {
        noise(image, temp, col, row);
        for (int j = 0; j < row; ++j) {
            for (int k = 0; k < col; ++k) {
                imageSum[j][k] += temp[j][k];
            }
        }
    }

    int avg;

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            avg = imageSum[i][j] / count;

            if (avg > 255) {
                output[i][j] = 255;
            } else if (avg < 0) {
                output[i][j] = 0;
            } else {
                output[i][j] = avg;
            }
        }
    }
}

double computePSNR(unsigned char** original, unsigned char** noisy, int col, int row) {

    double mse = 0.0;

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            mse += pow((int)(original[i][j]) - (int)(noisy[i][j]), 2);
        }
    }

    mse /= (double)(col * row);

    if (mse == 0) {
        return INFINITY;
    }

    double maxI = 255.0;
    double psnr = 10.0 * log10(maxI * maxI / mse);

    return psnr;
}
