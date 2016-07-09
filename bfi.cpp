#include "bfi.h"
#include <readline/readline.h>
#include <readline/history.h>


using namespace std;
using namespace bfi;
//std::string input;

void mainloop(void);
void interpretfile(std::string);
interpreter* i = new interpreter();
int main(int argc, char* argv[]){
    if (argv[1] == nullptr){
      mainloop();
    }else if(static_cast<std::string>(argv[1]) == "-v"){
         version();
    }else if (static_cast<string>(argv[1]) == "-h"){
         options();
    }else {
      interpretfile(argv[1]);
    }
delete i;
return 0;
}

void mainloop(){
  cout << "bfi version ";
  version();
  std::string lineStr;
  char *line;
  const char *prompt = "bfi> ";
  do {
    line = readline(prompt);
    lineStr = std::string(line);
    i->interpret(lineStr);
  }while(line);
}

void interpretfile(std::string filename){
  ifstream file(filename);
  stringstream buff;
  string contents;
  if (file.is_open()){
      buff << file.rdbuf();
      contents = buff.str();
      i->interpret(contents);
  }else {
      cout << "Error: Invalid File Path" << endl;
  }
}
