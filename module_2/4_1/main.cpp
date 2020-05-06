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

    void Add(const T& element) {
        root = addInternal(root, element);
    }

    void Delete(const T& element) {
        root = deleteInternal(root, element);
    }

private:
    size_t getHeight(TreeNode* node) { return node ? node->height : 0; }

    size_t getCount(TreeNode* node) { return node ? node->count : 0; }

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

    TreeNode* addInternal(TreeNode* node, const T& element) {
        if (!node) return new TreeNode(element);
        if (element < node->value)
            node->left = addInternal(node->left, element);
        else
            node->right = addInternal(node->right, element);

        return balance(node);
    }

    TreeNode* findAndRemoveMin(TreeNode* node) {
        TreeNode* prev = node;
        TreeNode* tmp = node->left;
        if (!tmp)
            return node;

        while (tmp->left) {
            prev = tmp;
            tmp = tmp->left;
        }
        prev->left = tmp->right;

        balance(node);
        tmp->right = node;

        return tmp;
    }

    TreeNode* deleteInternal(TreeNode* node, const T& element) {
        if (!node) return nullptr;
        if (element < node->value)
            node->left = deleteInternal(node->left, element);
        else if (element > node->value)
            node->right = deleteInternal(node->right, element);
        else {
            TreeNode* left = node->left;
            TreeNode* right = node->right;

            delete node;

            if (!right) return left;

            TreeNode* newNode;
            //if (getHeight(left) > getHeight(right)) {
            //    newNode = findAndDeleteMax(left);
            //} else {
            //      newNode = findAndDeleteMin(right);
            //}

            newNode = findAndRemoveMin(right);
            newNode->left = left;

            return balance(newNode);
        }
        return balance(node);
    }

    TreeNode* balance(TreeNode* pivot) {
        fixHeight(pivot);
        fixCount(pivot);

        switch (balanceFactor(pivot))
        {
            case 2:
            {
                if (balanceFactor(pivot->right) < 0)
                    pivot->right = smallTurnRight(pivot->right);
                return smallTurnLeft(pivot);
            }
            case -2:
            {
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
            tree.Add(value);
            cout << "OK";
            //cout << tree.getIndex(value);
        } else {
            tree.Delete(value);//tree.DeleteByIndex(value);
            cout << "DEL OK";
        }
    }

    return 0;
}
