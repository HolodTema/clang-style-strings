#include <iostream>
#include <fstream>



class InputNotFoundException : std::exception {
public:
    const char * what() const noexcept override {
        return "Error: input file not found\n";
    }
};

class InvalidInputFileException : std::exception {
public:
    const char * what() const noexcept override {
        return "Error: input file must have 2 lines of text\n";
    }
};


char *task12(char *destination, const char *p, const char *q) {
    unsigned long long destinationIndex = 0;
    unsigned long long sourceIndex = 0;

    while (p[sourceIndex] != '\0' && q[sourceIndex] != '\0') {
        destination[destinationIndex] = p[sourceIndex];
        ++destinationIndex;
        destination[destinationIndex] = q[sourceIndex];
        ++destinationIndex;
        ++sourceIndex;
    }
    if (p[sourceIndex]=='\0' && q[sourceIndex] != '\0') {
        while(q[sourceIndex]!='\0') {
            destination[destinationIndex] = q[sourceIndex];
            ++destinationIndex;
            ++sourceIndex;
        }
    }
    if(q[sourceIndex] == '\0' && p[sourceIndex] !='\0') {
        while(p[sourceIndex] !='\0') {
            destination[destinationIndex] = p[sourceIndex];
            ++destinationIndex;
            ++sourceIndex;
        }
    }
    destination[destinationIndex] = '\0';
    return destination;
}

void readInputData(char * p, char * q, const char * filename, const unsigned long long maxLen) {
    std::ifstream in(filename);
    if(in.is_open()) {
        in.getline(p, maxLen);
        if(!in.eof()) {
            in.getline(q, maxLen);
        }
        else {
            in.close();
            throw InvalidInputFileException();
        }

    }
    else {
        in.close();
        throw InputNotFoundException();
    }
    in.close();
}

void writeOutputData(const char *result, const char *filename) {
    std::ofstream out;
    out.open(filename);
    out << result << std::endl;
    std::cout << result << "\n";
    out.close();
}


int main() {
    const char * FILENAME_INPUT = "input.txt";
    const char * FILENAME_OUTPUT = "output.txt";

    const unsigned long long MAX_STRING_LEN = 256;

    char p[MAX_STRING_LEN];
    char q[MAX_STRING_LEN];

    try {
        readInputData(p, q, FILENAME_INPUT, MAX_STRING_LEN);
    }
    catch (InputNotFoundException &e) {
        std::cout << e.what();
        return 1;
    }
    catch (InvalidInputFileException &e) {
        std::cout << e.what();
        return 1;
    }

    char destination[MAX_STRING_LEN * 2];
    task12(destination, p, q);
    writeOutputData(destination, FILENAME_OUTPUT);

    return 0;
}


