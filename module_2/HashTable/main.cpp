#include <bits/stdc++.h>

using namespace std;

#define A1 79
#define A2 97
class StringHasher {
public:
    StringHasher()
            : prime1(A1)
            , prime2(A2)
    {
    }

    size_t operator()(const string& key, size_t size, size_t i)
    {
        size_t hash = 0;
        size_t h1 = hashFunc(key, prime1);
        size_t h2 = 2 * hashFunc(key, prime2) + 1;
        hash = (h1 + i * h2) % size;

        return hash;
    }

private:
    size_t hashFunc(const string& key, int prime)
    {
        size_t hash = 0;
        for (int i = 0; i < key.size(); i++)
            hash = hash * prime + key[i];

        return hash;
    }

    int prime1;
    int prime2;
};

#define INIT_SIZE 8
#define FILL_KOEF 0.75

#define NIL "NIL"
#define DEL "DEL"

template <typename T, class Hasher>
class HashTable {
public:
    HashTable()
            : size(0)
    {
        for (int i = 0; i < INIT_SIZE; i++)
            table.push_back(NIL);
    }

    HashTable(size_t size)
            : size(0)
    {
        for (int i = 0; i < size; i++)
            table.push_back(NIL);
    }

    bool Add(const T& key)
    {
        if (size >= table.size() * FILL_KOEF)
            grow();

        int i = 0;
        int firstDel = -1;

        while (i < table.size()) {
            size_t hash = hasher(key, table.size(), i);

            if (table[hash] == NIL && firstDel == -1) {
                table[hash] = key;
                size++;
                return true;
            } else if (table[hash] == key) {
                return false;
            } else if (table[hash] == DEL && firstDel == -1) {
                firstDel = hash;
            }
            i++;
        }
        if (firstDel != -1) {
            table[firstDel] = key;
            size++;
            return true;
        }
        return false;
    }

    bool Delete(const T& key)
    {
        int i = 0;
        while (i < table.size()) {
            size_t hash = hasher(key, table.size(), i);

            if (table[hash] == NIL) {
                return false;
            }
            else if (table[hash] == key) {
                table[hash] = DEL;
                size--;
                return true;
            }
            i++;
        }
        return false;
    }

    bool Has(T key)
    {
        size_t i = 0;
        while (i < table.size()) {
            size_t hash = hasher(key, table.size(), i);
            if (table[hash] == NIL) {
                return false;
            }
            else if (table[hash] == key) {
                return true;
            }
            i++;
        }
        return false;
    }

private:
    void grow()
    {
        HashTable<T, Hasher> hashTable(table.size() * 2);
        for (int i = 0; i < table.size(); i++) {
            if (table[i] != NIL && table[i] != DEL)
                hashTable.Add(table[i]);
        }
        *this = std::move(hashTable);
    }

    size_t size;
    Hasher hasher;
    vector<T> table;
};

int main(int argc, const char* argv[])
{
    HashTable<string, StringHasher> table;

    char op;
    string str;
    while (cin >> op >> str) {
        switch (op) {
            case '+':
                std::cout << (table.Add(str) ? "OK" : "FAIL") << endl;
                break;
            case '-':
                cout << (table.Delete(str) ? "OK" : "FAIL") << endl;
                break;
            case '?':
                cout << (table.Has(str) ? "OK" : "FAIL") << endl;
                break;
        }
    }

    return 0;
}
