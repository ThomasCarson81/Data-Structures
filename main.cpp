#include <iostream>
#include <vector>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::vector;

unsigned long long Hash(string input)
{
    unsigned long long result = 0;
    for (int i = 0; i < input.length(); i++)
    {
        result += input[i] * (i + 1);
    }
    return result;
}

struct KVPair
{
    string key;
    string value;
};

class DLLNode
{

public:
    KVPair *pair;
    DLLNode *prev;
    DLLNode *next;
    DLLNode() : pair(nullptr), prev(nullptr), next(nullptr) {}

    ~DLLNode()
    {
        Delete();
    }

    void Delete()
    {
        if (prev != nullptr)   // if node is not head
            prev->next = next; // link previous node to next
        if (next != nullptr)   // if node is not tail
            next->prev = prev; // link next node to previous
        delete pair;
    }

    void Link(DLLNode *prevNode, DLLNode *nextNode)
    {
        prev = prevNode;
        next = nextNode;
    }

    void Set(KVPair *newPair)
    {
        delete pair;
        pair = new KVPair(*newPair);
    }

    /// @return string representation of the node
    string Repr()
    {
        return "{\"" + pair->key + "\":\"" + pair->value + "\"}";
    }
};

class DoublyLinkedList
{
private:
    DLLNode *head;
    DLLNode *tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList()
    {
        DLLNode *node = head;
        while (node)
        {
            DLLNode *next = node->next;
            delete node;
            node = next;
        }
    }

    void Append(KVPair *pair)
    {
        DLLNode *node = new DLLNode();
        node->Set(pair);
        if (head == nullptr)
        {
            head = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

    /// @brief Find a node with the given key
    /// @param key Key to find
    /// @return The node with the given key, or nullptr if not found
    DLLNode *Find(string key)
    {
        DLLNode *node = head;
        while (node) // while node is not null
        {
            if (node->pair->key == key)
            {
                return node;
            }
            node = node->next;
        }
        return nullptr; // Key not found
    }

    /// @brief Find the value associated with a key
    /// @param key The key to find
    /// @return The value associated with the given key, or an empty string if not found
    string Get(string key)
    {
        DLLNode *node = head;
        while (node)
        {
            if (node->pair->key == key)
                return node->pair->value;
            node = node->next;
        }
        return "";
    }

    /// @return The length of the list
    int Length()
    {
        int length = 0;
        DLLNode *node = head;
        while (node != nullptr)
        {
            length++;
            node = node->next;
        }
        return length;
    }

    /// @return string representation of the list
    string Repr()
    {
        string s;
        DLLNode *node = head;
        while (node != nullptr)
        {
            s += node->Repr() + ", ";
            node = node->next;
        }
        s.pop_back();
        s.pop_back();
        return s;
    }
};

class Dict
{
public:
    int size;
    DoublyLinkedList *arr;
    Dict(int size) : size(size), arr(new DoublyLinkedList[size]) {}

    ~Dict()
    {
        delete[] arr;
    }

    /// @brief Find the value associated with the given key
    /// @param key The key to find
    /// @return The value associated with the given key, or an empty string if not found
    string Get(string key)
    {
        int index = Hash(key) % size;
        return arr[index].Get(key);
    }

    /// @brief Set the value associated with the given key
    /// @param key The key to set
    /// @param value The value to set
    void Set(string key, string value)
    {
        int index = Hash(key) % size;
        DLLNode *node = arr[index].Find(key);
        if (node) // if the key is already in the dictionary
            node->Set(new KVPair{key, value});
        else
            arr[index].Append(new KVPair{key, value});
    }
};

int main()
{
    int len;
    cout << "Enter length of HashMap: ";
    cin >> len;
    Dict dict(len);
    while (true)
    {
        string key, value;
        cout << "Enter a key: ";
        while (key.empty())
            getline(cin, key);
        string result = dict.Get(key);
        if (!result.empty())
            cout << "Value: " << result << endl;
        else
        {
            cout << "Enter a value: ";
            while (value.empty())
                getline(cin, value);
            dict.Set(key, value);
        }
    }
    return 0;
}
