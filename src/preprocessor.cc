#include <preprocessor.hh>

using namespace cv;

void doRotate(Mat& src, double angle)
{
  Mat rotated;
  Point2f pt(src.cols / 2., src.rows / 2.);
  Mat r = getRotationMatrix2D(pt, angle, 1.0);
  warpAffine(src, rotated, r, Size(src.cols, src.rows));
  src = rotated.clone();
}

double getSkew(Mat src, unsigned int matchCount,
    double ratio, unsigned int lineStep)
{

  std::vector<cv::Vec4i> lines;
  cvtColor(src, src, CV_BGR2GRAY);
  Mat img_bw = src > 128;
  Size size = src.size();
  bitwise_not(img_bw, img_bw);
  HoughLinesP(img_bw, lines, 1, CV_PI / 180,
      matchCount, size.width / ratio, lineStep);

  double angle = 0.;
  unsigned nb_lines = lines.size();
  for (unsigned i = 0; i < nb_lines; ++i)
    angle += atan2((double)lines[i][3] - lines[i][1], (double)lines[i][2] - lines[i][0]);
  angle /= nb_lines; // mean angle, in radians.
  return angle * 180 / CV_PI;
}

void doBlur(Mat& target, unsigned int blur)
{
  Size size(blur, blur);

  if (blur == 0)
    return;

  GaussianBlur(target, target, size, 0);
}

void doThreshold(Mat& target, unsigned int threshold, unsigned int matrix, unsigned int constant)
{
  adaptiveThreshold(target, target, threshold, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, matrix, constant);
}

void doIsolate(Mat& target)
{
  Mat tmp = target.clone();
  int largest_area = -1;
  Rect bounding_rect;
  std::vector<std::vector<Point> > contours;
  std::vector<Vec4i> hierarchy;

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
    target = target(bounding_rect);
}

void doRevert(Mat& target)
{
  cv::bitwise_not(target, target);
}

void guard(unsigned int& matrix, unsigned int& blur)
{
  if (matrix < 3)
    matrix = 3;
  else if (matrix % 2 == 0)
    matrix = matrix + 1;

  if (blur > 0 && blur % 2 == 0)
    blur = blur + 1;
}

bool preprocess(std::string sourcePath,
    std::string destinationPath,
    Params params)
{
  Mat src;
  Mat dst;

  src = imread(sourcePath);
  if (!src.data)
    return false;


  if (params.deskew) {
    doRotate(src, getSkew(src, params.matchCount,
                      params.ratio, params.lineStep));
  }

  cvtColor(src, dst, CV_BGR2GRAY);

  guard(params.matrix, params.blur);


  if (params.blur > 0)
    doBlur(dst, params.blur);

  doThreshold(dst, params.threshold, params.matrix, params.constant);

  if (params.isolate)
    doIsolate(dst);
  if (params.revert)
    doRevert(dst);

  return imwrite(destinationPath, dst);
}
