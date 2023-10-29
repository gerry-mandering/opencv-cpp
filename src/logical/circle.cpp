//
// Created by 김민석 on 2023/10/28.
//

#include "../../opencv.hpp"

unsigned char **circleImage(int col, int row, double diameter) {

    unsigned char **circleImage = allocateImage(col, row);
    double xSquare, ySquare;

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            ySquare = pow(abs(row / 2 - i), 2);
            xSquare = pow(abs(col / 2 - j), 2);

            sqrt(ySquare + xSquare) < diameter ? circleImage[i][j] = 255 : circleImage[i][j] = 0;
        }
    }

    return circleImage;
}