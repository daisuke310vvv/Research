CC					= mpicxx
CFLAGS				= -O2 -Wall `pkg-config --cflags opencv` -fopenmp
DEST				= /usr/local/bin
LDFLAGS				= -L/user/lib64 `pkg-config --libs opencv`				
LIBS				= -lhighgui -lcv

BIN_PATH			= bin/

NODE_OBJS			= node.o
SERVER_OBJS			= server.o

NODE				= node
SERVER				= server

SATO_SERVER_PATH := src/server/
SATO_NODE_PATH := src/client/

all:				$(NODE) $(SERVER)

$(NODE):			$(NODE)
					$(CC) $(SATO_NODE_PATH)$(NODE).cpp $(CFLAGS) $(LDFLAGS) -o $(BIN_PATH)$(NODE)

$(SERVER):			$(SERVER)
					$(CC) $(SATO_SERVER_PATH)$(SERVER).cpp $(CFLAGS) $(LDFLAGS) -o $(BIN_PATH)$(SERVER)

#clean:;				rm -f *.o *~ $(NODE) $(SERVER)

.cpp.o:
					$(CC) $(CFLAGS) $(CXXFLAGS) $(LIBS) -c $<
					$(SATO_SERVER_PATH)server.h
					$(SATO_NODE_PATH)node.h
					$(SATO_NODE_PATH)node.o
					$(SATO_SERVER_PATH)server.o

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
