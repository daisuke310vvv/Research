# ----------------------------------------------------------------------- #
# makefile by daisuke sato.(14/11/21)
#
#
# 参考URL: http://urin.github.io/posts/2013/simple-makefile-for-clang/
# ----------------------------------------------------------------------- #
CC					= g++
MPICC				= mpicxx
DEST				= /usr/local/bin
CFLAGS				= -O2 -Wall `pkg-config --cflags opencv` -fopenmp
LDFLAGS				= -L/user/lib64 `pkg-config --libs opencv`				
LIBS				= -lhighgui -lcv
INCLUDE 			= -I../include

OBJDIR				= ./obj
ifeq "$(strip $(OBJDIR))" ""
	OBJDIR = .
endif
SOURCES				= $(wildcard *.cpp)
OBJECTS 			= $(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))
DEPENDS				= $(OBJECTS:.o=.d)


all: ../bin/server ../bin/node

#../bin/server:	./obj/server.o ./obj/Communication.o ./obj/Image.o $(LIBS)
../bin/server:	./obj/server.o ./obj/Communication.o ./obj/Image.o 
				$(CC) -o $@ $^ $(LDFLAGS)
				@echo server実行ファイルを生成しました

#../bin/node:	./obj/node.o ./obj/Communication.o ./obj/Image.o ./obj/BallTracking.o $(LIBS)
../bin/node:	./obj/node.o ./obj/Communication.o ./obj/Image.o ./obj/BallTracking.o
				$(CC) -o $@ $^ $(LDFLAGS)
				@echo node実行ファイルを生成しました


#すべてのファイルをコンパイル
$(OBJDIR)/%.o:	%.cpp
				@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
				$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<
				@echo コンパイル


clean:
		rm -f $(OBJECTS) $(DEPENDS) $(OBJDIR)
#		@rmdir --ignore-fail-on-on-empty `readlink -f $(OBJDIR)`

-include $(DEPENDS)

