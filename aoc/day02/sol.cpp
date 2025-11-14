#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

bool isOnlyIncreasing(const vector<int> nums)
{
    for (int i = 0; i < nums.size()-1; i++)
    {
        if (nums.at(i) >= nums.at(i+1) || abs(nums.at(i) - nums.at(i+1))>3) return false;
    }
    return true;
}

bool isOnlyDecreasing(const vector<int> nums)
{
    for (int i = 0; i < nums.size()-1; i++)
    {
        if (nums.at(i) <= nums.at(i+1) || abs(nums.at(i) - nums.at(i+1))>3) return false;
    }
    return true;
}

void part1(const vector<string> &input)
{
    int tmp;
    int counter = 0;
    for (int i = 0; i < input.size(); i++) 
    {
        vector<int> numbers;
        stringstream ss(input.at(i));

        while (ss >> tmp)
        {
            numbers.push_back(tmp);
        }

        if (isOnlyIncreasing(numbers) || isOnlyDecreasing(numbers))
            counter++;
    }

    cout << endl << "part 1: " << counter << endl;
}

void part2(const vector<string> &input)
{
    int tmp;
    int counter = 0;
    for (int i = 0; i < input.size(); i++)
    {
        vector<int> numbers;
        stringstream ss(input.at(i));

        vector<int> numbersCopy;

        while (ss >> tmp)
        {
            numbers.push_back(tmp);
        }

        // Check if already safe
        if (isOnlyIncreasing(numbers) || isOnlyDecreasing(numbers))
        {
            counter++;
        }
        else
        {
            for (int i = 0; i < numbers.size(); i++)
            {
                // Try removing a number
                numbersCopy = numbers;
                numbersCopy.erase(numbersCopy.begin() + i);

                if (isOnlyIncreasing(numbersCopy) || isOnlyDecreasing(numbersCopy))
                {
                    counter++;
                    break;
                }
            }
        }
    }

    cout << endl << "part 2: " << counter << endl;
}

int main()
{
    vector<string> input;
    string line;

    while (getline(cin, line)) 
    {
        input.push_back(line);
    }

    part1(input);
    part2(input);
}

