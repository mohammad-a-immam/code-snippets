/*
 MOHAMMAD IMMAM
*/




#include <vector>
#include <iostream>
using namespace std;

class Heap
{
	int arr[2];
public:
	Heap(vector<int> array)
	{
		for (int i=0; i<array.size();i++)
		{
			Insert(array[i]);
		}
	}

	int getLeftChild(int v)
	{
		return (2 * v) + 1;
	}
	int getRightChild(int v)
	{
		return (2 * v) + 2;
	}
	int getParent(int v)
	{
		if (v % 2 == 0)
		{
			if ((v / 2) - 1 >= 0)
				return (v / 2) - 1;
		}

		else
		{
			if ((v/2)>= 0)
				return (v / 2);
		}
	}

	int size()
	{
		heapArr.size();
	}

	void Insert(int n)
	{
		
	}
};
