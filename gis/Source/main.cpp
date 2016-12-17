
#include <iostream>
#include "Graph.h"
#include "Path.h"


void lol()
{
    Edge e1(1, 2), e2(2, 2), e3(3, 4);
    Graph g;
    g.addEdge(0, e1);
    g.addEdge(1, e2);
    g.addEdge(2, e3);

    Path p(0);
    p.addEdge(e1);
    p.addEdge(e2);
    p.addEdge(e3);

    std::cout << p.maxFlow() << std::endl;

    p.setMaxFlow(1);
    std::cout << p;
    g.subtract(p);
}

int main()
{
    lol();

    Graph g("graf.txt");
    std::cout << g;

}