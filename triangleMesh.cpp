#include "triangleMesh.h"
#include "cppitertools/range.hpp"
using iter::range;
#include <SDL.h>
#include <SDL_opengl.h>



TriangleMesh::TriangleMesh(const SDL_Surface* _image)
  :image(_image)
{
  vertices.push_back({{0,0}});
  vertices.push_back({{image->w,0}});
  vertices.push_back({{image->w,image->h}});
  vertices.push_back({{0, image->h}});
  vertices.push_back({{image->w/2, image->h/2}});
 
  triangles.push_back({{{0,1,4}},{255,255,255,255}});
  triangles.push_back({{{1,2,4}},{255,0,0,255}});
  triangles.push_back({{{2,3,4}},{0,0,255,255}});
  triangles.push_back({{{3,0,4}},{0,255,0,255}});
  
}

void TriangleMesh::renderOpenGL() const{
  glBegin(GL_TRIANGLES);
  for(auto& t : triangles){
	glColor4ub(t.color.r, t.color.g, t.color.b, t.color.a);
	for(auto j : {0,1,2}){
	  glVertex2d(vertices[t.vertices[j]].position(0),
				 vertices[t.vertices[j]].position(1));
	}
  }
  glEnd();
}
