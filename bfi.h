#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include <sstream>
#ifndef BFI_H
#define BFI_H
using namespace std;
namespace bfi {
double bfiversion = 1.0;

inline extern void version(){
    cout << "bfi v. " << version << endl;
}
inline extern void options() {
    cout << "bfi [options] -v -h" << endl;
    cout << "bfi [filepath]" << endl;
    cout << "bfi [noargs] (for interactive interpreter)" << endl;
}
  class myexception : public exception {
      virtual const char* what() const throw(){
          return "Error: UnbalancedParenthesesException";
        }
  }UnbalancedParenthesesException;

  class interpreter {
      public:
          interpreter():
              cells(30000)
          {
              this->cellptr = cells.begin();
              this->vecptr = &cells;
          }
        virtual ~interpreter(){}
      std::vector<int>::iterator cellptr;
      std::vector<int> cells;
      vector<int>* vecptr;
       void interpret(std::string& i){
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
                      //std::cout << static_cast<char>(*cellptr);
                      cout << static_cast<char>(*cellptr);
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
                       *cellptr = static_cast<int>(getchar());
                      break;
                  default:
                     break;
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
      bool checkParentheses(string& str) {
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
      int findClosing (string& text, size_t pos){
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
      int findOpening (string& text, size_t pos){
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
  }; // end class interpreter
}//end namespace bfi
#endif
