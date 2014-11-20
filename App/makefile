CC					= mpicxx
CFLAGS				= -02 -Wall `pkg-config --cflags opencv` -fopenmp
DEST				= /usr/local/bin
LDFLAGS				= -L/user/lib64 `pkg-config --libs opencv`				
LIBS				= -lhighgui -lcv

NODE_OBJS			= node.o
SERVER_OBJS			= server.o

NODE				= node
SERVER				= server

SATO_SERVER_PATH := src/server/
SATO_CLIENT_PATH := src/client/

all:				$(NODE) $(SERVER)

$(NODE_OBJS):		$(NODE_OBJS)
					$(CC) $(NODE_OBJS) $(CFLAGS) $(LDFLAGS) -o $(NODE)

$(SERVER_OBJS):		$(SERVER_OBJS)
					$(CC) $(SERVER_OBJS) $(CFLAGS) $(LDFLAGS) -o $(SERVER)

#clean:;				rm -f *.o *~ $(NODE) $(SERVER)

.cpp.o:
					$(CC) $(CFLAGS) $(CXXFLAGS) $(LIBS) -c $<
					server.h
					node.h
					node.o
					server.h

#
# # CPPFLAGS	:= -I$(GENICAM_ROOT_V2_1)/library/CPP/include \
# # 		   -I$(PYLON_ROOT)/include -DUSE_GIGE
# # CXXFLAGS	:= -g -O0 -fopenmp
#
# #追記
# SATO_SERVER_PATH := src/server/
# SATO_CLIENT_PATH := src/client/
#
# # LDFLAGS	:= -L$(PYLON_ROOT)/lib64 \
# # 		   -L$(PYLON_ROOT)/lib \
# # 		   -L$(GENICAM_ROOT_V2_1)/bin/Linux64_x64 \
# # 		   -L$(GENICAM_ROOT_V2_1)/bin/Linux64_x64/GenApi/Generic \
# # 		   -L$(GENICAM_ROOT_V2_1)/bin/Linux32_i86 \
# # 		   -L$(GENICAM_ROOT_V2_1)/bin/Linux32_i86/GenApi/Generic \
# # 		   -Wl,-E \
# # 		    -L/usr/lib64 `pkg-config --libs opencv` 
# # #-L/usr/lib64 `pkg-config --libs opencv` tukekuwaeta
# # 		   # -g -fopenmp
# \
# #node(client)側でコンパイルするプログラム群
# #OBJS          = node.o Communication.o Image.o Images.o timer.o\
# OBJS          = node.o\
# #server側でコンパイルするプログラム群
# #OBJS2         = server.o Communication.o Image.o make3d.o camera.o xml.o point.o calibration.o timer.o\
# OBJS2         = server.o\
# \
# PROGRAM	= node\
# PROGRAM2	= server\
# \
# all:            $(PROGRAM) $(PROGRAM2)\
# \
# $(PROGRAM):     $(OBJS)\
# 		$(CC)  $(SATO_CLIENT_PATH)$(OBJS) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM)\
# \
# $(PROGRAM2):    $(OBJS2)\
# 		$(CC) $(SATO_SERVER_PATH)$(OBJS2) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM2)\
# 				\
# clean:;         rm -f *.o *~ $(PROGRAM) $(PROGRAM2)\
# \
# .cpp.o:\
# 		$(CC) $(CFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(LIBS) -c $<\
# #server.h: Communication.h Image.h \
# #node.h: Communication.h Image.h\
# #node.o: Communication.h Image.h timer.o\
# #server.o: Communication.h Image.h camera.o point.o make3d.o timer.o\
# #calibration.o:  calibration.h\
