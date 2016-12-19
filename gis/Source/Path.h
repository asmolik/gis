#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include "Edge.h"

class Path
{
public:
    // Start vertex of a path
    const int startVertex;

    // All edges of a path
    std::vector<Edge> path;

    // Path's flow
    int flow;


    explicit Path(int start);
    ~Path();

    // Adds an edge to a path
    void addEdge(const Edge& e);
    // Finds maximum flow in path
    int maxFlow();
    // Returns path's length
    int length() const;
    // Set path's flow, flow can't exceed maxFlow
    void setMaxFlow(int flow);
};

std::ostream& operator<<(std::ostream& os, const Path& obj);
