#include <string>

using namespace std;

class Lexer {
  public:
    Lexer(istream & in):in(in) {

    } 
	istream & in;
    bool mFirst = true;
    shared_ptr < Token > get_next_token() {
	if (mFirst) {
	    mFirst = false;
	    Terminal_token *token = new Terminal_token();
	    return shared_ptr < Token > (token);
	}
	char c = in.peek();
	while (isspace(c)) {
	    in.get();
	    c = in.peek();
	}
	if (c == EOF || c == '\0') {
	    Terminal_token *token = new Terminal_token();
	    return shared_ptr < Token > (token);
	}
	if (isdigit(c)) {
	    Number_token *tok {
	    new Number_token()};
	    in >> tok->n;
		tok->n.canonicalize();
	    return shared_ptr < Token > (tok);
	}
	Oprator_token *tok {
	new Oprator_token()};
	switch (c) {
	case '+':
	case '-':
	case '*':
	case '/':
	case '(':
	case ')':
	    tok->mOp = c;
	    in.get();
	    break;
	default:
	    tok->mType = Token::TOKEN_UNKNOWN;
	    tok->mOp = c;
	    in.get();
	    break;
	}
	return shared_ptr < Token > (tok);
    }
};

