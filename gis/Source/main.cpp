#include <fstream>
#include <iostream>
#include <string>
#include "Graph.h"
#include "Path.h"


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
    std::cout<<"Wynik dla grafu z pliku: \""<<input<<"\" zapisano w pliku \""<<output<<"\""<<std::endl;
    printOutput(output, graph.find_shortest_paths());

}
