BINARY  = application

# Make does not offer a recursive wildcard function, so here's one:
rwildcard=$(strip $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(strip $(call rwildcard,$d/,$2))))
# Find source files (SRCS) for different file endings
SRCS   += $(patsubst ./%,%,$(call rwildcard,./,*.c))

OBJS   += $(patsubst %.c, %.o, $(filter-out application.c,$(SRCS)))

DEVICE      = stm32f769nih6

CFLAGS  += -O0 -ggdb3
#CFLAGS   = -O3 -ggdb3
CFLAGS  += -D_GNU_SOURCE
CFLAGS  += -std=gnu18
LDLIBS   = -lm

# disable gfx_color_t warning
CFLAGS += -Wno-packed-bitfield-compat

# setup malloc for external ram
# see support/newlib_integration
# the first ram-bank is reserved as display memory 
#CFLAGS += -DMALLOC_AREA_START=0xC2000000U -DMALLOC_AREA_SIZE=0x8000000U


include ../../Makefile.include
