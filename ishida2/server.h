#include "Communication.h"
#include "calibration.h"
#include"make3d.h"
#include <string>
#include <omp.h>
#include "timer.h"
int outputImage(unsigned char *, string);
bool isoffline(string calibimg,int pucnum,int i);
bool isonline(Communication *);
make3d Make3d;
camera Cameradata[iNodenum];
int pc2imgs[iNodenum];
int pc2rank[iNodenum];
