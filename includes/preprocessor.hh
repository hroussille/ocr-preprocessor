#ifndef PREPROCESSOR_HH
#define PREPROCESSOR_HH

#include <opencv2/opencv.hpp>

using namespace cv;

bool preprocess(std::string sourcePath , 
                std::string destinationPath ,
                unsigned int blur , 
                unsigned int threshold , 
                unsigned int matrix , 
                unsigned int constant , 
                bool revert , 
                bool isolate);

void doBlur(Mat & target , unsigned int blur);

void doThreshold(Mat & target , unsigned int threshold , 
    unsigned int matrix , unsigned int constant);

void doIsole(Mat & target);

void doRevert(Mat & target);

void guard(unsigned int & matrix);

#endif // PREPROCESSOR_HH
