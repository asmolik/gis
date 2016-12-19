#include "Edge.h"


Edge::Edge(int v, int c) : vertex(v), capacity (c), flow(0) {}

Edge::Edge(int v, int c, int f) : vertex(v), capacity(c), flow(f) {}

Edge::~Edge() {}

bool operator==(const Edge& a, const Edge& b)
{
    return a.vertex == b.vertex;
}
