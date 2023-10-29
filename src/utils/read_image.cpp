//
// Created by 김민석 on 2023/10/27.
//

#include "../../opencv.hpp"

void readImage(unsigned char **image, int col, int row, char *filename) {

    std::FILE *fp;

    fp = fopen(filename, "rb");
    if (fp == nullptr) {
        std::cout << "Error: fopen() failure" << std::endl;
        exit(0);
    }

    for (int i = 0; i < row; ++i) {
        if (fread(image[i], sizeof(unsigned char), col, fp) != col) {
            std::cout << "Error: fread() failure" << std::endl;
            exit(0);
        }
    }

    fclose(fp);
}