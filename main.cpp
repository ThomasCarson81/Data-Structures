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

struct DLLNode
{
    KVPair *pair;
    DLLNode *prev;
    DLLNode *next;
};

void Link(DLLNode *node1, DLLNode *node2)
{
    node1->next = node2;
    node2->prev = node1;
}
void Set(DLLNode *node, *KVPair pair)
{
    node->pair = pair;
}
void Delete(DLLNode *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
}

class Dict
{
public:
    int size;
    vector<KVPair> vec;
    Dict(string key, string value, int size)
    {
        this->size = size;
        vec.resize(size * sizeof(KVPair));
        int index = Hash(key) % size;
        vec[index].key = key;
        vec[index].value = value;
    }
    string Get(string key)
    {
        int index = Hash(key) % size;
        if (vec[index].key == key)
            return vec[index].value;
        return "";
    }
    void Set(string key, string value)
    {
        int index = Hash(key) % size;
        vec[index].key = key;
        vec[index].value = value;
    }
};

int main()
{
    int len;
    cout << "Enter length of HashMap: ";
    cin >> len;
    string key, value;
    cout << "Enter initial key: ";
    while (key.empty())
        getline(cin, key);
    cout << "Enter initial value: ";
    while (value.empty())
        getline(cin, value);
    Dict dict(key, value, len);
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
