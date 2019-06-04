// C program to demonstrate use of fork(), pipe() and md5 hash strings using child process. 
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include <iostream>
#include "md5.h"

int main() 
{ 
	// We use two pipes 
	// First pipe to send input string from parent 
	// Second pipe to send md5-hashed string from child 

	int fd1[2]; // Used to store two ends of first pipe 
	int fd2[2]; // Used to store two ends of second pipe 

	char input_str[21]; 
	pid_t p; 

	if (pipe(fd1)==-1) 
	{ 
		fprintf(stderr, "Pipe Failed" ); 
		return 1; 
	} 
	if (pipe(fd2)==-1) 
	{ 
		fprintf(stderr, "Pipe Failed" ); 
		return 1; 
	} 

	printf("plain text: "); //input  
	// fgets(input_str, 21, stdin);  //we read max 20 chars. last char is end char \0 for "strings" in C.
	scanf("%20s",input_str);
	p = fork(); 

	if (p < 0)  //failure.
	{ 
		fprintf(stderr, "fork Failed" ); 
		return 1; 
	} 

	// Parent process 
	else if (p > 0) 
	{ 
		char hashed_str[100]; //we will read more than 32 characters, and then performs a check for returned length is actually 32 bytes, as md5 outputs. 

		close(fd1[0]); // Close reading end of first pipe 

		// Write input string and close writing end of first 
		// pipe. 
		write(fd1[1], input_str, strlen(input_str)+1); 
		close(fd1[1]); 

		// Wait for child to send a string 
		wait(NULL); 

		close(fd2[1]); // Close writing end of second pipe 

		// Read string from child, print it and close 
		// reading end. 
		read(fd2[0], hashed_str, 100); //we will read more than 32 characters, and then performs a check for returned length is actually 32 bytes, as md5 outputs. 
		if(strlen(hashed_str) == 32){
			// printf("My child hashed the input, he returned: %s \n", hashed_str); 
			// printf("The length of this hashed string is actually: %d\n", strlen(hashed_str));
			printf("encrypted by process %d : %s \n", p, hashed_str); 
		}
		else{
			printf("My child tried to MD5 the string but returned a string which is not 32bytes. hence md5 didn't work for him.");
		}
		close(fd2[0]); 
	} 

	// child process 
	else
	{ 
		close(fd1[1]); // Close writing end of first pipe 

		// Read a string using first pipe 
		char plaintext_str[21]; //last char is \0
		read(fd1[0], plaintext_str, 21); 

		// Hashing the string
		std::string hashed = md5(plaintext_str);
		//converting string back to c-type strings, char* .
		const char* cStringHashed = hashed.c_str();


		// Close both reading ends 
		close(fd1[0]); 
		close(fd2[0]); 

		// Write hashed string and close writing end 

		write(fd2[1], cStringHashed, strlen(cStringHashed)); 
		close(fd2[1]); 

		exit(0); 
	} 
} 
