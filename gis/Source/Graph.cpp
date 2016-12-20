#include "Graph.h"


Graph::Graph() : begin(0), end(0), flow(0)
{
    graph.push_back(std::vector<Edge>());
}

Graph::Graph(const Graph& g)
    : begin(g.begin), end(g.end), flow(g.flow), graph(g.graph) {}

Graph::Graph(const std::string& file) : begin(0), end(0), flow(0)
{
    graph.push_back(std::vector<Edge>());

    std::ifstream fs(file.c_str());
    if (!fs.is_open())
    {
        std::cerr << "input file" << std::endl;
        return;
    }

    std::string line;
    
    // flow
    std::getline(fs, line);
    std::istringstream myStream(line.c_str());
    if (!(myStream >> flow))
    {
        std::cout << "flow" << std::endl;
        return;
    }
    // begin vertex
    std::getline(fs, line);
    myStream.clear();
    myStream.str(line.c_str());
    if (!(myStream >> begin))
    {
        std::cout << "begin" << std::endl;
        return;
    }
    //end vertex
    std::getline(fs, line);
    myStream.clear();
    myStream.str(line.c_str());
    if (!(myStream >> end))
    {
        std::cout << "end" << std::endl;
        return;
    }

    // adjacency list
    while (std::getline(fs, line))
    {
        int vertexS = 0;
        int vertexT = 0;
        int capacity = 0;
        myStream.clear();
        myStream.str(line.c_str());

        myStream.ignore(256, '(');
        while (myStream.peek() != EOF)
        {
            if (!(myStream >> vertexS))
            {
                std::cout << "vertexS" << std::endl;
            }
            myStream.ignore(256, ',');
            if (!(myStream >> vertexT))
            {
                std::cout << "vertexT" << std::endl;
            }
            myStream.ignore(256, ',');
            if (!(myStream >> capacity))
            {
                std::cout << "capacity" << std::endl;
            }
            Edge e(vertexT, capacity);
            addEdge(vertexS, e);

            myStream.ignore(256, '(');
        }
    }
}

Graph::~Graph() {}

std::pair<std::vector<Edge>, bool> Graph::adjacencyList(int vertex)
{
    if (vertex < graph.size())
    {
        return std::make_pair(graph[vertex], true);
    }
    else
    {
        return std::make_pair(graph[0], false);
    }
}

bool Graph::addEdge(int v, const Edge& e)
{
    if (graph.size() < v + 1)
    {
        for (int i = graph.size(); i < v + 1; ++i)
        {
            graph.push_back(std::vector<Edge>());
        }
    }
    std::vector<Edge>& adjList = graph[v];
    if (std::find(adjList.begin(), adjList.end(), e) == adjList.end())
    {
        adjList.push_back(e);
        if (graph.size() < e.vertex + 1)
        {
            for (int i = graph.size(); i < e.vertex + 1; ++i)
            {
                graph.push_back(std::vector<Edge>());
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool Graph::removeEdge(int v, const Edge& e)
{
    if (graph.size() < v + 1)
    {
        return false;
    }
    std::vector<Edge>& adjList = graph[v];
    auto it = std::find(adjList.begin(), adjList.end(), e);
    if ((it) == adjList.end())
    {
        return false;
    }
    else
    {
        adjList.erase(it);
        return true;
    }
}

void Graph::subtract(const Path& p)
{
    int currentVertex = p.startVertex;
    for (const Edge& e : p.path)
    {
        auto& adjl = graph[currentVertex];
        auto edge = std::find(adjl.begin(), adjl.end(), e);
        edge->capacity -= e.flow;
        if (edge->capacity == 0)
        {
            removeEdge(currentVertex, *edge);
        }
        currentVertex = e.vertex;
    }
}

std::ostream& operator<<(std::ostream& os, const Graph& g)
{
    os << g.flow << std::endl;
    os << g.begin << std::endl;
    os << g.end << std::endl;
    for (int i = 0; i < g.graph.size(); ++i)
    {
        auto& adjl = g.graph[i];
        for (auto& e : adjl)
        {
            os << "(" << i << ", "
                << e.vertex << ", "
                << e.capacity << ") ";
        }
        os << std::endl;
    }


    os << std::endl;
    return os;
}

std::vector<Path> Graph::find_shortest_paths()
{
    // Result paths
    std::vector<Path> paths;

    // Counter of remaining flow
    int remain_flow = flow;
    while(remain_flow>0)
    {
        try
        {
            // Find shortest path at each step
            Path shortest_path = bfs(remain_flow);
            remain_flow -= shortest_path.flow;
            subtract(shortest_path);
            paths.push_back(shortest_path);
        }
        catch(...)
        {
            // Flow cannot be sent
            paths.clear();
            return paths;
        }
    }

    return paths;
}

Path Graph::bfs(int max_flow)
{
    // Queue of vertices for bread-first search
    std::queue<int> _queue;
    // Vector of preceding vertices for path finding
    std::vector<int> prev_vertex(graph.size(), -1);
    // Vector of logical values, if vertix has been visited
    std::vector<bool> visited(graph.size(), false);

    // Add starting vertix to queue
    _queue.push(begin);
    visited[begin] = true;

    // Flag, if path is completed
    bool end_found = false;

    while(!_queue.empty())
    {
        int vertex = _queue.front();
        _queue.pop();

        // Break if path is completed
        if(vertex==end)
        {
            end_found = true;
            break;
        }
        // Bread search
        for(Edge e : adjacencyList(vertex).first)
        {
            if(!visited[e.vertex])
            {
                visited[e.vertex] = true;
                _queue.push(e.vertex);
                prev_vertex[e.vertex] = vertex;

            }
        }
    }

    // Throw exception if path is not found
    if(!end_found)
    {
        throw "Path not found";
    }

    // Reconstruct the path from start to end
    std::vector<int> path;
    path.insert(path.begin(), end);
    int path_vertex = prev_vertex[end];
    while(path_vertex != begin)
    {
        path.insert(path.begin(), path_vertex);
        path_vertex = prev_vertex[path_vertex];
    }

    Path shortest_path = Path(begin);
    int temp_vertex = begin;
    for(int path_vertex : path)
    {
        for(Edge e : adjacencyList(temp_vertex).first)
        {
            if(e.vertex==path_vertex)
            {
                shortest_path.addEdge(e);
                temp_vertex = e.vertex;
            }           
        }
    }

    // Set max flow for a path
    shortest_path.setMaxFlow(std::min(max_flow,shortest_path.maxFlow()));
    return shortest_path;
}
