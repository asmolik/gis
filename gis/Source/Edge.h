#pragma once

class Edge
{
public:
    // The edge points to this vertex (int is number of vertex)
    int vertex;
    // Maximum flow for this edge
    int capacity;

    // Actual flow for this edge
    int flow;

public:
    Edge(int vertex, int capacity);
    Edge(int vertex, int capacity, int flow);
    ~Edge();
};

bool operator==(const Edge& a, const Edge& b);
