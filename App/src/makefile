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
#TARGET				= ../bin/$(shell basename `readlink -f ..`)
TARGET				= ../bin/$(shell basename `readlink -f ..`)
TARGET				= ../bin/$(shell basename `readlink -f ..`)
OBJDIR				= ./obj
ifeq "$(strip $(OBJDIR))" ""
	OBJDIR = .
endif
SOURCES				= $(wildcard *.cpp)
OBJECTS 			= $(addprefix $(OBJDIR)/, $(SOURCES:.cpp=.o))
DEPENDS				= $(OBJECT:+.o=.d)

$(TARGET):	$(OBJECTS) $(LIBS)
			$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o:	%.cpp
				@[ -d $(OBJDIR) ] || mkdir -p $(OBJDIR)
				$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)

clean:
		rm -f $(OBJECTS) $(DEPENDS) $(OBJDIR)
		@rmdir --ignore-fail-on-on-empty `readling -f $(OBJDIR)`

-include $(DEPENDS)
