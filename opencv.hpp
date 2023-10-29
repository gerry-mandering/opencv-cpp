//
// Created by 김민석 on 2023/10/28.
//

#ifndef OPENCV_OPENCV_HPP
#define OPENCV_OPENCV_HPP

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/imgproc.hpp>

// utils
unsigned char **allocateImage(int col, int row);
int **allocateIntImage(int col, int row);
void readImage(unsigned char **image, int col, int row, char *filename);

// negative
void negative(unsigned char **image, unsigned char **output, int col, int row);

// mosaic
void mosaic(unsigned char **image, unsigned char **output, int col, int row, int block);

// binary
double getAverage(unsigned char **image, int col, int row);
void binary(unsigned char **image, unsigned char **output, int col, int row);

// gamma
void gammaCorrection(unsigned char **image, unsigned char **output, int col, int row, double gamma);

// bitplane
void bitSlicing(unsigned char **image, unsigned char **output, int col, int row, int bit);
void combineBitSlicing(unsigned char **image, unsigned char **output, int col, int row, int bitFrom, int bitTo);

// noise
void noise(unsigned char **image, unsigned char **output, int col, int row);
void combineNoise(unsigned char **image, unsigned char **output, int col, int row, int count);
double computePSNR(unsigned char** original, unsigned char** noisy, int col, int row);

// logical
unsigned char **circleImage(int col, int row, double diameter);
void maskAnd(unsigned char **input1, unsigned char **input2, unsigned char **output, int col, int row);
void maskOr(unsigned char **input1, unsigned char **input2, unsigned char **output, int col, int row);

#endif//OPENCV_OPENCV_HPP
