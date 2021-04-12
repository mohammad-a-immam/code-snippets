//
// Created by Mohammad Asfaq Immam on 9/5/2019.
// for Data Structure UF Fall 2019
//
#include <stack>
#include <cmath>
#include "ExpTree.h"
#include "PostFixTokens.h"

//Creates an expression Tree Object. Default Constructor Should Work for this
ExpTree::ExpTree() {
//Dfault Constructor with nothing happening
    root= nullptr;
//work with current and never change root and always point current to root at the end of the day//
}

ExpTree::~ExpTree() {
//we dont need the postFix that we created so Take it OFF
postFix.clear();

//go through the tree top to bottom and delete all the nodes that we created for the tree
//in other words destroy the tree
RecursivelyDestroyTree(root);
}

void ExpTree::RecursivelyDestroyTree(node* root)
{
    if (!root->isOp)
    {
        delete root;
        root=nullptr;
        return;
    }
    RecursivelyDestroyTree(root->left);
    RecursivelyDestroyTree(root->right);
    delete root;
    root= nullptr;
    return;
}

void ExpTree::CreateTree(vector<string> postFix) {
    //Considering the postFix passed into this method is valid
    this->postFix=postFix;
    //THE EDGE CASE WHEN ITS ONE OPERAND ONLY
    if (postFix.size()==1)
    {
        root->data=postFix[0];
    }
    stack<node*> pendingNodes;
    node* tempNode;
    node* left;
    node* right;
    for (int i=0; i<postFix.size(); i++)
    {
        string workingToken= postFix[i];
        if (isOperand(workingToken))
        {
            //it is an operand "a", "b" etc. create leafnode
            tempNode=new node(workingToken);
            pendingNodes.push(tempNode);

        }
        else if (isOperator(workingToken))
        {
            //it is an operator. + - etc. now make it the parent and give it left and right
            right= pendingNodes.top();
            pendingNodes.pop();
            left= pendingNodes.top();
            pendingNodes.pop();
            tempNode= new node(workingToken,left,right);
            root=tempNode;
            pendingNodes.push(tempNode);

            /* we are done with these pointers now they point to null
            tempNode= nullptr;
            left= nullptr;
            right= nullptr;*/
        }
    }
}

void ExpTree::SetVariableValues(vector<int> values) {
    if (!postFix.empty())
    {
        if (!CheckExpression(postFix, values.size()))
            throw invalid_argument( "Variable Count does not match! Check Values and rerun!" );
    }
    else  throw invalid_argument( "Create Tree not called yet on valid PostFix!" );

    RecursiveSetVariable(root,values);
    }

int ExpTree::EvaluateTree() {

    return RecursivelyEvaluateTree(root);
}


void ExpTree::inOrderTraversalandPrint(ostream &out) {
    /*traverse the tree and pass it to out
    consider that out is a valid output stream*/
    RecursiveInOrder(root,out);
}

int ExpTree:: RecursivelyEvaluateTree (node* root)
{
    if (root->left== nullptr || root->right== nullptr)
        return root->value;
    else if (root->data=="+")
        return RecursivelyEvaluateTree(root->left)+RecursivelyEvaluateTree(root->right);
    else if (root->data=="-")
        return RecursivelyEvaluateTree(root->left)-RecursivelyEvaluateTree(root->right);
    else if (root->data=="*")
        return RecursivelyEvaluateTree(root->left)*RecursivelyEvaluateTree(root->right);
    else if (root->data=="/")
        return RecursivelyEvaluateTree(root->left)/RecursivelyEvaluateTree(root->right);
    else if (root->data=="^")
        return pow(RecursivelyEvaluateTree(root->left),RecursivelyEvaluateTree(root->right));
    else if (root->data=="%")
        return RecursivelyEvaluateTree(root->left)%RecursivelyEvaluateTree(root->right);
}
void ExpTree::RecursiveSetVariable(node *root, vector<int> &values)
{
    //start at root and call recursion with respect to LNR
    //BASE CASE//
    if (!root->isOp)
    {
        root->value=values[values.size()-1];
        values.pop_back();
        return;
    }
    //If its not an operator then it will guranteed have two child given valid
    RecursiveSetVariable(root->right, values);
    RecursiveSetVariable(root->left, values);
}
void ExpTree::RecursiveInOrder(node* root, ostream &out)
{
    //start at root and call recursion with respect to LNR
    //BASE CASE//
    if (!root->isOp)
    {
        out<<root->data;
        return;
    }
    //If its not an operator then it will guranteed have two child given valid
    RecursiveInOrder(root->left, out);
    out<<" ";
    out<<root->data;
    out<<" ";
    RecursiveInOrder(root->right, out);
    //out<<" ";
}

bool ExpTree::CheckExpression(vector<string> postFix, int valueCount) {
    if (isOperator(postFix[0]))
        return false;
    int operatorCount = 0;
    int operandCount = 0;
    for (int i = 0; i < postFix.size(); i++) {
        if (isOperator(postFix[i]))
            operatorCount++;
        else if (isOperand(postFix[i]))
            operandCount++;
            //invalid syntax
        else
            return false; //The expression coming in is not valid because it is neither an operator nor operand
        // which means it is symbols
        //what if operator count is zero? i.e there are no operators
    }

        //There should always be at max one less operator than operands
        if (operatorCount >= operandCount)
            return false;
        //Now check if the numbers align
        if (!(operandCount == valueCount))
            return false;

        return true;
}


bool ExpTree::isOperand(string input) {

    if (input==")")
        return false;
    for (int i=0; i<input.length();i++)
    {
        if((!(input.at(i) >= '0' && input.at(i) <= '9')) && (!(input.at(i) >= 'a' && input.at(i) <= 'z')) && (!(input.at(i) >= 'A' && input.at(i) <= 'Z')))
            return false;
    }
    return true;
}

bool ExpTree::isOperator(string input) {
    if (input=="+"||input=="-"||input=="*"||input=="%"||input=="/"||input=="^"||input=="(")
    {
        return true;
    }
    return false;
}


