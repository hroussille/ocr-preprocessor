#include <preprocessor.hh>

using namespace cv;

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
  Mat dtc;
  Mat rst;

  int largest_area = -1;

  Rect bounding_rect;
  Size size(blur, blur);

  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  src = imread(sourcePath);

  if (!src.data)
    return false;

  cvtColor(src, dst, CV_BGR2GRAY);
  GaussianBlur(dst, dst, size, 0);

  adaptiveThreshold(dst, dst, threshold,
      CV_ADAPTIVE_THRESH_MEAN_C,
      CV_THRESH_BINARY, matrix, constant);

  dtc = dst.clone();

  findContours(dtc, contours, hierarchy,
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

  if (largest_area == -1)
    rst = dst;
  else
    rst = dst(bounding_rect);

  return imwrite(destinationPath, rst);
}
