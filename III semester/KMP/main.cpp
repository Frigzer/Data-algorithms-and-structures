#include <iostream>
#include <vector>

using namespace std;

void machine(string text, string pattern)
{
	vector <int> tab;

	for (int i = 0; i < pattern.size(); i++)
	{
		tab.push_back(0);
		if (i == 0)
			tab[i] = 0;
		else if (i > 0)
		{
			for (int k = 0; k < i; k++)
			{
				if (pattern.substr(0, 1 + k) == (pattern.substr(i - k, 1 + k)))
					tab[i] = k + 1;
				//else
					//break;
			}
		}
		//cout << tab[i] << " ";
	}

	int s = 0;
	int q = 0;
	for (int i = 0; i <= text.size(); i++)
	{
		if (q == pattern.size())
		{
			cout << "Znaleziono wzorzec na pozycji: " << i - q << endl;
		}

		if (pattern[q] == text[i])
			q++;
		else if (q > 0)
		{
			q = tab[q - 1];
			i--;
		}
	}
}

int main()
{
	string text = "abracadabraabrabracadabra";
	string pattern = "abracadabra";

	//machine(pattern);
	machine(text, pattern);

	//find(text, key);
	//cout << pattern.substr(5, 5) + "abc";
}