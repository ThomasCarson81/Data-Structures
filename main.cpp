#include <iostream>
#include <vector>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

struct LLNode
{
    string key = key;
    string value = value;
    LLNode *next = nullptr;
    LLNode()
    {
        this->key = "";
        this->value = "";
        cout << "Default constructor called" << endl;
    }
    LLNode(string key, string value)
    {
        this->key = key;
        this->value = value;
    }
    LLNode(string key, string value, LLNode *prev)
    {
        this->key = key;
        this->value = value;
        prev->next = this;
    }
};
unsigned long long Hash(string input)
{
    unsigned long long result = 1;
    for (int i = 0; i < input.length(); i++)
    {
        result += input[i] * (i + 1);
    }
    return result;
}
class Dict
{
public:
    int size;
    vector<LLNode> vec;
    Dict(string key, string value, int size)
    {
        this->size = size;
        vec.resize(size * sizeof(LLNode));
        int index = Hash(key) % size;
        if (vec[index].key == "")
        {
            vec[index].key = key;
            vec[index].value = value;
        }
        else
        {
            new LLNode(key, value, &vec[index]);
        }
    }
    string Get(string key)
    {
        int index = Hash(key) % size;
        if (vec[index].key == key)
        {
            return vec[index].value;
        }
        else
        {
            return "";
        }
    }
    void Set(string key, string value)
    {
        int index = Hash(key) % size;
        if (vec[index].key == key)
        {
            vec[index].value = value;
        }
        else
        {
            new LLNode(key, value, &vec[index]);
        }
    }
};

int main()
{
    int len;
    cout << "Enter length of HashMap: ";
    cin >> len;
    string key, value;
    cout << "Enter key: ";
    cin >> key;
    cout << "Enter value: ";
    cin >> value;
    Dict dict(key, value, len);
    while (true)
    {
        string input;
        cout << "Enter a key: ";
        cin >> input;
        string result = dict.Get(input);
        if (!result.empty())
        {
            cout << "Value: " << result << endl;
        }
        else
        {
            cout << "Enter a value:";
            cin >> value;
        }
    }
    return 0;
}
