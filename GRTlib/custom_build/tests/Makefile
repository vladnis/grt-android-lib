LIB_DIR = -L../libraries
GRT_HEADERS = -I../../GRT
LIBS = -lgrt
PLATFORM = X86
CFLAGS = -g -Wall
CC_X86_64 = g++
AR_X86_64 = ar
CC_ARM = arm-linux-androideabi-g++
CC_X86 = i686-linux-android-g++
AR_ARM = arm-linux-androideabi-ar
AR_X86 = i686-linux-android-ar
AR = ${AR_${PLATFORM}}
CC = ${CC_${PLATFORM}}

all: 1.cpp
	$(CC) 1.cpp -o 1 $(GRT_HEADERS) $(LIBS) $(LIB_DIR) $(CFLAGS)
