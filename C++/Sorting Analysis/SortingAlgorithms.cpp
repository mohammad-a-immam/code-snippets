//
// Created by ashim on 10/17/2019.
//

#include "SortingAlgorithms.h"

//**INSPIRED BY PSUEDO-CODE DISCUSSED IN TOP-HAT**//
vector<int> SortingAlgorithms::selectionSort(vector<int> arr) {
    for (int n=0; n< arr.size()-1; n++)
    {
        int posMin=n;
        for (int i=posMin+1; i<arr.size(); i++)
        {
            if (arr[i]<arr[posMin])
                posMin=i;
        }

        if (n!=posMin)
            Swap(n,posMin,arr);
    }
    return arr;
}

vector<int> SortingAlgorithms::bubbleSort(vector<int> arr) {
    bool sorted=false;

    while(!sorted)
    {
        sorted=true;
        for(int i=0, j=1; i< arr.size()-1;i++,j++)
        {
            if(arr[j]<arr[i])
            {
                Swap(i,j,arr);
                sorted=false;
            }
        }
    }
    return arr;
}

vector<int> SortingAlgorithms::mergerSort(vector<int> arr) {
    //BASE CASE
    if (arr.size()==1)  //ITS SORTED
    {
        return arr;
    }
    int midPoint=arr.size()/2;
    vector<int> l1;
    vector <int> l2;
    //make l1
    for (int i=0; i<=midPoint-1; i++)
    {
        l1.push_back(arr[i]);
    }
    for (int i=midPoint; i<arr.size(); i++)
    {
        l2.push_back(arr[i]);
    }
    l1=mergerSort(l1);
    l2=mergerSort(l2);
    return merge(l1,l2);
}

void SortingAlgorithms::Swap(int indOne, int indTwo, vector<int> &arr) {
    int temp= arr[indOne];
    arr[indOne]=arr[indTwo];
    arr[indTwo]=temp;
}

vector<int> SortingAlgorithms::merge(vector<int> l1, vector<int> l2) {
    int i,j=0;
    vector<int> result;
    for (i=0, j=0; i<l1.size() & j<l2.size();)
    {
        if (l1[i]<l2[j])
        {
            result.push_back(l1[i]);
            i++;
        }

        else
        {
            result.push_back(l2[j]);
            j++;
        }
    }

    //DONE WITH ONE LIST

    while (i<l1.size())
    {
        result.push_back(l1[i]);
        i++;
    }

    while (j<l2.size())
    {
        result.push_back(l2[j]);
        j++;
    }

    return result;
}



