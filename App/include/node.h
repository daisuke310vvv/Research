#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/cvaux.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include "mpi.h"

/* MPIの通信を行う */
#include "Communication.h"
#include "BallTracking.h"

void node_hello_world();

Communication* nodedata;
