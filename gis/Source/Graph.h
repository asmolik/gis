#pragma once

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>
#include "Edge.h"
#include "Path.h"


class Graph
{
    friend std::ostream& operator<<(std::ostream& out, const Graph& g);

private:
    // maps vertices to edges
    std::vector<std::vector<Edge> > graph;

    // Breadth first search for shoretest path
    Path bfs(int max_flow);


public:
    // Start and finish of a flow
    int begin, end;
    // Amount flow to send
    int flow;

    Graph();
    Graph(const Graph&);
    Graph(const std::string& filename);
    ~Graph();

    // Return adjacency list for a given vertex, false if vertex isn't in graph
    std::pair<std::vector<Edge>, bool> adjacencyList(int vertex);

    // Add/remove edge to/from a graph
    bool addEdge(int vertexS, const Edge& edge);
    bool removeEdge(int vertexS, const Edge& edge);
    
    // Subtract edge from a graph
    void subtract(const Path& path);

    // Find shortest paths for given constraints
    std::vector<Path> find_shortest_paths();
};

std::ostream& operator<<(std::ostream& os, const Graph& obj);
