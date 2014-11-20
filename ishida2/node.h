#include "Communication.h"
#include "Images.h"
#include <omp.h>
#include <opencv/cv.h>
#include <opencv/cvaux.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

bool isnodeonline(Images*);
int procname2cameranum(string temp);
Communication* nodedata;
IplImage *tmp_img;
