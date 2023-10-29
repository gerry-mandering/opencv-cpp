//
// Created by 김민석 on 2023/10/28.
//

#include "../../opencv.hpp"

void gammaCorrection(unsigned char **image, unsigned char **output, int col, int row, double gamma) {

    double temp;

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            temp = pow(image[i][j] / 255.0, 1 / gamma);

            if (temp * 255 > 255) {
                output[i][j] = 255;
            } else if (temp * 255 < 0) {
                output[i][j] = 0;
            } else {
                output[i][j] = temp * 255;
            }
        }
    }
}