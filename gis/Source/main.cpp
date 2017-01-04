#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include "Graph.h"
#include "Path.h"


void printOutput(const std::string& fileName, const std::vector<Path>& paths, float time)
{
    std::ofstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "output file" << std::endl;
        return;
    }
    file << "Time elapsed: " << time << " ms" << std::endl;
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
    std::string mode;
    if (argc < 4)
    {
        std::cout << " Poprawny sposób uruchomienia programu: " << std::endl;
        std::cout << " ./main plik_z_grafem.txt plik_do_zapisu_sciezek.txt wersja_algorytmu" << std::endl;
        std::cout << " Gdzie wersja_algorytmu 1 to algorytm SPE, 2 to algorytm LPE" << std::endl << std::endl;
        input = "Test_graphs/graf.txt";
        output = "out.txt";
        Graph graph(input);
        const clock_t begin_time = clock();
        auto paths = graph.find_shortest_paths();
        auto time = float(clock() - begin_time) / CLOCKS_PER_SEC;
        std::cout << "Wynik dla grafu przykładowego z pliku: \"" << input << "\" zapisano w pliku \"" << output << "\"" << std::endl;
        printOutput(output, paths, time);
    }
    else
    {
        input = argv[1];
        output = argv[2];
        mode = argv[3];
        Graph graph(input);
        if (mode == "2")
        {
            const clock_t begin_time = clock();
            auto paths = graph.find_shortest_paths_2();
            auto time = float(clock() - begin_time) / CLOCKS_PER_SEC;
            std::cout << "Wynik dla grafu użytkownika z pliku: \"" << input << "\" zapisano w pliku \"" << output << "\"" << std::endl;
            printOutput(output, paths, time);
        }
        else
        {
            const clock_t begin_time = clock();
            auto paths = graph.find_shortest_paths();
            auto time = float(clock() - begin_time) / CLOCKS_PER_SEC;
            std::cout << "Wynik dla grafu użytkownika z pliku: \"" << input << "\" zapisano w pliku \"" << output << "\"" << std::endl;
            printOutput(output, paths, time);

        }

    }
    return 0;
}
