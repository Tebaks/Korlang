#include <iostream>
#include <string>
using namespace std;

string trim(const string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

int main()
{
    int lineCount = 0;
    while (cin)
    {
        lineCount++;
        string input_line;
        getline(cin, input_line);
        auto l = trim(input_line);
        if ((l.compare("true") != 0) && (l.compare("") != 0))
        {
            cout << "ERROR at print : " << lineCount << endl;
            cout << "Test Failed!" << endl
                 << endl;
            return 0;
        }
    };
    cout << "Test Passed!" << endl
         << endl;
    return 0;
}
