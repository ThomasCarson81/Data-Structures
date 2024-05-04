#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;

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
