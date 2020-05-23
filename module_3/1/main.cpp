#include <bits/stdc++.h>

// ListGraph, хранящий граф в виде массива списков смежности,
// MatrixGraph, хранящий граф в виде матрицы смежности,
// SetGraph, хранящий граф в виде массива хэш-таблиц/сбалансированных деревьев
// поиска,
// ArcGraph, хранящий граф в виде одного массива пар {from, to}.

struct IGraph {
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
    explicit ListGraph(int size)
            : container(size)
    {
    }

    explicit ListGraph(const IGraph& graph)
            : container(graph.VerticesCount())
    {
        for (int i = 0; i < graph.VerticesCount(); i++) {
            container[i] = graph.GetNextVertices(i);
        }
    }

    void AddEdge(int from, int to) override
    {
        assert(0 <= from && from <= VerticesCount());
        assert(0 <= to && to <= VerticesCount());
        container[from].push_back(to);
    }

    int VerticesCount() const override
    {
        return container.size();
    }

    std::vector<int> GetNextVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex <= VerticesCount());
        return container[vertex];
    }

    std::vector<int> GetPrevVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex <= VerticesCount());
        std::vector<int> result;

        for (int from = 0; from < VerticesCount(); from++) {
            for (int to : container[from]) {
                if (to == vertex)
                    result.push_back(from);
            }
        }

        return result;
    }

private:
    std::vector<std::vector<int> > container;
};

void DFS(const IGraph& graph, int vertex, std::vector<bool>& visited,
         std::function<void(int)>& func)
{
    visited[vertex] = true;
    func(vertex);

    for (int nextVertex : graph.GetNextVertices(vertex)) {
        if (!visited[nextVertex])
            DFS(graph, nextVertex, visited, func);
    }
}

void mainDFS(const IGraph& graph, std::function<void(int)> func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i])
            DFS(graph, i, visited, func);
    }
}

void BFS(const IGraph& graph, int vertex, std::vector<bool>& visited,
         std::function<void(int)>& func)
{
    std::queue<int> qu;
    qu.push(vertex);
    visited[vertex] = true;

    while (!qu.empty()) {
        int currentVertex = qu.front();
        qu.pop();

        func(currentVertex);

        for (int nextVertex : graph.GetNextVertices(currentVertex)) {
            if (!visited[nextVertex]) {
                visited[nextVertex] = true;
                qu.push(nextVertex);
            }
        }
    }
}

void mainBFS(const IGraph& graph, std::function<void(int)> func)
{
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i])
            BFS(graph, i, visited, func);
    }
}

void topologicalSortInternal(const IGraph& graph, int vertex,
                             std::vector<bool>& visited,
                             std::deque<int>& sorted)
{
    visited[vertex] = true;

    for (int nextVertex : graph.GetNextVertices(vertex)) {
        if (!visited[nextVertex])
            topologicalSortInternal(graph, nextVertex, visited, sorted);
    }

    sorted.push_front(vertex);
}

std::deque<int> topologicalSort(const IGraph& graph)
{
    std::deque<int> sorted;
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i])
            topologicalSortInternal(graph, i, visited, sorted);
    }

    return sorted;
}

class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(int size)
            : matrix(size)
    {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++)
                matrix[i].push_back(false);
        }
    }

    MatrixGraph(const IGraph& graph)
            : matrix(graph.VerticesCount())
    {
        for (int i = 0; i < graph.VerticesCount(); i++) {
            for (int j = 0; j < graph.VerticesCount(); j++)
                matrix[i].push_back(false);
        }
        for (int from = 0; from < graph.VerticesCount(); from++) {
            for (int to : graph.GetNextVertices(from)) {
                matrix[from][to] = true;
            }
        }
    }

    void AddEdge(int from, int to) override
    {
        assert(0 <= from && from <= VerticesCount());
        assert(0 <= to && to <= VerticesCount());
        matrix[from][to] = true;
    }

    int VerticesCount() const override
    {
        return matrix.size();
    }

    std::vector<int> GetNextVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex <= VerticesCount());
        std::vector<int> result;
        for (int j = 0; j < matrix.size(); j++) {
            if (matrix[vertex][j] == true)
                result.push_back(j);
        }
        return result;
    }

    std::vector<int> GetPrevVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex <= VerticesCount());
        std::vector<int> result;
        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[i][vertex] == true)
                result.push_back(i);
        }
        return result;
    }

