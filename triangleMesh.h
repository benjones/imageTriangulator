#pragma once

#include<SDL.h>
#include<vector>
#include<array>
#include<eigen3/Eigen/Eigen>

struct Vertex{

  Eigen::Vector2d position;
  
};

struct Triangle{
  std::array<size_t, 3> vertices;
  SDL_Color color;
};

struct MeshEvent{
};


class TriangleMesh{

public:
  TriangleMesh(const SDL_Surface* _image);
  
  void addBestVertex();
  void splitBestEdge();
  void bestVertexMove();

  void undoEvent();
  void renderOpenGL() const;
  
  SDL_Color averageColorInTriangle(size_t triangleIndex) const;

  std::vector<Triangle> triangles;
  std::vector<Vertex> vertices;

  std::vector<MeshEvent> eventLog;

  const SDL_Surface* image;
  
  bool pointInTriangle(Eigen::Vector2d point, const Triangle& triangle) const;
  
  SDL_Color readColorAtPixel(int x, int y) const;
};
