
CC=clang++
OPTS= -O2 -Wall -std=c++11 -stdlib=libc++ -Wno-deprecated-register -g
INCLUDE_DIRS=-I./png++-0.2.5 -I/Library/Frameworks/SDL2.framework/Headers \
-I/Library/Frameworks/SDL2_image.framework/Headers

LINK_FLAGS=-lpng -framework SDL2 -framework OpenGL -framework SDL2_image

HEADERS=
OBJECTS=imageTriangulator.o

all: imageTriangulator

imageTriangulator: $(HEADERS) $(OBJECTS)
	$(CC) $(OPTS) $(LINK_FLAGS) -o imageTriangulator $(OBJECTS)

%.o: %.cpp
	$(CC) $(OPTS) $(INCLUDE_DIRS) -c  -o $@ $<

clean:
	rm -v *.o imageTriangulator
