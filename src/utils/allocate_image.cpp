//
// Created by 김민석 on 2023/10/27.
//

#include "../../opencv.hpp"

unsigned char **allocateImage(int col, int row) {

    unsigned char **image;

    image = (unsigned char **) calloc(row, sizeof(unsigned char *));
    if (image == nullptr) {
        std::cout << "Error: calloc() failure" << std::endl;
        exit(0);
    }

    for (int i = 0; i < row; ++i) {
        image[i] = (unsigned char *) calloc(col, sizeof(unsigned char));
        if (image[i] == nullptr) {
            std::cout << "Error: calloc() failure" << std::endl;
            exit(0);
        }
    }

    return image;
}

int **allocateIntImage(int col, int row) {

        int **image;

        image = (int **) calloc(row, sizeof(int *));
        if (image == nullptr) {
            std::cout << "Error: calloc() failure" << std::endl;
            exit(0);
        }

        for (int i = 0; i < row; ++i) {
            image[i] = (int *) calloc(col, sizeof(int));
            if (image[i] == nullptr) {
                std::cout << "Error: calloc() failure" << std::endl;
                exit(0);
            }
        }

        return image;
}