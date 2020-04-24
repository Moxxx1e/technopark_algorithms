#include <bits/stdc++.h>

using namespace std;

template <typename T>
class TreeNode {
public:
    TreeNode(): left(nullptr), right(nullptr), parent(nullptr) {}
    explicit TreeNode(T value): value(value), left(nullptr), right(nullptr), parent(nullptr){}
    T value;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
};

template <typename T>
class Comparator {
public:
    bool operator()(const T& left, const T& right)
    {
        return left < right;
    }
};

template <typename T, typename Comparator>
class BinaryTree {
public:
    BinaryTree(): root(), isEmpty(true) {}

    void Add(const T& newElement)
    {
        auto* newNode = new TreeNode<T>(newElement);

        if (isEmpty) {
            root = newNode;
            isEmpty = false;
            return;
        }

        TreeNode<T>* tmp = root;
        while (newNode->parent == nullptr) {
            if (!cmp(newElement, tmp->value)) {
                if (tmp->right == nullptr) {
                    tmp->right = newNode;
                    newNode->parent = tmp->right;
                }
                else
                    tmp = tmp->right;
            } else {
                if (tmp->left == nullptr) {
                    tmp->left = newNode;
                    newNode->parent = tmp->left;
                }
                else
                    tmp = tmp->left;
            }
        }

    }

    void BFS()
    {
        queue<TreeNode<T>*> queue;
        TreeNode<T>* tmp = root;
        queue.push(tmp);

        while (!queue.empty()) {
            tmp = queue.front();
            queue.pop();
            cout << tmp->value << " ";
            if (tmp->left != nullptr)
                queue.push(tmp->left);
            if (tmp->right != nullptr)
                queue.push(tmp->right);
        }
    }

private:
    TreeNode<T> *root;
    bool isEmpty;
    Comparator cmp;
};

int main() {
    int n;
    cin >> n;

    BinaryTree<int, Comparator<int>> tree;
    int tmpElement;
    for (int i = 0; i < n; i++) {
        cin >> tmpElement;
        tree.Add(tmpElement);
    }

    tree.BFS();

    return 0;
}
