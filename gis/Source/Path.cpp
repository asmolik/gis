#include "Path.h"


Path::Path(int s) : startVertex(s), flow(0) {}

Path::~Path() {}

void Path::addEdge(const Edge& e)
{
    path.push_back(e);
}

int Path::maxFlow()
{
    return std::min_element(path.begin(), path.end(),
        [](const Edge& a, const Edge& b) 
    {return a.capacity < b.capacity; })->capacity;
}

int Path::length() const
{
    return path.size();
}

void Path::setMaxFlow(int f)
{
    flow = std::min(f, maxFlow());
    for (Edge& e : path)
    {
        e.capacity -= flow;
        e.flow += flow;
    }
}

std::ostream& operator<<(std::ostream& os, const Path& p)
{
    os << p.flow << ", " << p.length() << ": ";
    int currentVertex = p.startVertex;
    for (const Edge& e : p.path)
    {
        if (currentVertex != p.startVertex)
        {
            os << ", ";
        }
        os << "(" << currentVertex << ", "
            << e.vertex << ", "
            << e.flow << ")";
        currentVertex = e.vertex;
    }
    os << std::endl;
    return os;
}
