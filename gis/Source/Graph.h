#pragma once

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Edge.h"
#include "Path.h"


class Graph
{
    friend std::ostream& operator<<(std::ostream& out, const Graph& g);

private:
    // maps vertices to edges
    std::vector<std::vector<Edge>> graph;

public:
    int begin, end;
    // flow to send
    int flow;

    Graph();
    Graph(const Graph&);
    Graph(const std::string& filename);
    ~Graph();

    // false if vertex isn't in graph
    std::pair<std::vector<Edge>&, bool> adjacencyList(int vertex);
    bool addEdge(int vertexS, const Edge& edge);
    bool removeEdge(int vertexS, const Edge& edge);
    
    void subtract(const Path& path);
};

std::ostream& operator<<(std::ostream& os, const Graph& obj);

