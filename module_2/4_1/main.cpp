#include <bits/stdc++.h>

using namespace std;

template <typename T>
class AVLTree {
    struct TreeNode {
        explicit TreeNode(T value)
                : value(value), height(1), count(1), left(nullptr), right(nullptr) {}

        size_t height;
        size_t count;
        TreeNode* left;
        TreeNode* right;
        T value;
    };

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { destroyTree(root); }

    bool Has(const T& element) {
        TreeNode* tmp = root;
        while (tmp) {
            if (tmp->value == element)
                return true;

            if (element > tmp->value)
                tmp = tmp->right;
            else
                tmp = tmp->left;
        }

        return false;
    }

    int Add(const T& element) {
        int index = 0;
        root = addInternal(root, element, index);
        return index;
    }

    void Delete(int index) {
        root = deleteInternal(root, index + 1);
    }

private:
    size_t getHeight(TreeNode* node) {
        return node ? node->height : 0;
    }

    size_t getCount(TreeNode* node) {
        return node ? node->count : 0;
    }

    void fixHeight(TreeNode* node) {
        size_t heightLeft = getHeight(node->left);
        size_t heightRight = getHeight(node->right);
        node->height = max(heightLeft, heightRight) + 1;
    }

    void fixCount(TreeNode* node) {
        size_t countLeft = getCount(node->left);
        size_t countRight = getCount(node->right);
        node->count = 1 + countLeft + countRight;
    }

    int balanceFactor(TreeNode* node) {
        return getHeight(node->right) - getHeight(node->left);
    }

    void destroyTree(TreeNode* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    TreeNode* addInternal(TreeNode* node, const T& element, int& index) {
        if (!node)
            return new TreeNode(element);
        if (element < node->value) {
            index += getCount(node->right) + 1;
            node->left = addInternal(node->left, element, index);
        }
        else if (element > node->value)
            node->right = addInternal(node->right, element, index);

        return balance(node);
    }

    TreeNode* findAndRemoveMin(TreeNode* node, TreeNode** min) {
        if (!node->left) {
            *min = node;
            return node->right;
        }
        node->left = findAndRemoveMin(node->left, min);
        return balance(node);
    }

    TreeNode* findAndRemoveMax(TreeNode* node, TreeNode** max) {
        if (!node->right) {
            *max = node;
            return node->left;
        }
        node->right = findAndRemoveMax(node->right, max);
        return balance(node);
    }

    TreeNode* deleteInternal(TreeNode* node, int index) {
        if (!node || index > getCount(node))
            return nullptr;

        int tmpIndex = getCount(node->right) + 1;
        if (index > tmpIndex)
            node->left = deleteInternal(node->left, index - tmpIndex);
        else if (index < tmpIndex)
            node->right = deleteInternal(node->right, index);
        else {
            TreeNode* left = node->left;
            TreeNode* right = node->right;

            delete node;

            if (!right) return left;

            // newNode = max in left subTree or min in right subTree
            TreeNode* newNode = nullptr;
            TreeNode* subTree;

            if (getHeight(left) > getHeight(right)) {
                subTree = findAndRemoveMax(left, &newNode);
                newNode->right = right;
                newNode->left = subTree;
            } else {
                subTree = findAndRemoveMin(right, &newNode);
                newNode->left = left;
                newNode->right = subTree;
            }

            return balance(newNode);
        }
        return balance(node);
    }

    TreeNode* balance(TreeNode* pivot) {
        fixHeight(pivot);
        fixCount(pivot);

        switch (balanceFactor(pivot)) {
            case 2: {
                if (balanceFactor(pivot->right) < 0)
                    pivot->right = smallTurnRight(pivot->right);
                return smallTurnLeft(pivot);
            }
            case -2: {
                if (balanceFactor(pivot->left) > 0)
                    pivot->left = smallTurnLeft(pivot->left);
                return smallTurnRight(pivot);
            }
            default:
                return pivot;
        }
    }

    TreeNode* smallTurnRight(TreeNode* pivot) {
        TreeNode* newPivot = pivot->left;
        pivot->left = newPivot->right;
        newPivot->right = pivot;

        fixHeight(pivot);
        fixHeight(newPivot);
        fixCount(pivot);
        fixCount(newPivot);

        return newPivot;
    }

    TreeNode* smallTurnLeft(TreeNode* pivot) {
        TreeNode* newPivot = pivot->right;
        pivot->right = newPivot->left;
        newPivot->left = pivot;

        fixHeight(pivot);
        fixHeight(newPivot);
        fixCount(pivot);
        fixCount(newPivot);

        return newPivot;
    }

    TreeNode* root;
};

int main(int argc, const char* argv[]) {
    int n = 0;
    cin >> n;

    int cmd, value = 0;

    AVLTree<int> tree;
    for (int i = 0; i < n; i++) {
        cin >> cmd >> value;

        if (cmd == 1) {
            cout << tree.Add(value) << endl;
        } else {
            tree.Delete(value);
        }
    }

    return 0;
}
