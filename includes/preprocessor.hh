#ifndef PREPROCESSOR_HH
#define PREPROCESSOR_HH

#include <opencv2/opencv.hpp>
#include <Params.hh>

using namespace cv;

bool preprocess(std::string sourcePath , 
                std::string destinationPath ,
                Params params);

double getSkew(Mat src , unsigned int matchCount ,
    double ratio , unsigned int lineStep);

void doBlur(Mat & target , unsigned int blur);

void doThreshold(Mat & target , unsigned int threshold , 
    unsigned int matrix , unsigned int constant);

void doIsole(Mat & target);

void doRevert(Mat & target);

void doRotate(Mat & target , double angle);

void guard(unsigned int & matrix , unsigned int & blur);

#endif // PREPROCESSOR_HH
