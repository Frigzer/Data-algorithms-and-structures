#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool canCreatePermutation(const vector<int>& sequence, int N) 
{
    vector<int> sortedSequence = sequence;
    sort(sortedSequence.begin(), sortedSequence.end());

    for (int i = 0; i < sortedSequence.size() - 1; i++) 
    {
        if (abs(sortedSequence[i] - sortedSequence[i + 1]) != N) 
        {
            bool foundPair = false;
            for (int j = i + 2; j < sortedSequence.size(); j++) 
            {
                if (abs(sortedSequence[i] - sortedSequence[j]) == N) 
                {
                    swap(sortedSequence[i + 1], sortedSequence[j]);
                    foundPair = true;
                    break;
                }
            }

            if (!foundPair)
            {
                return false; // Nie mo¿na utworzyæ pary
            }
        }
    }

    return true; // Mo¿na utworzyæ permutacjê
}

int main() 
{
    vector<int> sequence = { 1, 3, 2, 6, 4, 5 };
    int N = 1;

    if (canCreatePermutation(sequence, N)) 
    {
        cout << "Mozna utworzyc permutacje spelniajaca warunek." << endl;
    }
    else 
    {
        cout << "Nie mozna utworzyc permutacji spelniajacej warunek." << endl;
    }

    return 0;
}
