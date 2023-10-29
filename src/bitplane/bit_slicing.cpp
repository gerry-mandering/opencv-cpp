//
// Created by 김민석 on 2023/10/28.
//

#include "../../opencv.hpp"

void bitSlicing(unsigned char **image, unsigned char **output, int col, int row, int bit) {

    unsigned char mask = 0x01 << (bit - 1);

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            (image[i][j] & mask) ? output[i][j] = 255 : output[i][j] = 0;
        }
    }
}