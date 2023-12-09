TARGET = hello
OBJS = main.o			\
	   graphics.o		\
	   flib.o			\
	   framebuffer.o	\
	   audio.o			\
	   utility.o		\
	   tex.o			\
       mp3utils.o

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS= -lpng -ljpeg -lz -lmad -lm -lpspaudiolib -lSDL_ttf -lfreetype

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = RosettaShard

PSPSDK=$(shell psp-config --pspsdk-path)
PSPBIN = $(PSPSDK)/../bin
CFLAGS += $(shell $(PSPBIN)/sdl-config --cflags)
CXXFLAGS += $(shell $(PSPBIN)/sdl-config --cflags)
LIBS += $(shell $(PSPBIN)/sdl-config --libs)
include $(PSPSDK)/lib/build.mak 
