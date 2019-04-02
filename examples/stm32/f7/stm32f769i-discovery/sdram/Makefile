BINARY  = application

OBJS    = clock.o sdram.o board.o
OBJS   += $(patsubst %.c, %.o, $(wildcard support/*.c))

#CFLAGS   = -O0 -ggdb3
CFLAGS   = -O3 -ggdb3 -D_GNU_SOURCE
CSTD     = -std=c18
#LDLIBS   = 

DEVICE   = stm32f769nih6
FP_FLAGS = -mfloat-abi=hard -mfpu=fpv5-d16

include ../../Makefile.include
