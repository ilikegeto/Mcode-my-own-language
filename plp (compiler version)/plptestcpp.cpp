#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "PipaCompile.cpp"

int main(int argc, char* argv[]){
    if (argc < 2){
        std::cout << "use command \".\\plptestcpp <filename.plp>\"\n";
        return 1;
    }
    std::string filelocation = argv[1];
    std::ifstream file(filelocation);
    if (!file.is_open()){
        std::cout << "file not found ->" << filelocation <<"\n";
        return 1;
    }
    std::string pipalangcode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    std::vector<Token> tokens = Tokenize(pipalangcode);
    parser parserInstance(tokens);
    std::unique_ptr<ProgramNode> ast = parserInstance.parseProgram();
    codeGenerator generator;
    generator.generate(ast.get(), "output_pipalang.cpp");

    std::string filename = filelocation;
    size_t lastdot = filename.find_last_of(".");
    if (lastdot != std::string::npos){filename = filename.substr(0, lastdot);}
    std::string runproject = ".\\" + filename + ".exe";
    std::string command = "g++ output_pipalang.cpp -o " + filename + ".exe";
    std::cout << "compiling please wait around 5 years...\n";
    int compileResult = std::system(command.c_str());
    if (compileResult == 0){
        std::cout << "run your code...........\n";
        std::system(runproject.c_str());
    } else {std::cout << "can't run your code :(\n";}
    return 0;
}