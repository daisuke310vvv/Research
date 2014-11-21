#include <opencv/cv.h>
#include "mpi.h"

/* MPIの通信を行う */
#include "../share/Communication.h"

void hello_world();

Communication* nodedata;
