#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if(argc != 2){
        printf("No argument\n");
        return 0;
    }
    const int pgSize = 4096;
    unsigned int address, pgNum, offset;
    address = atoi(argv[1]);
    pgNum = address / pgSize;
    offset = address % pgSize;
    printf("The address %s contains:\n", argv[1]); 
    printf("page number = %d\n", pgNum);
    printf("offset = %d\n", offset);
    return 0;
}
