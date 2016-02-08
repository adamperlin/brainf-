#include "bfi.h"

using namespace std;
using namespace interpreter;
std::string input;
int main(int argc, char* argv[]){
    interpreter* i = new interpreter();
    if (argv[1] == nullptr){
    std::cout << "BrainF Interpreter Running" << std::endl;
    while (std::getline(std::cin,input)){
    std::cout << "> ";
    std::getline(std::cin,input);
    i->interpret(input);
    }
    }else {
        ifstream file(argv[1]);
        stringstream buff;
        string contents;
        if (file.is_open()){
            buff << file.rdbuf();
            contents = buff.str();
            i->interpret(contents);
        }else {
            cout << "Please enter a valid file path" << endl;
            cout << "To use BF interpreter shell, provide no arguments" << endl;
        }
    }
delete i;
return 0;
}
