#include <iostream>
#include <vector>

using namespace std;

void machine(string text, string pattern)
{
	int temp[126 - 33] = { 0 };
	string key = "";
	
	for (int i = 0; i < (126 - 33); i++)
	{
		for (int j = 0; j < pattern.size(); j++)
		{
			if (pattern[j] == i + 33)
			{
				temp[i] = 1;
				key += pattern[j];
				break;
			}
		}
		/*if (temp[i])
		{
			numberOfLetters++;
		}*/
	}
	
	vector <vector<int>> tab;
	for (int i = 0; i <= pattern.size(); i++)
	{
		vector<int> row;
		for (int j = 0; j < key.size(); j++)
		{
			row.push_back(0);
			//stworzyæ automat
			if (pattern[i] == key[j])
				row[j] = i + 1;
			else if (i == 0)
				row[j] = 0;
			else if(i > 0)
			{
				for (int k = 0; k < i; k++)
				{
					if (pattern.substr(0, i - k) == (pattern.substr(k + 1, i - k - 1) + key[j]))
						row[j] = i - k;
					//else
						//row[j] = 0;
				}
			}
		//	cout << row[j];
		}
		tab.push_back(row);
		//cout << endl;
	}

	int currentState = 0;
	for (int i = 0; i < text.size(); i++)
	{
		for (int j = 0; j < key.size(); j++)
		{
			if (text[i] == key[j])
				currentState = tab[currentState][j];
		}
		if (currentState == pattern.size())
			cout << "Znaleziono wzorzec na pozycji: " << i - currentState + 1 << endl; 
	}

}

int main()
{
	string text = "xyzabracadabraabraabracadabra";
	string pattern = "abracadabra";
	
	//machine(pattern);
	machine(text, pattern);

	//find(text, key);
	//cout << pattern.substr(5, 5) + "abc";
}