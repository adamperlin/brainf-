#include "bfi.h"

using namespace std;
using namespace bfi;
std::string input;
int main(int argc, char* argv[]){
    interpreter* i = new interpreter();
    if (argv[1] == nullptr){
    std::cout << "BrainF Interpreter Running" << std::endl;
    while (std::getline(std::cin,input)){
    std::cout << "> ";
    std::getline(std::cin,input);
    string& ref = input;
    i->interpret(ref);
    }

    }else {
        ifstream file(argv[1]);
        stringstream buff;
        string contents;
        if (file.is_open()){
            buff << file.rdbuf();
            contents = buff.str();
            string& ref = contents;
            i->interpret(ref);
        }else {
             if(static_cast<string>(argv[1]) == "-v"){
                version();
                }else if (static_cast<string>(argv[1]) == "-h"){
                options();
                }else{
                cout << "Please enter a valid file path" << endl;
                }

        }
    }
delete i;
return 0;
}
