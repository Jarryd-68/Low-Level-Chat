#include <stdio.h>

int main(int argc, char const *argv[])
{   
    //vim is cool	
    //this program is the basics of reading and writing to the terminal
    int a, b;
    char str[15];
    printf("Enter values:  digit digit string\n");
    //To scan input remember to put & symbol before digits!
    scanf("%d %d %s", &a, &b, str);
    printf("You entered %d\t%d\t%s", a, b, str);
}

//Here is some basics of printing to stdout
/* 
%d print as decimal integer
%6d print as decimal integer, at least 6 characters wide
%f print as floating point
%6f print as floating point, at least 6 characters wide
%. 2f print as floating point, 2 characters after decimal point
%6. 2f print as floating point, at least 6 wide and 2 after decimal point
*/


