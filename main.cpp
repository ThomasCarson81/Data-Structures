#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;

typedef struct LLNode
{
    string key = key;
    string value = value;
    LLNode *next = nullptr;
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

long long Hash(string input)
{
    long long result = 1;
    for (int i = 0; i < input.length(); i++)
    {
        result += input[i] * (i + 1);
    }
    return result;
}

int main()
{
    while (true)
    {
        cout << "Enter a string: ";
        string input;
        cin >> input;
        cout << "Hash: ";
        cout << Hash(input) << endl;
    }
    return 0;
}
