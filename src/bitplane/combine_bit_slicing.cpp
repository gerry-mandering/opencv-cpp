//
// Created by 김민석 on 2023/10/28.
//

#include "../../opencv.hpp"

void combine(unsigned char **image, unsigned char **output, int col, int row, int currentBit) {

    unsigned char mask = 0x01 << (currentBit - 1);

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            output[i][j] += (image[i][j] & mask);
        }
    }
}

void combineBitSlicing(unsigned char **image, unsigned char **output, int col, int row, int bitFrom, int bitTo) {

    unsigned char **temp = allocateImage(col, row);

    for (int currentBit = bitFrom; currentBit <= bitTo; ++currentBit) {
        bitSlicing(image, temp, col, row, currentBit);
        combine(temp, output, col, row, currentBit);
    }
}
