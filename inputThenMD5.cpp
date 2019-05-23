#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "md5.h"

using std::cout;

int main(){
    char name[32]; //max chars after md5.
    printf("Enter your message: ");
    fgets(name, 20, stdin);  //we read max 20 chars.
    printf("Your message is: %s", name);
    std::string hashed = md5(name);
    const char * cstr = hashed.c_str();
    cout << "Your message after MD5: "<<  cstr ;
    return 0;
}