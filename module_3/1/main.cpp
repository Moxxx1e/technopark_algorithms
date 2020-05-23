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

// Списки смежности
class ListGraph : public IGraph {
public:
    ListGraph(int size) : container(size) {}
    ~ListGraph() {}

    ListGraph(const IGraph& graph) : container(graph.VerticesCount()) {
        for (int i = 0; i < graph.VerticesCount(); i++) {
            container[i] = graph.GetNextVertices(i);
        }
    }

    void AddEdge(int from, int to) override {
        assert(0 <= from && from <= VerticesCount());
        assert(0 <= to && to <= VerticesCount());
        container[from].push_back(to);
    }

    int VerticesCount() const override { return container.size(); }

    std::vector<int> GetNextVertices(int vertex) const override {
        assert(0 <= vertex && vertex <= VerticesCount());
        return container[vertex];
    }

    std::vector<int> GetPrevVertices(int vertex) const override {
        assert(0 <= vertex && vertex <= VerticesCount());
        std::vector<int> result;

        for (int from = 0; from < VerticesCount(); from++) {
            for (int to : container[from]) {
                if (to == vertex) result.push_back(from);
            }
        }

        return result;
    }

private:
    std::vector<std::vector<int>> container;
};

void BFS(const IGraph& graph, int vertex, std::vector<bool>& visited,
         const std::function<void(int)>& func) {
    std::queue<int> qu;
    qu.push(vertex);

    while (qu.empty()) {
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

void DFS(const IGraph& graph, int vertex, std::vector<bool>& visited,
         std::function<void(int)>& func) {
    visited[vertex] = true;
    func(vertex);

    for (int nextVertex : graph.GetNextVertices(vertex)) {
        if (!visited[nextVertex]) DFS(graph, nextVertex, visited, func);
    }
}

void mainDFS(const IGraph& graph, std::function<void(int)> func) {
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i])
            DFS(graph, i, visited, func);
    }
}

void mainBFS(const IGraph& graph, const std::function<void(int)>& func) {
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (visited[i])
            BFS(graph, i, visited, func);
    }
}

void topologicalSortInternal(const IGraph& graph, int vertex,
                             std::vector<bool>& visited,
                             std::deque<int>& sorted) {
    visited[vertex] = true;

    for (int nextVertex : graph.GetNextVertices(vertex)) {
        if (!visited[nextVertex])
            topologicalSortInternal(graph, nextVertex, visited, sorted);
    }

    sorted.push_front(vertex);
}

std::deque<int> topologicalSort(const IGraph& graph) {
    std::deque<int> sorted;
    std::vector<bool> visited(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i]) topologicalSortInternal(graph, i, visited, sorted);
    }

    return sorted;
}

class MatrixGraph : public IGraph {
public:
    void AddEdge(int from, int to) override {}

    int VerticesCount() const override {}

    std::vector<int> GetNextVertices(int vertex) const override {}

    std::vector<int> GetPrevVertices(int vertex) const override {}
};

class SetGraph : public IGraph {
public:
    void AddEdge(int from, int to) override {}

    int VerticesCount() const override {}

    std::vector<int> GetNextVertices(int vertex) const override {}

    std::vector<int> GetPrevVertices(int vertex) const override {}
};

class ArcGraph : public IGraph {
public:
    void AddEdge(int from, int to) override {}

    int VerticesCount() const override {}

    std::vector<int> GetNextVertices(int vertex) const override {}

    std::vector<int> GetPrevVertices(int vertex) const override {}
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
