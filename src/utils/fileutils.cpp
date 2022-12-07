#include "fileutils.h"
#include <iostream>
#include <string.h>

std::string read_file(const char* filename){

    FILE *f = fopen(filename, "r");

    // if file was not correctly opened return an empty string
    if(!f){
        std::cerr << "Was not able to open file "<< filename << "\n"; 
        return "";
    }

    // move to the end of the file
    fseek(f,0, SEEK_END);

    // get the amount of characters in the file
    unsigned long length = ftell(f);

    // return to the beginning of the file
    fseek(f, 0, SEEK_SET);

    // allocate memory for the character array holding the contents of the file
    char * contents = new char [length + 1];

    // set the memory allocated of the content char to 0
    memset(contents, 0, length + 1);

    // copy the data to the contents array
    fread(contents, 1, length, f);

    // close the file
    fclose(f);

    // create the output data
    std::string out(contents);

    //deallocate memory
    delete[] contents;

    return out;
}