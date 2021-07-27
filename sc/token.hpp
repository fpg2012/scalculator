#include <string>
// #include "rational_number.hpp"
#include <gmpxx.h>
class Token {
  public:
    enum token_type { TOKEN_NUM, TOKEN_OP, TOKEN_TERM, TOKEN_UNKNOWN };
     Token(int type):mType(type) {
    } virtual std::string toString() {
	return "unknown token";
    }
    int mType;
};

class Terminal_token:public Token {
  public:
    Terminal_token():Token(Token::TOKEN_TERM) {
    } std::string toString() {
#ifdef DEBUG
	return "<term>";
#else 
	return " ";
#endif
    }
};

class Oprator_token:public Token {
  public:
    Oprator_token()
    :Token(Token::TOKEN_OP) {
    } int mOp;
    std::string toString() {
	std::string r;
#ifdef DEBUG
        r = "<op ";
	r = r + (char)mOp + ">";
#else
	r = r + (char)mOp;
#endif
	return r;
    }
};

class Number_token:public Token {
  public:
    Number_token():Token(Token::TOKEN_NUM) {}
    //Number_token(rational_number n):n(n), Token(Token::TOKEN_NUM) {}
	Number_token(mpq_class n):n(n), Token(Token::TOKEN_NUM){}
    std::string toString() {
        std::ostringstream t;
#ifdef DEBUG
        t << "<number " << n << ">";
#else
	t << "(" << n << ")";
#endif
        return t.str();
    }
    //rational_number n;
	mpq_class n;
};

