//
// Created by Immam, Mohammad on 10/17/2019 //
//
#include <vector>
using namespace std;

#ifndef SORTINGANALYSIS_SORTINGALGORITHMS_H
#define SORTINGANALYSIS_SORTINGALGORITHMS_H

class SortingAlgorithms {

public:
    vector<int> selectionSort(vector<int> arr);

    vector<int> bubbleSort(vector<int> arr);

    vector<int> mergerSort(vector<int> arr);


private:
    void Swap(int indOne, int indTwo, vector<int> &arr);
    vector<int> merge(vector<int> l1, vector<int> l2);
};


#endif //SORTINGANALYSIS_SORTINGALGORITHMS_H
