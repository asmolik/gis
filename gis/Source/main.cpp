
#include <fstream>
#include <iostream>
#include <string>
#include "Graph.h"
#include "Path.h"


void lol()
{
    Edge e1(1, 2), e2(2, 2), e3(3, 4), e4(2, 3);
    Graph g;
    g.flow = 4;
    g.begin = 0;
    g.end = 3;
    g.addEdge(0, e1);
    g.addEdge(1, e2);
    g.addEdge(2, e3);
    g.addEdge(0, e4);

    Path p(0);
    p.addEdge(e1);
    p.addEdge(e2);
    p.addEdge(e3);
    std::vector<Path> paths = g.find_shortest_paths();

    std::cout<<"Wynik: "<<std::endl;
    for(Path p : paths)
    {
        std::cout<<p<<std::endl;
    }
    std::cout<<"Koniec wyniku."<<std::endl;
}

void printOutput(const std::string& fileName, const std::vector<Path>& paths)
{
    std::ofstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "output file" << std::endl;
        return;
    }
    int totalFlow = 0;
    for (auto& p : paths)
    {
        totalFlow += p.flow;
    }
    file << totalFlow << std::endl;
    file << "flow, length: path" << std::endl;
    for (auto& p : paths)
    {
        file << p;
    }
}

int main(int argc, char* argv[])
{
    std::string input;
    std::string output;
    if (argc < 3)
    {
        std::cout << argv[0] << " <input file> <output file>" << std::endl;
        //return 0;
        input = "graf.txt";
        output = "out.txt";
    }
    else
    {
        input = argv[1];
        output = argv[2];
    }

    Graph graph(input);
    // liczenie
    std::vector<Path> paths;



    Edge e1(1, 2), e2(2, 2), e3(3, 4);
    Path p(0);
    p.addEdge(e1);
    p.addEdge(e2);
    p.addEdge(e3);
    p.setMaxFlow(1);
    paths.push_back(p);
    printOutput(output, paths);

    lol();

    Graph g("graf.txt");
    std::cout << g;

}
