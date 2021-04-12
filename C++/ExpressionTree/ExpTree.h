 //
//  ExpTree.h
//  
//
//  Created by Resch,Cheryl on 7/11/19.
//

#ifndef ExpTree_h
#define ExpTree_h

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

//you may change this
struct node
{
    //construct parent Node or node with operator as data
    node(string data, node* leftData, node* rightData)
    {
        this->data=data;
        this->left=leftData;
        this->right=rightData;
        this->isOp=true;
    }
    //construct a leaf node which will contain operators
    node(string data)
    {
        this->data=data;
        isOp=false;
    }
    string data;
    node* left= nullptr;
    node* right= nullptr;
    bool isOp;
    int value;
};

class ExpTree {
    //do not change public methods
public:
    ExpTree();
    ~ExpTree();

    void CreateTree(vector<string> postFix);
    void SetVariableValues(vector<int> values);
    int EvaluateTree();
    void inOrderTraversalandPrint(ostream &out);


private:
    node* root;

    //added variables to help
    vector<string> postFix;
    int postFixExpressionCount;
    int postFixValueCount;

    //add helper methods here
    bool isOperator(string input);
    bool isOperand(string input);
    //** Method to check if the postfix expression passed in is valid**//
    bool CheckExpression(vector<string> postFix, int valueCount);
    void RecursiveInOrder(node* root, ostream &out);
    void RecursiveSetVariable(node* root, vector<int> &values);
    int RecursivelyEvaluateTree (node* root);
    void RecursivelyDestroyTree(node* root);

};

#endif /* ExpTree_h */