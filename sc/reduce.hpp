#include <vector>

using namespace std;

class ReduceRule {
public:
    int mTokenNum;
    ReduceRule() {}
	ReduceRule(int n):mTokenNum(n) {}
    virtual bool fixRule(vector < shared_ptr < Token >> &tokens) {
		cout << "ReduceRule fun" << endl;
		return false;
    }
    virtual vector<shared_ptr<Token>> reduce(vector<shared_ptr<Token >> &tokens) {
	return tokens;
    }
};

class SubReduceRule:public ReduceRule {
public:
    SubReduceRule():ReduceRule(5) {
    } virtual bool fixRule(vector < shared_ptr < Token >> &tokens) {
	Oprator_token *t0 = (Oprator_token *) tokens[0].get();
	Number_token *t1 = (Number_token *) tokens[1].get();
	Oprator_token *t2 = (Oprator_token *) tokens[2].get();
	Number_token *t3 = (Number_token *) tokens[3].get();
	Oprator_token *t4 = (Oprator_token *) tokens[4].get();
	bool b0 = !(t0->mType == Token::TOKEN_OP 
			&& (t0->mOp == '*' || t0->mOp == '/' || t0->mOp == '-')
			|| t4->mType == Token::TOKEN_OP
			&& (t4->mOp == '*' || t4->mOp == '/')
		);
	bool b1 = t1->mType == Token::TOKEN_NUM
	    && t3->mType == Token::TOKEN_NUM
	    && t2->mType == Token::TOKEN_OP && t2->mOp == '-';
	return b0 && b1;
    }
    vector < shared_ptr < Token >> reduce(vector < shared_ptr <
					  Token >> &tokens) {
	vector < shared_ptr < Token >> r;
	r.push_back(tokens[0]);
	auto & n = ((Number_token *) tokens[1].get())->n;
	auto & m = ((Number_token *) tokens[3].get())->n;
	r.push_back(shared_ptr < Token > (new Number_token(n - m)));
	r.push_back(tokens[4]);
	return r;
    }
};

class AddReduceRule:public ReduceRule {
  public:
    AddReduceRule():ReduceRule(5) {
    } virtual bool fixRule(vector < shared_ptr < Token >> &tokens) {
	Oprator_token *t0 = (Oprator_token *) tokens[0].get();
	Number_token *t1 = (Number_token *) tokens[1].get();
	Oprator_token *t2 = (Oprator_token *) tokens[2].get();
	Number_token *t3 = (Number_token *) tokens[3].get();
	Oprator_token *t4 = (Oprator_token *) tokens[4].get();
	bool b0 = !(t0->mType == Token::TOKEN_OP 
			&& (t0->mOp == '*' || t0->mOp == '/' || t0->mOp == '-')
			|| t4->mType == Token::TOKEN_OP
			&& (t4->mOp == '*' || t4->mOp == '/')
		);
	bool b1 = t1->mType == Token::TOKEN_NUM
	    && t3->mType == Token::TOKEN_NUM
	    && t2->mType == Token::TOKEN_OP && t2->mOp == '+';
	return b0 && b1;
    }
    vector < shared_ptr < Token >> reduce(vector < shared_ptr <
					  Token >> &tokens) {
	vector < shared_ptr < Token >> r;
	r.push_back(tokens[0]);
	auto & n = ((Number_token *) tokens[1].get())->n;
	auto & m = ((Number_token *) tokens[3].get())->n;
	r.push_back(shared_ptr < Token > (new Number_token(n + m)));
	r.push_back(tokens[4]);
	return r;
    }
};

