//#include <png.hpp>
#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <OpenGL/glu.h>
#include "cppitertools/range.hpp"
using iter::range;

#include "triangleMesh.h"

void drawFrame(SDL_Window* window,
			   const TriangleMesh& triangleMesh);

int main(int argc, char** argv){
  
  if(argc < 2){
	std::cout << "usage: imageTriangulator <input_image>" << std::endl;
	exit(1);
  }

  if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
	std::cout << "couldn't init SDL" << std::endl;
	exit(1);
  }
  
  std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> 
	window{SDL_CreateWindow("3.2", SDL_WINDOWPOS_CENTERED,
							SDL_WINDOWPOS_CENTERED,
							800,800,
							SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN),
	  &SDL_DestroyWindow};
  //automatically destory the window when we're done

  IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
  
  auto deleter = [](SDL_Surface* surf){
	IMG_Quit();
	SDL_FreeSurface(surf);
  };
  std::unique_ptr<SDL_Surface,
				  decltype(deleter)> image{IMG_Load(argv[1]), deleter};

  
  TriangleMesh triangleMesh{image.get()};
  
  SDL_SetWindowSize(window.get(),
					image->w,
					image->h);
  
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  auto context = SDL_GL_CreateContext(window.get());

  //loop
  bool readyToExit = false;
  while(!readyToExit){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
	  switch(event.type){
	  case SDL_KEYDOWN:
		if(event.key.keysym.sym == SDLK_ESCAPE){
		  readyToExit = true;
		}
		break;
	  case SDL_QUIT:
		readyToExit = true;
		break;
	  default:
		; // do nothing
	  }
	}
	
	drawFrame(window.get(), triangleMesh);
	
  }
  
  SDL_GL_DeleteContext(context);
  return 0;
}

void drawFrame(SDL_Window* window,
			   const TriangleMesh& triangleMesh){
  
  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, triangleMesh.image->w,
			 0, triangleMesh.image->h);


  triangleMesh.renderOpenGL();

/*
  glBegin(GL_QUADS);
  for(auto row : range(image->h)){
	for(auto col : range(image->w)){
	  //	  if((row + col) % 2){
	  auto* pix = reinterpret_cast<unsigned char*>(image->pixels) + 
		row*image->pitch + col*image->format->BytesPerPixel;
	  
	  glColor4ubv(pix);
	  
	  glVertex2f(col, row);
	  glVertex2f(col + 1, row);
	  glVertex2f(col + 1, row + 1);
	  glVertex2f(col, row + 1);
	  //	  }
	}
  }
  glEnd();*/

  glFlush();
  SDL_GL_SwapWindow(window);

}
