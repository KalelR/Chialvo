#ifndef TOSTRING_H
#define TOSTRING_H

#include <cstdlib>
#include <string>
#include <sstream>

std::string toString(int n) {
	std::ostringstream ss;
	ss << n;
	return ss.str();	
}

std::string toString(float f) {
	std::ostringstream ss;
	ss << f;
	return ss.str();	
}

std::string toString(double d) {
	std::ostringstream ss;
	ss << d;
	return ss.str();	
}

std::string toString(const char *c_str) {
	std::ostringstream ss;
	ss << c_str;
	return ss.str();	
}



int strToInt(std::string str, int base=0) {
    int result;
    char *end;
    long l = strtol(str.c_str(), &end, base);

    if (*(str.c_str()) == '\0' || *end != '\0') {
        std::cout << "Erro convertendo str \'" << str << "\' to int!\n";
        return -1;
    }

    result = l;

    return result;
}

int strToInt(char const *cstr, int base=0) {
    int result;
    char *end;
    long l = strtol(cstr, &end, base);

    if (*cstr == '\0' || *end != '\0') {
        std::cout << "Erro convertendo cstr \'" << cstr << "\' to int!\n";
        return -1;
    }

    result = l;

    return result;
}


float strToFloat(std::string str) {
    double result;
    char *end;

    result = strtod(str.c_str(), &end);

    if (*(str.c_str()) == '\0' || *end != '\0') {
        std::cout << "Erro convertendo str \'" << str << "\' to float!\n";
        return -1;
    }

    return result;
}

float strToFloat(char const *cstr) {
    double result;
    char *end;
   
	result = strtod(cstr, &end);

    if (*cstr == '\0' || *end != '\0') {
        std::cout << "Erro convertendo cstr \'" << cstr << "\' to float!\n";
        return -1;
    }

    return result;
}

#endif