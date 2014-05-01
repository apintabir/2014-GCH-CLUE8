#ifndef GRAPH_H
#define GRAPH_H

#define DEBUG (true)

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <queue>

#include "extra_math.h"

class DijkstraResult
{
public:
  DijkstraResult(std::map<int, std::pair<double, int>> _s) : s(_s) {}
  std::string prettyPrintPathTo(int destination);
private:
  std::map<int, std::pair<double, int>> s;
};


class Graph
{
public:
  static Graph readGraph();
  static DijkstraResult dijkstra(Graph g, int s);

  Graph(int numNodes);
  
  // set the distance between two nodes.
  // set to 0 to remove edge
  void setEdge(int origin, int destination, double distance);

  // returns 0 if no edge present
  double getEdge(int origin, int destination);

  int getNumNodes() { return numNodes; }

private:
  int numNodes;

  // stores distance between edges
  // zero means no edge 
  std::vector<std::vector<double>> adjMat;
};

#endif