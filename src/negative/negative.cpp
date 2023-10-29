//
// Created by 김민석 on 2023/10/28.
//

#include "../../opencv.hpp"

void negative(unsigned char **image, unsigned char **output, int col, int row) {

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            output[i][j] = 255 - image[i][j];
        }
    }
}