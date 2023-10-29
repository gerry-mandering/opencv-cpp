//
// Created by 김민석 on 2023/10/28.
//

#include "../../opencv.hpp"

double getAverage(unsigned char **image, int col, int row) {

    double sum, avg;

    sum = 0;

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            sum += image[i][j];
        }
    }

    avg = sum / ((double)row * col);

    std::cout << "Average of Image: " << avg << std::endl;

    return avg;
}