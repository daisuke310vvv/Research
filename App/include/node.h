#include <stdio.h>
#include <opencv/cv.h>
#include "mpi.h"

/* MPIの通信を行う */
#include "Communication.h"
#include "BallTracking.h"

void node_hello_world();

Communication* nodedata;
