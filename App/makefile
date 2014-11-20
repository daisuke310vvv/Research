CC	:= mpicxx
CFLAGS	:= -02 -Wall `pkg-config --cflags opencv` -fopenmp
CPPFLAGS	:= -I$(GENICAM_ROOT_V2_1)/library/CPP/include \
		   -I$(PYLON_ROOT)/include -DUSE_GIGE
CXXFLAGS	:= -g -O0 -fopenmp
DEST          := /usr/local/bin

#追記
SATO_SERVER_PATH := src/server/
SATO_CLIENT_PATH := src/client/

LDFLAGS	:= -L$(PYLON_ROOT)/lib64 \
		   -L$(PYLON_ROOT)/lib \
		   -L$(GENICAM_ROOT_V2_1)/bin/Linux64_x64 \
		   -L$(GENICAM_ROOT_V2_1)/bin/Linux64_x64/GenApi/Generic \
		   -L$(GENICAM_ROOT_V2_1)/bin/Linux32_i86 \
		   -L$(GENICAM_ROOT_V2_1)/bin/Linux32_i86/GenApi/Generic \
		   -Wl,-E \
		    -L/usr/lib64 `pkg-config --libs opencv` 
#-L/usr/lib64 `pkg-config --libs opencv` tukekuwaeta
		   # -g -fopenmp

LIBS          = -lhighgui -lcv -fopenmp -lpylonbase -lpylonutility
#node(client)側でコンパイルするプログラム群
OBJS          = node.o Communication.o Image.o Images.o timer.o
#server側でコンパイルするプログラム群
OBJS2         = server.o Communication.o Image.o make3d.o camera.o xml.o point.o calibration.o timer.o

PROGRAM	= node
PROGRAM2	= server

all:            $(PROGRAM) $(PROGRAM2)

$(PROGRAM):     $(OBJS)
		$(CC)  $(SATO_SERVER_PATH)$(OBJS) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM)

$(PROGRAM2):    $(OBJS2)
		$(CC) $(SATO_CLIENT_PATH)$(OBJS2) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM2)
				
clean:;         rm -f *.o *~ $(PROGRAM) $(PROGRAM2)

.cpp.o:
		$(CC) $(CFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(LIBS) -c $<
server.h: Communication.h Image.h 
node.h: Communication.h Image.h
node.o: Communication.h Image.h timer.o
server.o: Communication.h Image.h camera.o point.o make3d.o timer.o
calibration.o:  calibration.h
