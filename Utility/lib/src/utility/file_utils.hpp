#ifndef _FILE_UTILS_H_
#define _FILE_UTILS_H_

#include <string>

// Extract the directory part from the file name
std::string FileDirFormFileName(const std::string & fileName){
    std::string::size_type slashIndex = fileName.find_last_of("/");
    std::string dir;

    if (slashIndex == std::string::npos) {
        dir = ".";
    }
    else if (slashIndex == 0) {
        dir = "/";
    }
    else {
        dir = fileName.substr(0, slashIndex);
    }
    
    return dir;
}

#endif