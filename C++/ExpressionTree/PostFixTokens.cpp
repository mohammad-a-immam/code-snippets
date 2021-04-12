//
// Created by Mohammad Asfaq Immam on 9/5/2019.
// for Data Structure UF Fall 2019
//
#include "PostFixTokens.h"
#include <stack>
#include <string>
#include <regex>


using namespace std;

PostFixTokens::PostFixTokens()
{
    //The Default Constructor. User  later sets the vector if asked
}

PostFixTokens::PostFixTokens(vector<string> inFix)
{
    inFixTokens=inFix;
}

vector<string> PostFixTokens::getInFixTokens()
{
    return inFixTokens;
}

void PostFixTokens::setInFixTokens(vector<string> inFix)
{
    inFixTokens=inFix;
}

//Returns the valie of the postFixes
vector<string> PostFixTokens::getPostFixTokens()
{
    if (!checkExpression())
        throw invalid_argument( "Infix expression Invalid" );
    else
        return postFixTokens;
}

void PostFixTokens::printInFix()
{
    for (int i=0; i<inFixTokens.size();i++)
    {
        cout<<inFixTokens[i]+"\n";
    }
}

//to Print the fixes on screen
void PostFixTokens::printPostFix()
{
    if (!checkExpression())
        throw invalid_argument("Invalid Expression");
    else {
        for (int i = 0; i < postFixTokens.size(); i++) {
            cout << i<<" "<<postFixTokens[i] << "\n";
        }
    }
}
void PostFixTokens::createPostFix()
{
    if (!checkExpression())
        throw invalid_argument( "Infix expression Invalid" );
    else {
        stack<string> operators;
        //string expression = "";
        postFixTokens.clear();

        for (int i = 0; i < inFixTokens.size(); i++) {
            auto workingToken = inFixTokens[i];       //if its not operator or () then its a operand
            if (isOperand(workingToken))
                postFixTokens.push_back(workingToken);           //add it to the expression
            else if (workingToken == "(")
                operators.push(workingToken);
            else if (workingToken == ")")             //if its close paren then we had (
            {
                while (operators.top() != "(") {
                    postFixTokens.push_back(operators.top());      //take care until you get (
                    operators.pop();
                }
                operators.pop();        //Popping out the ( without adding
            } else if (isOperator(workingToken)) {
                if (operators.empty())
                    operators.push(workingToken);       //if its empty add
                else if (OpNumber(workingToken) >
                         OpNumber(operators.top()))      //if you find greate paren then you push to stack
                    operators.push(workingToken);
                else if (operators.top() == "^" & workingToken == "^")              //if both are ^ push carat again
                    operators.push(workingToken);
                else                    //operator is close parend
                {
                    //if empty or top is lower or both ^ then stop other wise keep adding and popping
                    while (!operators.empty() && operators.top() != "(") {
                        if ((OpNumber(workingToken) <= OpNumber(operators.top()))) {
                            postFixTokens.push_back(operators.top());
                            operators.pop();
                        } else break;
                    }
                    if (workingToken != ")") {
                        operators.push(workingToken);
                    }
                    if (operators.top() == "(")
                        operators.pop();
                }
            } else        //Invalid Expression, calling printing postfix
            {
                throw invalid_argument("Infix expression Invalid");
            }
        }
        while (!operators.empty()) {
            postFixTokens.push_back(operators.top());
            operators.pop();
        }

      /*  //Time to break the expression into string of vectors//
        postFixTokens = breakExpression(expression);*/
    }

}

//METHOD TO CHECK IF IT IS OPERATOR
//Credits: Help taken from GeeksOfGreeks
bool PostFixTokens::isOperator(string input) {
    if (input=="+"||input=="-"||input=="*"||input=="%"||input=="/"||input=="^"||input=="(")
    {
        return true;
    }
    return false;
}

//METHOD FOR OPERATOR VALUE
int PostFixTokens::OpNumber(string input) {

        if (input== "+")
            return 1;
        else if (input=="-")
            return 1;
        else if (input=="*")
            return 3;
        else if (input=="%")
            return 3;
        else if (input=="/")
            return 3;
        else if (input=="^")
            return 8;
        else if (input=="(")
            return 8;
    return 0;
}
//To Check if the string is an operand

bool PostFixTokens::isOperand(string input) {

    if (input==")")
        return false;
    for (int i=0; i<input.length();i++)
    {
        if((!(input.at(i) >= '0' && input.at(i) <= '9')) && (!(input.at(i) >= 'a' && input.at(i) <= 'z')) && (!(input.at(i) >= 'A' && input.at(i) <= 'Z')))
        return false;
    }
    return true;
}

vector<string> PostFixTokens::breakExpression(string expression) {
    //Help from https://stackoverflow.com/questions/5607589/right-way-to-split-an-stdstring-into-a-vectorstring

    vector<string> results;
    int begin=0;
    int end=0;

    for (int i=0; i< expression.length(); i++)
    {
        if (expression.at(i)=='+'||expression.at(i)=='-'||expression.at(i)=='*'||expression.at(i)=='%'||expression.at(i)=='/'||expression.at(i)=='^'||expression.at(i)==' ')
        {
            end=i;
            if ((end-begin)!=0)
                results.push_back(expression.substr(begin,end-begin));
            begin=end+1;
            if (expression.at(i)!=' ')
                results.push_back(expression.substr(i,1));
        }
    }

    end=expression.length();
    results.push_back(expression.substr(begin,end-begin));

    return results;
}

bool PostFixTokens::checkExpression()
{
    stack<string> brackets;
    for (int i=0; i< inFixTokens.size(); i++)
    {

        if (inFixTokens[i]==")")
        {
           if (brackets.empty())
               return false;
           else brackets.pop();
        }
        if (isOperator(inFixTokens[i]))
        {
            if (i==0 & inFixTokens[i]!="(")
                return false;
            if (i==inFixTokens.size()-1)
                return false;
            if ((isOperator(inFixTokens[i+1]))) {
               if (inFixTokens[i+1]!="(")
                   return false;
            }
            if (inFixTokens[i]=="(") {
                brackets.push("(");
            }
        }
        else if (isOperand(inFixTokens[i])& i!=inFixTokens.size()-1)
        {
            if(!isOperator(inFixTokens[i+1])&&inFixTokens[i+1]!=")")
                return false;
        }
    }
    if (!brackets.empty())
        return false;
    return true;
}



