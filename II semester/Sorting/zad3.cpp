#include <iostream>
#include <vector>

using namespace std;

bool buildTowersDFS(const vector<int>& elements, vector<bool>& used, int T, int K, int currHeight, int towersBuilt) 
{
    if (towersBuilt == T) 
    {
        return true;
    }

    for (int i = 0; i < elements.size(); i++)
    {
        if (!used[i] && elements[i] >= K) 
        {
            used[i] = true;

            if (buildTowersDFS(elements, used, T, K, currHeight + elements[i], towersBuilt + 1)) 
            {
                return true;
            }

            used[i] = false;
        }
    }

    return false;
}

bool canBuildTowers(const vector<int>& elements, int T, int K)
{
    vector<bool> used(elements.size(), false);
    return buildTowersDFS(elements, used, T, K, 0, 0);
}

int main() 
{
    vector<int> elements = { 5, 7, 6, 9, 8 };
    int T = 3;
    int K = 6;

    if (canBuildTowers(elements, T, K))
    {
        cout << "Mozna zbudowac " << T << " wieze o minimalnej wysokosci " << K << "." << endl;
    }
    else 
    {
        cout << "Nie mozna zbudowac " << T << " wiez o minimalnej wysokosci " << K << "." << endl;
    }

    return 0;
}
