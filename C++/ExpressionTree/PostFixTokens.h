//
// Created by ashim on 9/5/2019.
//
//
//  PostFixTokens.h
//
//
//  Created by Resch,Cheryl on 6/26/19.
//

#ifndef PostFixTokens_h
#define PostFixTokens_h
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class PostFixTokens {
public:
    PostFixTokens();
    PostFixTokens(vector<string> inFix);
    ~PostFixTokens() {};

    vector<string> getPostFixTokens();
    vector<string> getInFixTokens();
    void setInFixTokens(vector<string> inFix);
    void printPostFix();
    void printInFix();
    void createPostFix();



private:
    vector<string> inFixTokens;
    vector<string> postFixTokens;

    bool isOperator(string input);
    bool isOperand(string input);
    int OpNumber(string input);
    bool checkExpression();

};


#endif /* PostFixTokens_h */
