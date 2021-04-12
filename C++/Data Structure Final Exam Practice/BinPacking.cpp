//MOHAMMAD IMMAM


#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

class BinPack
{
	void PackBin()
	{
		//BIN PACKING PROBLEM

	   //Declaring constraints
		const int CAPACITY = 10;
		std::string inpLine;

		//Getting Input
		getline(cin, inpLine);
		//Formatiing Input
		std::vector<int> inp;
		cout << inpLine << "\n";
		int totalW = 0;
		std::map<int, int> bins;    //Contains Bin Number and Bin Inputs
		for (int i = 0, j = 0; i < (inpLine.length() / 2) + 1; i++)
		{
			int t = stoi(inpLine.substr(j, 1));
			inp.push_back(t);
			totalW += inp[i];
			if (j + 2 < inpLine.length())
				j += 2;
			//inp[i] has weights
		}

		int cBin = 0;
		int wInHandIndex = 0;
		while (totalW > 0)
		{
			int wInHand = inp[wInHandIndex];
			int maxFill = -1;
			for (auto b = bins.begin(); b != bins.end(); b++)
			{
				//Check if it can take the number
				if (b->second + wInHand <= CAPACITY)
				{
					int tempFill = (b->second) + wInHand;
					if (tempFill > 0)
						maxFill = b->first;
				}
			}
			if (maxFill != -1)
			{
				//Max input Bin found
				bins[maxFill] += wInHand;
				wInHandIndex++;
			}
			else
			{
				//we need to add a bin
				bins[cBin] += wInHand;
				wInHandIndex++;
				cBin++;
			}
			totalW -= wInHand;

		}

		for (auto b = bins.begin(); b != bins.end(); b++)
		{
			cout << b->second << " ";
		}
		int input;
		cin >> input;
	}
};
