BINARY  = application

OBJS    = clock.o sdram.o
OBJS   += drivers/otm8009a.o drivers/display.o 
OBJS   += $(patsubst %.c, %.o, $(wildcard support/*.c))

CFLAGS  += -O0 -ggdb3
#CFLAGS   = -O3 -ggdb3
CFLAGS  += -D_GNU_SOURCE
CSTD     = -std=c18
#LDLIBS   = 

DEVICE      = stm32f769nih6


# setup malloc for external ram
# see support/newlib_integration
# the first ram-bank is reserved as display memory 
#CFLAGS += -DMALLOC_AREA_START=0xC2000000U -DMALLOC_AREA_SIZE=0x8000000U


include ../../Makefile.include
