#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

class DLLNode
{

public:
    int data;
    DLLNode *prev;
    DLLNode *next;
    DLLNode() : data(0), prev(nullptr), next(nullptr) {}

    ~DLLNode()
    {
        if (prev != nullptr)   // if node is not head
            prev->next = next; // link previous node to next
        if (next != nullptr)   // if node is not tail
            next->prev = prev; // link next node to previous
        prev = nullptr;
        next = nullptr;
        data = 0;
    }

    void Link(DLLNode *prevNode, DLLNode *nextNode)
    {
        prev = prevNode;
        next = nextNode;
    }

    void Set(int newData)
    {
        data = newData;
    }

    void Swap(DLLNode *other)
    {
        int temp = data;
        data = other->data;
        other->data = temp;
    }
};

class DoublyLinkedList
{
private:
    DLLNode *head;
    DLLNode *tail;

public:
    int length;
    DoublyLinkedList() : head(nullptr), tail(nullptr), length(0) {}

    ~DoublyLinkedList()
    {
        // DLLNode *node = head;
        // while (node)
        // {
        //     DLLNode *next = node->next;
        //     delete node;
        //     node = next;
        // }
        for (DLLNode *node, *next = head; node; node = next)
        {
            next = node->next;
            delete node;
        }
    }

    /// @brief Add a node to the end of the list
    /// @param data The data to add
    void Append(int data)
    {
        DLLNode *node = new DLLNode();
        node->Set(data);
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
        length++;
    }

    /// @brief Find a node with the given value
    /// @param data Value to find
    /// @return The node with the given value, or nullptr if not found
    DLLNode *Find(int data)
    {
        DLLNode *node = head;
        while (node) // while node is not null
        {
            if (node->data == data)
            {
                return node;
            }
            node = node->next;
        }
        return nullptr; // Value not found
    }

    /// @brief Get the value at the given index
    /// @param index The index of the value to get
    /// @return The value at the given index
    /// @throws std::range_error If the index is out of range
    int ValueAt(int index)
    {
        if (index < 0 || index >= length)
        {
            throw new std::range_error("Index out of range");
        }
        int i = 0;
        DLLNode *node = head;
        while (i < index)
        {
            node = node->next;
            i++;
        }
        return node->data;
    }

    /// @brief Get the node at the given index
    /// @param index The index of the node to get
    /// @return The node at the given index
    /// @throws std::range_error If the index is out of range
    DLLNode *NodeAt(int index)
    {
        if (index < 0 || index >= length)
        {
            throw new std::range_error("Index out of range");
        }
        int i = 0;
        DLLNode *node = head;
        while (i < index)
        {
            node = node->next;
            i++;
        }
        return node;
    }

    /// @brief Check if the list contains a node with the given value
    /// @param data The int to check for
    /// @return True if the list contains the int, false otherwise
    bool Contains(int data)
    {
        if (Find(data) != nullptr)
        {
            return true;
        }
        return false;
    }

    /// @brief Remove the first occurence of the given value
    /// @param data The value to remove
    /// @throws std::invalid_argument If the data is not in the list
    void Remove(int data)
    {
        if (!Contains(data))
            throw new std::invalid_argument("Data not in list");
        DLLNode *node = Find(data);
        if (node == head)
        {
            head = head->next;
        }
        else if (node == tail)
        {
            tail = tail->prev;
        }
        delete node;
    }

    /// @brief Remove a node a the given index
    /// @param index The index of the node to remove
    /// @throws std::range_error If the index is out of range
    void Pop(int index)
    {
        if (index < 0 || index >= length)
        {
            throw new std::range_error("Index out of range");
        }
        if (length == 1)
        {
            delete this;
            return;
        }
        int i = 0;
        DLLNode *node = head;
        while (i < index)
        {
            node = node->next;
            i++;
        }
        if (node == head)
        {
            head = head->next;
        }
        if (node == tail)
        {
            tail = tail->prev;
        }
        delete node;
    }

    /// @brief Swap the values of two nodes
    /// @param index1 the index of the first node
    /// @param index2 the index of the second node
    void Swap(int index1, int index2)
    {
        if (index1 < 0 || index1 >= length || index2 < 0 || index2 >= length)
        {
            throw new std::range_error("Index out of range");
        }
        DLLNode *node1 = NodeAt(index1);
        DLLNode *node2 = NodeAt(index2);
        node1->Swap(node2);
    }

    /// @brief Reverse the list
    void Reverse()
    {
        DLLNode *node = head;
        while (node)
        {
            DLLNode *temp;
            temp = node->next;
            node->next = node->prev;
            node->prev = temp;
            node = temp;
        }
    }

    /// @brief Sort the list using the given compare function
    /// @param compare The compare function to use, should return true if the elements should be swapped
    /// @throws std::invalid_argument If the compare function is nullptr
    void BubbleSort(bool (*compare)(int, int))
    {
        if (compare == nullptr)
        {
            throw new std::invalid_argument("Compare function is nullptr");
        }
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < length - i - 1; j++)
            {
                if (compare(ValueAt(j), ValueAt(j + 1)))
                {
                    Swap(j, j + 1);
                }
            }
        }
    }

    /// @return string representation of the list
    string Repr()
    {
        string s;
        DLLNode *node = head;
        while (node != nullptr)
        {
            s += std::to_string(node->data) + ", ";
            node = node->next;
        }
        if (head != nullptr)
        {
            s += "\b\b  "; // remove trailing comma
        }
        return s;
    }
};
