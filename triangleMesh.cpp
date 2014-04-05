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

  for(auto i : range(triangles.size())){
	triangles[i].color = averageColorInTriangle(i);
  }
  
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

SDL_Color TriangleMesh::averageColorInTriangle(size_t triangleIndex) const{

  auto& tri = triangles[triangleIndex];


  auto minMaxX = std::minmax({vertices[tri.vertices[0]].position(0),
		vertices[tri.vertices[1]].position(0),
		vertices[tri.vertices[2]].position(0)});
  auto minMaxY = std::minmax({vertices[tri.vertices[0]].position(1),
		vertices[tri.vertices[1]].position(1),
		vertices[tri.vertices[2]].position(1)});

  Eigen::Vector3d colorSum = Eigen::Vector3d::Zero(); //using RGB for simplicity
  double pixelCount = 0;
  for(int y : range(static_cast<int>(minMaxY.first),
					static_cast<int>(ceil(minMaxY.second)))){
	
	for(int x : range(static_cast<int>(minMaxX.first),
					  static_cast<int>(ceil(minMaxX.second)))){
	  
	  
	  //for now check if ANY part of the pixel is in the triangle
	  //Triangle are big enough that at least one pixel corner will be contained
	  
	  if(pointInTriangle(Eigen::Vector2d{x,y}, tri) ||
		 pointInTriangle(Eigen::Vector2d{x+1,y}, tri) ||
		 pointInTriangle(Eigen::Vector2d{x+1,y+1}, tri) ||
		 pointInTriangle(Eigen::Vector2d{x,y+1}, tri)){
	
		auto thisColor = readColorAtPixel(x,y);
		
		colorSum(0) += thisColor.r;
		colorSum(1) += thisColor.g;
		colorSum(2) += thisColor.b;
		pixelCount += 1;
	  }
	}
  }
  return SDL_Color{static_cast<unsigned char>(colorSum(0)/pixelCount),
	  static_cast<unsigned char>(colorSum(1)/pixelCount),
	  static_cast<unsigned char>(colorSum(2)/pixelCount),
	  255};
}


bool TriangleMesh::pointInTriangle(Eigen::Vector2d point, const Triangle& triangle) const{

  //do 3 determinant checks
  Eigen::Matrix2d mat;
  for(auto i : {0,1,2}){
	mat.col(0) = vertices[triangle.vertices[i]].position - point;
	mat.col(1) = vertices[triangle.vertices[(i+1)%3]].position - point;
	if(mat.determinant() < 0){
	  return false;
	}
  }
  return true;
}


SDL_Color TriangleMesh::readColorAtPixel(int x, int y) const{
  uint32_t* pixel = 
	reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(image->pixels) +
								y*image->pitch +x*image->format->BytesPerPixel);
  
  SDL_Color ret;
  SDL_GetRGB(*pixel,
			 image->format,
			 &ret.r, &ret.g, &ret.b);
  ret.a = 255;
  return ret;
}
