#include <iostream>
#include <memory>
#include <vector>
#include <cctype>
#include <sstream>
//#include "native_number.hpp"

#include "token.hpp"
#include "lexer.hpp"
#include "reduce.hpp"

using namespace std;

int main()
{
    cout << "input math expr and use Ctrl-D complete expr" << endl;
    srand(time(NULL));
    Lexer lex(cin);
    vector<shared_ptr<Token>> tokens;
    while (!cin.eof()) {
    shared_ptr<Token> tok = lex.get_next_token();
        if (tok == nullptr)
            break;
        tokens.push_back(tok);
    }
    int last_size = 0;
    for (int i = 0; i < 100; ++i) {
        if (tokens.size() < 3) break;
            tokens = reduce(tokens);
            if (last_size != tokens.size())
            {
                last_size = tokens.size();
            	for (auto token:tokens) {
                	cout << token->toString();
            	}
            	cout << endl;
        	}
    }
    return 0;
}
