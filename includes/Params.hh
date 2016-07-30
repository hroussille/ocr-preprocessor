#ifndef PARAMS_HH
#define PARAMS_HH

class Params 
{
  public :

  Params();
  ~Params();
 
  unsigned int blur;
  unsigned int threshold;
  unsigned int matrix;
  unsigned int constant;
  unsigned int matchCount;
  unsigned int lineStep;

  double ratio;

  bool revert;
  bool isolate;
  bool deskew;

};

#endif // PARAMS_HH