private:
    std::vector<std::vector<bool> > matrix;
};

class SetGraph : public IGraph {
public:
    explicit SetGraph(int size)
            : container(size)
    {
    }

    explicit SetGraph(const IGraph& graph)
            : container(graph.VerticesCount())
    {
        for (int i = 0; i < graph.VerticesCount(); i++) {
            std::vector<int> vector = graph.GetNextVertices(i);
            std::set<int> set(vector.begin(), vector.end());
            container[i] = set;
        }
    }

    void AddEdge(int from, int to) override
    {
        assert(0 <= from && from <= VerticesCount());
        assert(0 <= to && to <= VerticesCount());
        container[from].insert(to);
    }

    int VerticesCount() const override
    {
        return container.size();
    }

    std::vector<int> GetNextVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex <= VerticesCount());
        std::vector<int> nextVertices(container[vertex].begin(),
                                      container[vertex].end());
        return nextVertices;
    }

    std::vector<int> GetPrevVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex <= VerticesCount());
        std::vector<int> prevVertices;
        for (int from = 0; from < VerticesCount(); from++) {
            for (int to : container[from]) {
                if (to == vertex)
                    prevVertices.push_back(from);
            }
        }
        return prevVertices;
    }

private:
    std::vector<std::set<int> > container;
};

struct Edge {
    Edge() = default;
    Edge(int from_, int to_)
            : from(from_)
            , to(to_)
    {
    }
    int from;
    int to;
};

class ArcGraph : public IGraph {
public:
    explicit ArcGraph(const IGraph& graph)
    {
        for (int i = 0; i < graph.VerticesCount(); i++) {
            for (int j : graph.GetNextVertices(i)) {
                container.emplace_back(i, j);
            }
        }
    }

    void AddEdge(int from, int to) override
    {
        assert(0 <= from && from <= VerticesCount());
        assert(0 <= to && to <= VerticesCount());
        container.emplace_back(from, to);
    }

    int VerticesCount() const override
    {
        int count = 0;
        for (auto i : container) {
            if (i.from > count)
                count = i.from;
            if (i.to > count)
                count = i.to;
        }
        return count + 1; // +1, тк индексация с нуля
    }

    std::vector<int> GetNextVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex <= VerticesCount());
        std::vector<int> nextVertices;
        for (auto i : container) {
            if (i.from == vertex)
                nextVertices.push_back(i.to);
        }
        return nextVertices;
    }

    std::vector<int> GetPrevVertices(int vertex) const override
    {
        assert(0 <= vertex && vertex <= VerticesCount());
        std::vector<int> prevVertices;
        for (auto i : container) {
            if (i.to == vertex)
                prevVertices.push_back(i.from);
        }
        return prevVertices;
    }

private:
    std::vector<Edge> container;
};

int main()
{
    ListGraph graph(7);
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 5);
    graph.AddEdge(1, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(1, 5);
    graph.AddEdge(1, 6);
    graph.AddEdge(3, 2);
    graph.AddEdge(3, 4);
    graph.AddEdge(3, 6);
    graph.AddEdge(5, 4);
    graph.AddEdge(5, 6);
    graph.AddEdge(6, 4);

    mainBFS(graph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    ArcGraph arcGraph(graph);
    SetGraph setGraph(arcGraph);
    MatrixGraph mGraph(setGraph);

    mainBFS(arcGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    mainBFS(setGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    mainBFS(mGraph, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    return 0;
}
