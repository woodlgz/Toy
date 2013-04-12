
CC = gcc
GXX = g++

SOURCE = ./trial.cpp

INCLUDE_PATH = -I/usr/include/ -I/usr/include/SDL

LIRARY_PATH = -L/usr/lib64
LIBS = -lSDL -lSDL_image

TARGET = sdl_trial
DEBUG_PATH = ./Debug
RELEASE_PATH = ./Release

debug:
	mkdir $(DEBUG_PATH)
	$(GXX) $(SOURCE) -o  $(DEBUG_PATH)/$(TARGET) $(INCLUDE_PATH) $(LIBRARY_PATH) $(LIBS)

release:
	mkdir $(RELEASE_PATH)
	$(GXX) $(SOURCE) -o  $(RELEASE_PATH)/$(TARGET) $(INCLUDE_PATH) $(LIBRARY_PATH) $(LIBS)

all:
	make debug
	make release

clean:
	rm -rf $(DEBUG_PATH)
	rm -rf $(RELEASE_PATH)

