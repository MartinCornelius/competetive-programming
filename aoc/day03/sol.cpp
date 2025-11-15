#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

int multiply(const string line, int idx)
{
    int comma = line.find(",", idx);
    int paren = line.find(")", comma);
    cout << "comma:" <<comma<< " paren:" << paren << endl;
    if (comma > idx+4+3) return 0;
    if (paren > idx+4+3+5) return 0;

    string sa = line.substr(idx+4, comma-(idx+4));
    string sb = line.substr(comma+1, paren-(comma+1));
    int a, b;
    cout << "sa: " << sa << " sb: " << sb << endl;
    try
    {
        a = stoi(sa);
        b = stoi(sb);
    }
    catch (invalid_argument)
    {
        return 0;
    }

    cout << endl;
    return a*b;
}

void part1(const vector<string> input)
{
    int counter = 0;

    for (int i = 0; i < input.size(); i++)
    {
        cout << input.at(i) << endl;

        vector<int> startPositions;
        size_t pos = input.at(i).find("mul(");
        while (pos != string::npos)
        {
            startPositions.push_back(pos);
            pos = input.at(i).find("mul(", pos+1);
        }

        for (int j = 0; j < startPositions.size(); j++)
        {
            cout << "Position: " << startPositions.at(j) << endl;
            counter += multiply(input.at(i), startPositions.at(j));
        }
    }

    cout << endl << "part 1: " << counter << endl;
}

void part2(const vector<string> input)
{
    int counter = 0;

    for (int i = 0; i < input.size(); i++)
    {
        vector<int> startPositions;
        size_t pos = input.at(i).find("mul(");
        while (pos != string::npos)
        {
            startPositions.push_back(pos);
            pos = input.at(i).find("mul(", pos+1);
        }

        vector<int> disablePositions;
        int disablePos = input.at(i).find("don't()");
        while (disablePos != string::npos)
        {
            disablePositions.push_back(disablePos);
            cout << "disable: " << disablePos<< endl;
            disablePos= input.at(i).find("don't()", disablePos+1);
        }
        vector<int> enablePositions;
        enablePositions.push_back(0);
        int enablePos = input.at(i).find("do()");
        while (enablePos != string::npos)
        {
            enablePositions.push_back(enablePos);
            cout << "enable: " << enablePos << endl;
            enablePos= input.at(i).find("do()", enablePos+1);
        }

        for (int j = 0; j < startPositions.size(); j++)
        {
            cout << "position: " << startPositions.at(j) << endl;
            int lastEnabled =0;
            int lastDisabled = -1;
            // check for enable
            for (int x = 0; x < enablePositions.size(); x++)
            {
                if (enablePositions.at(x) < startPositions.at(j) && enablePositions.at(x) > lastEnabled)
                    lastEnabled = enablePositions.at(x);
            }
            for (int x = 0; x < disablePositions.size(); x++)
            {
                if (disablePositions.at(x) < startPositions.at(j) && disablePositions.at(x) > lastDisabled)
                    lastDisabled = disablePositions.at(x);
            }
            cout << "last enabled: " << lastEnabled << " last disabled: " << lastDisabled << endl;

            if (lastEnabled > lastDisabled)
                counter += multiply(input.at(i), startPositions.at(j));
        }
    }

    cout << endl << "part 2: " << counter << endl;
}

int main()
{
    vector<string> input;
    string line;
    while (getline(cin, line)) input.push_back(line);

    // part1(input);
    part2(input);
}
