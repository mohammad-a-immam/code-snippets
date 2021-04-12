#include <iostream>
#include <list>
#include <regex>
#include <algorithm>
#include "PostFixTokens.h"
#include "ExpTree.h"
class ostream_suppressor {
    std::ostream &out;
    std::ostringstream buffer;
    std::streambuf *old_buffer;
public:
    ostream_suppressor(std::ostream &out) : out(out) {
        old_buffer = out.rdbuf(buffer.rdbuf());
    }
    ~ostream_suppressor() {
        out.rdbuf(old_buffer);
    }};
static const std::list<std::regex> token_types = {
        std::regex("^(-?\\d+)"),    // numbers
        std::regex("^[\\(\\)\\+\\-\\*\\/%\\^]"),    // operators
        std::regex("^[[:alpha:]]([[:alnum:]_-]*)")  // variables
         };
        std::vector<std::string> tokenize(const std::string infixExp) {
        auto tokens = std::vector<std::string>{};
        auto matches = std::smatch{};
        auto it = begin(infixExp), endIt = end(infixExp);
        while(it != endIt) {
        for(const auto &token_type: token_types) {
        if(std::regex_search(it, endIt, matches, token_type)) {
        tokens.push_back(matches[0]);               // move the iterator forward to the end of the found token
        it += matches[0].length()-1;
        break;
        }
        }
        ++it;
        }
        return tokens;
        }
        void printTokens(std::vector<std::string> &tokens) {
        if(tokens.size() == 0)
        return;
        std::cout << tokens[0];
        std::for_each(begin(tokens)+1, end(tokens), [](const auto &token) {
        std::cout << " " << token;    });
        std::cout << std::endl;}vector<int> getVariableValues() {
        std::string line;

std::getline(std::cin, line);
std::stringstream ss(line);
std::vector<int> values;
int value;
while (ss >> value) {
values.
push_back(value);
}    return
values;
}

int main() {
    cout<<"Provide Infix Exp: \n";
    std::string infixExp;
    vector<string> postFixTokensPrint;
    while (std::getline(std::cin, infixExp)) {
        auto inFixTokens = tokenize(infixExp);
        auto values = getVariableValues();
        try {
            int ans;
            std::stringstream ss;
            {
                ostream_suppressor cout_supressor(std::cout);
                ostream_suppressor cerr_supressor(std::cerr);
                PostFixTokens tokens(inFixTokens);
                tokens.createPostFix();
                auto postFixTokens = tokens.getPostFixTokens();
                postFixTokensPrint=postFixTokens;
                cout<< "PostFixTokens: \n";
                tokens.printPostFix();
                ExpTree tree;
                tree.CreateTree(postFixTokens);
                tree.inOrderTraversalandPrint(ss);
                tree.SetVariableValues(values);
                ans = tree.EvaluateTree();
            }
            cout <<"postFixTokens: \n";
            for (int i=0; i< postFixTokensPrint.size();i++)
            {
                cout<< postFixTokensPrint[i]<<"\n";
            }
            cout << ss.str() << "THE_END"<< endl<<"\n";
            cout << ans << endl;
        } catch (std::invalid_argument &e) { std::cout << "Invalid infix expression\n"; } catch (std::exception &e) {
            std::cout << "Unexpected exception thrown with message " << e.what() << "\n";
        }
    }
}