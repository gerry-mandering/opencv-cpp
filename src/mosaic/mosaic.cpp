//
// Created by 김민석 on 2023/10/28.
//

#include "../../opencv.hpp"

void mosaic(unsigned char **image, unsigned char **output, int col, int row, int block) {
    int temp, count;
    int x, y;

    for (int i = 0; i < row; i += block) {
        for (int j = 0; j < col; j += block) {
            temp = 0;
            count = 0;
            for (y = 0; y < block; y++) {
                for (x = 0; x < block; x++) {
                    temp += image[i + y][j + x];
                    count++;
                }
            }
            temp /= count;

            for (y = 0; y < block; y++) {
                for (x = 0; x < block; x++) {
                    output[i + y][j + x] = temp;
                }
            }
        }
    }
}
