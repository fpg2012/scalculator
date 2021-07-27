#include <iostream>
#include <memory>
#include <vector>
#include <cctype>
#include <sstream>
#include "token.hpp"
#include "lexer.hpp"
#include "reduce.hpp"

namespace SuperCalculator
{
	class Calculator
	{
	public:
		std::string calculate(const std::string expr)
		{
			stringstream in(expr);
			Lexer lex(in);
		    vector<shared_ptr<Token>> tokens;
		    while (!in.eof()) {
				shared_ptr<Token> tok = lex.get_next_token();
				if (tok == nullptr)
				    break;
				tokens.push_back(tok);
		    }
			tokens.push_back(shared_ptr<Token>(new Terminal_token()));
		    int last_size = 0;
		    for (int i = 0; i < 100; ++i) {
		        if (tokens.size() < 3) break;
				tokens = reduce(tokens);
			}
			stringstream out;
			if (last_size != tokens.size())
				{
					last_size = tokens.size();
			        for (auto token:tokens) {
					   	out << token->toString();
					}
					out << endl;
				}
			return out.str();
		}
	};
}
