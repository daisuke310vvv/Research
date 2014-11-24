# ----------------------------------------------------------------------- #
# makefile by daisuke sato.(14/11/21)
#
#
# 参考URL: http://urin.github.io/posts/2013/simple-makefile-for-clang/
# ----------------------------------------------------------------------- #
CC					= mpicxx
MPICC				= mpicxx
DEST				= /usr/local/bin
CFLAGS				= -O2 -Wall `pkg-config --cflags opencv` -fopenmp
LDFLAGS				= -L/user/lib64 `pkg-config --libs opencv`				
LIBS				= -lhighgui -lcv
INCLUDE 			= -I../include

TARGET				= ../bin/$(shell basename `readlink -f ..`)
OBJDIR				= ./obj
ifeq "$(strip $(OBJDIR))" ""
	OBJDIR = .
endif
SOURCES				= $(wildcard *.cpp)
OBJECTS 			= $(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))
DEPENDS				= $(OBJECTS:.o=.d)

# $(TARGET):	$(OBJECTS) $(LIBS)
# 				$(CC) -o $@ $^ $(LDFLAGS)

../bin/node:	./obj/node.o ./obj/Communication.o ./obj/Image.o $(LIBS)
				$(CC) -o $@ $^ $(LDFLAGS)
				@echo node実行ファイルを生成しました

../bin/server:	./obj/server.o ./obj/Communication.o ./obj/Image.o $(LIBS)
				$(CC) -o $@ $^ $(LDFLAGS)
				@echo server実行ファイルを生成しました

#すべてのファイルをコンパイル
$(OBJDIR)/%.o:	%.cpp
				@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
				$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<
				@echo コンパイル

all: clean $(TARGET)

clean:
		rm -f $(OBJECTS) $(DEPENDS) $(OBJDIR)
		@rmdir --ignore-fail-on-on-empty `readlink -f $(OBJDIR)`

-include $(DEPENDS)

# # ----------------------------------------------------------------------- #
# # node
# # ----------------------------------------------------------------------- #
# NODE_TARGET			= ../bin/node # nodeの実行ファイル
# OBJDIR				= ./obj
# ifeq "$(strip $(OBJDIR))" ""
# 	OBJDIR = .
# endif
# NODE_SOURCES		= node.cpp Communication.cpp
# NODE_OBJECTS 		= $(addprefix $(OBJDIR)/, $(NODE_SOURCES:.cpp=.o))
# DEPENDS				= $(NODE_OBJECTS:.o=.d)
#
# $(NODE_TARGET):	$(NODE_OBJECTS) $(LIBS)
# 				$(CC) -o $@ $^ $(LDFLAGS)
#
# $(OBJDIR)/%.o:	%.cpp
# 				@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
# 				$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<
#
# all: clean $(NODE_TARGET)
#
# clean:
# 		rm -f $(NODE_OBJECTS) $(DEPENDS) $(OBJDIR)
# 		@rmdir --ignore-fail-on-on-empty `readling -f $(OBJDIR)`
#
# -include $(DEPENDS)
# # ----------------------------------------------------------------------- #
#
# # ----------------------------------------------------------------------- #
# # server
# # ----------------------------------------------------------------------- #
# SERVER_TARGET			= ../bin/server # serverの実行ファイル
# OBJDIR				= ./obj
# ifeq "$(strip $(OBJDIR))" ""
# 	OBJDIR = .
# endif
# SERVER_SOURCES		= server.cpp Communication.cpp
# SERVER_OBJECTS 		= $(addprefix $(OBJDIR)/, $(SERVER_SOURCES:.cpp=.o))
# DEPENDS				= $(SERVER_OBJECTS:.o=.d)
#
# $(SERVER_TARGET):	$(SERVER_OBJECTS) $(LIBS)
# 					$(CC) -o $@ $^ $(LDFLAGS)
#
# $(OBJDIR)/%.o:	%.cpp
# 				@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
# 				$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<
#
# all: clean $(SERVER_TARGET)
#
# clean:
# 	rm -f $(SERVER_OBJECTS) $(DEPENDS) $(OBJDIR)
# 	@rmdir --ignore-fail-on-on-empty `readling -f $(OBJDIR)`
#
# -include $(DEPENDS)
# # ----------------------------------------------------------------------- #
