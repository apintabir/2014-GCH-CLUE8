#include "graph.h"

Graph::Graph(int _numNodes) : numNodes(_numNodes)
{
    for (int i = 0; i < numNodes; ++i)
    {
        std::vector<double> v = std::vector<double>();
        for (int j = 0; j < numNodes; ++j)
        {
            v.push_back(0.0);
        }
        adjMat.push_back(v);
    }
}

void Graph::setEdge(int origin, int destination, double distance)
{
    adjMat[origin][destination] = distance;
}

double Graph::getEdge(int origin, int destination)
{
    return adjMat[origin][destination];
}

Graph Graph::readGraph()
{
    std::string lineInput;
    getline(std::cin, lineInput);
    int numNodes = atoi(lineInput.c_str());

    if DEBUG
    std::cout << "number of nodes: " << numNodes << std::endl;

Graph result = Graph(numNodes);

    // read coordinates
    std::vector<std::vector<double>> coords = std::vector<std::vector<double>>();
    double coord;
    for (int nodeIndex = 0; nodeIndex < numNodes; ++nodeIndex)
    {
        std::vector<double> pair = std::vector<double>();
        getline(std::cin, lineInput);
        std::stringstream coordStream(lineInput);

        coordStream >> coord;
        pair.push_back(coord);
        coordStream.ignore();
        coordStream >> coord;
        pair.push_back(coord);

        coords.push_back(pair);
    }

    if DEBUG
    std::cout << "last coord pair: " << coords[numNodes - 1][0] << "," << coords[numNodes - 1][1] << std::endl;

    // read adjacency matrix
    int adjacent;
    for (int n = 0; n < numNodes; ++n)
    {
        getline(std::cin, lineInput);
        std::stringstream ss(lineInput);

        for (int i = 0; i < numNodes; ++i)
        {
            ss >> adjacent;
            if (adjacent)
            {
                result.setEdge(n, i, ExtraMath::distance(coords[n][0], coords[n][1], coords[i][0], coords[i][1], 'M'));
            }

            if (ss.peek() == ',')
                ss.ignore();
        }
    }

    return result;
}


DijkstraResult Graph::dijkstra(Graph g, int s)
{
    std::cout << "starting dijkstra's" << std::endl;
    std::vector<double> d_vector = std::vector<double>();
    std::vector<int> pi_vector = std::vector<int>();
    std::vector<bool> q = std::vector<bool>();
    for (int i = 0; i < g.getNumNodes(); ++i)
    {
        d_vector.push_back(1000000000.0); // relative infinity
        pi_vector.push_back(-1); // nil predecessor
        q.push_back(true);
    }

    d_vector[s] = 0.0; // distance from s to itself

    // map from node ID to d, pi values
    std::map<int, std::pair<double, int>> set = std::map<int, std::pair<double, int>>();

    for (int n = 0; n < g.getNumNodes(); ++n)
    {
        int u = -1;
        double shortest_dist = 10000000.0;
        // extract-min:
        for (int j = 0; j < g.getNumNodes(); ++j)
        {
            if (q[j] && d_vector[j] < shortest_dist)
            {
                u = j;
                shortest_dist = d_vector[u];
            }
        }

        if (u == -1)
        {
            std::cerr << "oh, corks" << std::endl;
            return DijkstraResult(set);
        }

        if DEBUG
        std::cout << "u: " << u << std::endl;

    q[u] = false;
        set[u] = std::pair<double, int>(d_vector[u], pi_vector[u]); // shortest path to root is known

        for (int v = 0; v < g.getNumNodes(); ++v)
        {
            // relax edge:
            if (g.getEdge(u, v) != 0.0 && d_vector[v] > (d_vector[u] + g.getEdge(u, v)))
            {
                if DEBUG
                std::cout << "found better path to " << v << " via " << u << std::endl;
            d_vector[v] = d_vector[u] + g.getEdge(u, v);
                pi_vector[v] = u;
            }
        }
    }

    if DEBUG
{
    std::cout << "d and pi vectors: " << std::endl;
    for (int i = 0; i < g.getNumNodes(); ++i)
        {
            std::cout << "node: " << i;
            std::cout << "\td: " << d_vector[i];
            std::cout << "\tpi: " << pi_vector[i];
            std::cout << std::endl;
        }
    }

    return DijkstraResult(set);
}

std::string DijkstraResult::prettyPrintPathTo(int destination)
{
    std::stringstream result;
    result << "read this backwards:" << std::endl;
    int n = destination;
    bool keep_looping = true;
    while (keep_looping)
    {
        if (s[n].second == -1)
            keep_looping = false;
        result << "distance to " << n << ":\t" << s[n].first;
        result << "\tpi: " << s[n].second << std::endl;
        n = s[n].second;
    }

    return result.str();
}

int main()
{
    Graph g = Graph::readGraph();
    int keller = 0;
    int carlson = 39;
    int physics = 4;
    int amundson = 3;
    DijkstraResult answer = Graph::dijkstra(g, keller);
    // DijkstraResult answer = Graph::dijkstra(g, physics);
    printf("path from Keller to Carlson:\n%s\n\n", answer.prettyPrintPathTo(carlson).c_str());
    // printf("path from Keller to Carlson:\n%s\n\n", answer.prettyPrintPathTo(amundson).c_str());
    return 0;
}