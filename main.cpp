

#include "calculator.hpp"

int main(int argc, char *argv[]) {
    std::string filename, line;
    std::cout << "Enter a file: ";
    std::cin >> filename;
    std::ifstream file(filename);   //Opens file
    if (!file.is_open()) {
        std::cerr << "Cannot open.\n";
        return 1;
    }
    while (std::getline(file, line)) {
        if (validate_number(line)) { //Check for validity
            parse_number(line); //If valid, calculate accordingly
        } else {
            std::cout << line << " is an invalid num" << "\n";
        }
    }
    
    file.close();
    return 0;
}
