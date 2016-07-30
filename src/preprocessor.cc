#include <preprocessor.hh>

using namespace cv;

void doBlur(Mat & target , unsigned int blur)
{
  Size size(blur , blur);

  if (blur == 0)
    return;

  GaussianBlur(target , target , size , 0);
}

void doThreshold(Mat & target , unsigned int threshold , unsigned int matrix , unsigned int constant)
{
  adaptiveThreshold(target , target , threshold , CV_ADAPTIVE_THRESH_MEAN_C , CV_THRESH_BINARY , matrix , constant);
}

void doIsolate(Mat & target)
{
  Mat tmp = target.clone();
  int largest_area = -1;
  Rect bounding_rect;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  findContours(tmp, contours, hierarchy,
      CV_RETR_TREE,
      CV_CHAIN_APPROX_SIMPLE,
      Point(0, 0));

  for (unsigned int i = 0; i < contours.size(); i++) {
    double a = contourArea(contours[i], false);
    if (a > largest_area) {
      largest_area = a;
      bounding_rect = boundingRect(contours[i]);
    }
  }

  if (largest_area != -1)
    target  = target(bounding_rect);
}

void doRevert(Mat & target)
{
  cv::bitwise_not(target, target);
}

void guard(unsigned int & matrix)
{
  if (matrix < 3)
    matrix = 3;
  else if (matrix % 2 == 0)
    matrix = matrix + 1;
}


bool preprocess(std::string sourcePath, 
                std::string destinationPath ,
                unsigned int blur , 
                unsigned int threshold, 
                unsigned int matrix , 
                unsigned int constant , 
                bool revert , 
                bool isolate)
{
  Mat src;
  Mat dst;

  src = imread(sourcePath);
  if (!src.data)
    return false;

  cvtColor(src, dst, CV_BGR2GRAY);
  guard(matrix);

  if (blur > 0)
    doBlur(dst , blur);

  doThreshold(dst , threshold , matrix , constant);

  if (isolate)
    doIsolate(dst);
  if (revert)
    doRevert(dst);

  return imwrite(destinationPath, dst);
}
