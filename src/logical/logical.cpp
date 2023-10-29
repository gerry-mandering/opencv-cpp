//
// Created by 김민석 on 2023/10/28.
//

#include "../../opencv.hpp"

void maskAnd(unsigned char **input1, unsigned char **input2, unsigned char **output, int col, int row) {

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            output[i][j] = input1[i][j] & input2[i][j];
        }
    }
}

void maskOr(unsigned char **input1, unsigned char **input2, unsigned char **output, int col, int row) {

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            output[i][j] = input1[i][j] | input2[i][j];
        }
    }
}
