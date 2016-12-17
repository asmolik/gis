#pragma once

class Edge
{
public:
    // edge points to this vertex
    int vertex;
    // maximum flow for this edge
    int capacity;
    int flow;

public:
    Edge(int vertex, int capacity);
    Edge(int vertex, int capacity, int flow);
    ~Edge();
};

bool operator==(const Edge& a, const Edge& b);