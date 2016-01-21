#include <iostream>
#include <vector>
#include <string>
#include <stack>
//BrainFuck Interpreter:
//to fix: multiple nested loops
//throwing unbalance parentheses exceptions.
using namespace std;
std::string input;
class myexception : public exception {
    virtual const char* what() const throw(){
        return "Error: UnbalanceParenthesesException";
}
}UnbalancedParenthesesException;
class interpreter {
public:
    interpreter():
        cells(30000)
    {
        this->cellptr = cells.begin();
    }

std::vector<int>::iterator cellptr;
std::vector<int> cells;
stack<vector<int>::iterator> conditionCellPtrs;
 void interpret(std::string i){
    if (checkParentheses(i)){

        for (auto iter = i.begin(); iter != i.end(); ++iter){
            switch(*iter){
            case '+':
                (*cellptr)++;
                break;
            case '-':
                (*cellptr)--;
                break;
            case '.':
                std::cout << static_cast<char>(*cellptr);
                break;
            case '>':
                ++cellptr;
                break;
            case '<':
                --cellptr;
                break;
            case '[':
                if (!*cellptr){
                   //size_t temp = (i.find(']',iter-i.begin()));
                   size_t temp = findClosing(i,iter-i.begin());
                   iter = i.begin()+temp;
                }
                break;
            case ']':
                if (*cellptr){
                   // size_t temp = (i.rfind('[',iter-i.begin()));
                   size_t temp = findOpening(i, iter-i.begin());
                    iter = i.begin()+temp;

                }
                break;

            case 'q':
                exit(0);
            case ' ':
                break;
            case ',':
                cout << "?: ";
                cin >> *cellptr;
                break;
            default:
                std::cout << "Oops, didn't get that. Check your syntax" << std::endl;
            }
        }
    }else {
        try {
        throw UnbalancedParenthesesException;
        }catch (exception& e){
            cout << e.what() << endl;
        }
    }
}
bool checkParentheses(string str) {
stack<char> s;
    for (string::iterator it = str.begin(); it != str.end(); ++it){
        if (*it == '[')
        {
            s.push(*it);
        }else if (*it == ']'){
            if (s.top() == '['){
                s.pop();
            }else {
                return false;
            }
        }
    }
    return s.empty() ? true : false;
}

int findClosing (string text, size_t pos){
	size_t close = pos;
	int counter = 1;
	while (counter > 0){
		close++;
		char ch = text[close];
		if (ch == '['){
			counter++;
		}else if (ch == ']'){
			counter--;
		}
	}
	return close;
}
int findOpening (string text, size_t pos){
	int openpos = pos;
	int counter = 1;
	while (counter > 0){
		openpos--;
		char ch = text[openpos];
		if (ch == '['){
			counter--;
		}else if (ch == ']'){
			counter++;
		}
	}
	return openpos;
}
};
int main(){
      interpreter* i = new interpreter();
    std::cout << "BrainFuck Interpreter Running" << std::endl;
    while (std::getline(std::cin,input)){
    std::cout << "> ";
    std::getline(std::cin,input);
    //i->cells.push_back(1);
    //std::cout << i->cells[0] << std::endl;
    i->interpret(input);

    }
}


