//
// Created by 김민석 on 2023/10/28.
//

#include "../../opencv.hpp"

void binary(unsigned char **image, unsigned char **output, int col, int row) {

    double avg = getAverage(image, col, row);

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            image[i][j] > avg ? output[i][j] = 255 : output[i][j] = 0;
        }
    }
}