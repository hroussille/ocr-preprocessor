#ifndef PREPROCESSOR_HH
#define PREPROCESSOR_HH

#include <opencv2/opencv.hpp>

bool preprocess(std::string sourcePath , 
                std::string destinationPath ,
                unsigned int blur , 
                unsigned int threshold , 
                unsigned int matrix , 
                unsigned int constant , 
                bool revert , 
                bool isolate);

#endif // PREPROCESSOR_HH
