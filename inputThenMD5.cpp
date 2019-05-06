#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "md5.h"


int main(){
    char name[32]; //max chars after md5.
    printf("Enter your message: ");
    fgets(name, 20, stdin);  //we read max 20 chars.
    printf("Your message is: %s", name);
    std::string hashed = "a";
    // hashed = md5(hashed);
    printf("Your message after MD5: %s", name);
    return 0;
}