class MulReduceRule:public ReduceRule {
  public:
    MulReduceRule():ReduceRule(4) {
    } virtual bool fixRule(vector < shared_ptr < Token >> &tokens) {
	Oprator_token *t0 = (Oprator_token *) tokens[0].get();
	Number_token *t1 = (Number_token *) tokens[1].get();
	Oprator_token *t2 = (Oprator_token *) tokens[2].get();
	Number_token *t3 = (Number_token *) tokens[3].get();
	bool b0 = t0->mType != Token::TOKEN_OP
	    || t0->mOp == '+' || t0->mOp == '-' || t0->mOp == '*';
	bool b1 = t1->mType == Token::TOKEN_NUM
	    && t3->mType == Token::TOKEN_NUM
	    && t2->mType == Token::TOKEN_OP && t2->mOp == '*';
	return b0 && b1;
    }
    vector < shared_ptr < Token >> reduce(vector < shared_ptr <
					  Token >> &tokens) {
	vector < shared_ptr < Token >> r;
	r.push_back(tokens[0]);
	auto & n = ((Number_token *) tokens[1].get())->n;
	auto & m = ((Number_token *) tokens[3].get())->n;
	r.push_back(shared_ptr < Token > (new Number_token(n * m)));
	return r;
    }
};

class DivReduceRule:public ReduceRule {
  public:
    DivReduceRule():ReduceRule(3) {}
   	virtual bool fixRule(vector<shared_ptr<Token>> &tokens) {
		Number_token *t0 = (Number_token *) tokens[0].get();
		Oprator_token *t1 = (Oprator_token *) tokens[1].get();
		Number_token *t2 = (Number_token *) tokens[2].get();
		return t0->mType == Token::TOKEN_NUM
			&& t1->mType == Token::TOKEN_OP
			&& t1->mOp == '/' && t2->mType == Token::TOKEN_NUM;
    }
    vector<shared_ptr<Token>> reduce(
			vector<shared_ptr<Token>> &tokens) {
		vector<shared_ptr<Token>> r;
		auto & n = ((Number_token *) tokens[0].get())->n;
		auto & m = ((Number_token *) tokens[2].get())->n;
		r.push_back(shared_ptr<Token>(new Number_token(n / m)));
		return r;
    }
};
class BracketReduceRule:public ReduceRule {
  public:
    BracketReduceRule():ReduceRule(3) {
    } virtual bool fixRule(vector<shared_ptr<Token>> &tokens) {
	Oprator_token* t0 = (Oprator_token*)tokens[0].get();
	Number_token* t1 = (Number_token*)tokens[1].get();
	Oprator_token* t2 = (Oprator_token*)tokens[2].get();
	return t0->mType == Token::TOKEN_OP && t0->mOp == '('
	    && t1->mType == Token::TOKEN_NUM
	    && t2->mType == Token::TOKEN_OP && t2->mOp == ')';
    }
    vector<shared_ptr<Token>> reduce(vector<shared_ptr<Token>> &tokens) {
		vector<shared_ptr<Token>> r;
		r.push_back(tokens[1]);
		return r;
    }
};

vector<shared_ptr<Token>>
reduce(
		vector<shared_ptr<Token>> &tokens)
{
    shared_ptr<MulReduceRule> rule(new MulReduceRule);
    vector<shared_ptr<ReduceRule>> rules;
    rules.push_back(rule);
    rules.push_back(shared_ptr<DivReduceRule> (new DivReduceRule));
    rules.push_back(shared_ptr<AddReduceRule> (new AddReduceRule));
    rules.push_back(shared_ptr<SubReduceRule> (new SubReduceRule));
    rules.push_back(shared_ptr<BracketReduceRule> (new BracketReduceRule));
    int x = rand() % rules.size();
    int tokenNum = rules[x]->mTokenNum;
    if (tokens.size() < tokenNum)
		return tokens;

    for (int start = 0; start <= tokens.size() - tokenNum; ++start) {
		vector<shared_ptr<Token>> t;
		for (int i = 0; i < tokenNum; ++i)
			t.push_back(tokens[i + start]);
		if (rules[x]->fixRule(t)) {
			vector<shared_ptr<Token>> r;
			for (int i = 0; i < start; ++i)
				r.push_back(tokens[i]);
			t = rules[x]->reduce(t);
			for (int i = 0; i < t.size(); ++i)
				r.push_back(t[i]);
			for (int i = start + tokenNum; i < tokens.size(); ++i)
				r.push_back(tokens[i]);
			return r;
		}
    }
    return tokens;
}

