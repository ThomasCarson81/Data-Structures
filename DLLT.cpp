#include <iostream>
#include <vector>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::vector;

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
        if (prev) // if node is not head
        {
            prev->next = next; // link previous node to next
        }
        if (next) // if node is not tail
        {
            next->prev = prev; // link next node to previous
        }
        delete pair;
        cout << "Deleted node: " << Repr() << endl;
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
            tail->Link(tail, node);
            tail = node;
        }
    }

    /// @brief remove node with given key
    /// @param key key of node to be removed
    void Remove(string key)
    {
        if (head == nullptr)
        {
            cout << "Cannot delete from empty list" << endl;
            return;
        }
        DLLNode *loopnode = head;
        while (loopnode) // while loopnode is not null
        {
            if (loopnode->pair->key == key)
            {
                loopnode->Delete();
                cout << "found " << key << endl;
                break;
            }
            loopnode = loopnode->next;
        }
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

int main()
{
    DoublyLinkedList list;

    list.Append(new KVPair{"key1", "value1"});
    list.Append(new KVPair{"key2", "value2"});
    list.Append(new KVPair{"key3", "value3"});
    list.Append(new KVPair{"key4", "value4"});

    list.Remove("key1"); // doesn't work

    cout << list.Repr() << endl;
}
