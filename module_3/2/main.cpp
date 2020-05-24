#include "bits/stdc++.h"

class ListGraph {
public:
    ListGraph(int size)
            : adjacencyLists(size)
    {
    }

    ~ListGraph()
    {
    }

    void AddEdge(int from, int to)
    {
        assert(0 <= from && from < adjacencyLists.size());
        assert(0 <= to && to < adjacencyLists.size());
        adjacencyLists[from].push_back(to);
        adjacencyLists[to].push_back(from);
    }

    int VerticesCount() const
    {
        return (int)adjacencyLists.size();
    }

    std::vector<int> GetNextVertices(int vertex) const
    {
        assert(0 <= vertex && vertex < adjacencyLists.size());
        return adjacencyLists[vertex];
    }

    int FindPath(int from, int to) const
    {
        std::vector<int> r(VerticesCount(), INT_MAX);
        std::vector<int> pi(VerticesCount(), -1);
        std::vector<int> counter(VerticesCount(), 0);
        std::queue<int> q;
        q.push(from);

        r[from] = 0;
        counter[from] = 1;
        int v = 0;

        while (!q.empty()) {
            v = q.front();
            q.pop();
            for (int w : GetNextVertices(v)) {
                if (r[w] > r[v] + 1) {
                    r[w] = r[v] + 1;
                    pi[w] = v;
                    q.push(w);
                    counter[w] = counter[v];
                }
                else if (r[w] == (r[v] + 1))
                    counter[w] += counter[v];
            }
        }

        return counter[to];
    }

private:
    std::vector<std::vector<int> > adjacencyLists;
};

int main()
{
    int numberOfVertices = 0;
    int numberOfEdges = 0;
    std::cin >> numberOfVertices >> numberOfEdges;

    ListGraph graph(numberOfVertices);
    int from, to = 0;
    for (int i = 0; i < numberOfEdges; i++) {
        std::cin >> from >> to;
        graph.AddEdge(from, to);
    }

    std::cin >> from >> to;
    std::cout << graph.FindPath(from, to);

    return 0;
}
