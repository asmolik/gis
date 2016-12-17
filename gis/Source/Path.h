#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include "Edge.h"

class Path
{
public:
    const int startVertex;
    int flow;
    std::vector<Edge> path;

    explicit Path(int start);
    ~Path();

    void addEdge(const Edge& e);
    // finds maximum flow in path
    int maxFlow();
    int length() const;
    // flow can't exceed maxFlow
    void setMaxFlow(int flow);
};

std::ostream& operator<<(std::ostream& os, const Path& obj);

