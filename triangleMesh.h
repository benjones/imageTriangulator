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
  enum class Type{
	ADD_BEST_VERTEX,
	  SPLIT_BEST_EDGE,
	  MOVE_BEST_VERTEX
  };
  
  //info needed to undo these events
  struct AddVertexInfo{
	//this should probably just 1 or 2, actaully
	std::vector<Triangle> trianglesRemoved;
	size_t vertex_index; //probably unnecessary, since it should be the last vertex
  };
  struct SplitEdgeInfo{
	//whatever
  };
  struct MoveVertexInfo{
	//whatever
  };


  union LogInfo{
	AddVertexInfo addVertexInfo;
	SplitEdgeInfo splitEdgeInfo;
	MoveVertexInfo moveVertexInfo;
  };

  Type eventType;
  LogInfo logInfo;
};


class TriangleMesh{

public:
  TriangleMesh(const SDL_Surface* _image);
  
  void addBestVertex();
  void splitBestEdge();
  void moveBestVertex();

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
