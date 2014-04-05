
CC=clang++
OPTS= -O2 -Wall -std=c++11 -stdlib=libc++ -Wno-deprecated-register -g
INCLUDE_DIRS=-I/Library/Frameworks/SDL2.framework/Headers \
-I/Library/Frameworks/SDL2_image.framework/Headers

LINK_FLAGS=-framework SDL2 -framework OpenGL -framework SDL2_image

HEADERS=triangleMesh.h
OBJECTS=imageTriangulator.o triangleMesh.o

all: imageTriangulator

imageTriangulator: $(HEADERS) $(OBJECTS)
	$(CC) $(OPTS) $(LINK_FLAGS) -o imageTriangulator $(OBJECTS)

%.o: %.cpp
	$(CC) $(OPTS) $(INCLUDE_DIRS) -c  -o $@ $<

clean:
	rm -v *.o imageTriangulator
