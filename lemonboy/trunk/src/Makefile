# A basic Makefile to compile for Gp2x


OPEN2X = /mythtv/media/devel/toolchains/openwiz/arm-openwiz-linux-gnu

CC = $(OPEN2X)/bin/arm-openwiz-linux-gnu-gcc
CXX = $(OPEN2X)/bin/arm-openwiz-linux-gnu-g++
LD = $(CC)
STRIP = $(OPEN2X)/bin/arm-openwiz-linux-gnu-strip

NAME=lemonboy2x
TARGET=../$(NAME).gpe

DEFS = -DLEMONBOY -DGP2X -DGLOBAL_CONFIG_FILE=etc/system.gp2x -DIS_LITTLE_ENDIAN -DGP2X_ASM -DSUPERGB -DWIZLIB

#CFLAGS = -mcpu=arm920t -mtune=arm920 -fsigned-char \
#-O3 -msoft-float -ffast-math -fomit-frame-pointer -fstrict-aliasing \
#-mstructure-size-boundary=32 -fexpensive-optimizations \
#-fweb -frename-registers -falign-functions=16 -falign-loops -falign-labels -falign-jumps \
#-finline -finline-functions -fno-common -fno-builtin \
#-Wunused
#-Wall -Wno-sign-compare -Wunused -Wpointer-arith -Wcast-align -Waggregate-return -Wshadow

INCS =  -I. -I$(OPEN2X)/include

LDFLAGS=$(CFLAGS) -L$(OPEN2X)/lib
LIBS=-lSDL -lpng -lm -lz -lpthread -liconv

# While debugging, CFLAGS should be empty
#CFLAGS=-g -DDEBUG
CFLAGS = -O3 -mcpu=arm926ej-s -ffast-math -fomit-frame-pointer 

include Version

MINIMAL_OBJS = sys/gp2x/squidgehack.o sys/gp2x/gp2x.o sys/wiz/wiz_lib.o sys/wiz/sdlsound.o sys/wiz/uppermem.o sys/wiz/pollux_set.o \
	       sys/gp2x/memcpy.o sys/wiz/sys_cacheflush.o sys/gp2x/memset.o sys/gp2x/upscale_aspect.o sys/wiz/warm.o

OBJS = lcd.o refresh.o lcdc.o palette.o cpu.o mem.o rtc.o hw.o sound.o \
	events.o keytable.o \
	loader.o save.o emu.o main.o \
	rccmds.o rckeys.o rcvars.o rcfile.o exports.o \
	unzip/unzip.o unzip/ioapi.o split.o path.o inflate.o supergb.o \
	gui/menu.o gui/utils.o gui/imaging.o gui/options.o $(MINIMAL_OBJS) \
	sys/scale2x/getopt.o sys/scale2x/pixel.o sys/scale2x/scale2x.o sys/scale2x/scale3x.o sys/scale2x/scalebit.o


MYCXX = $(CXX) $(CFLAGS) $(INCS) $(DEBUG) $(PROFILING) $(DEFS)
MYCC = $(CC) $(CFLAGS) $(INCS) $(DEBUG) $(PROFILING) $(DEFS)
MYAS = $(CC) $(ASFLAGS)

VERSION = `cat $(PWD)/Version | awk '/VERSION =/ {printf("%s", $$3); }'`

########################################################################

minimal: $(TARGET)

$(TARGET): $(OBJS) $(MINIMAL_OBJS)
	$(LD) $(DEBUG) $(LDFLAGS) $(PROFILING) $(OBJS) -o $@ $(LIBS)
#	$(STRIP) $@

main.o: Version

.cpp.o:
	$(MYCXX) -c $< -o $@

.c.o:
	$(MYCC) -c $< -o $@

.S.o:
	$(MYAS) -c $< -o $@

clean:
	rm -f *.o sys/*.o sys/*/*.o unzip/*.o gio/*.o *~ sys/*/*~ sys/*~ gui/*~ unzip/*~

version:
	echo $(VERSION)

