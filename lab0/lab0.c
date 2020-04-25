#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<ctype.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

const char *VALUES[] = { 
                        "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL",
						"BS", "HT", "LF", "VT", "FF", "CR", "SO", "SI", "DLE",
						"DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB", "CAN",
						"EM", "SUB", "ESC", "FS", "GS", "RS", "US", "SPACE" };
const char*DEL = "DEL";

void calc(char* val){ 
	char binary[9];
	int decimal = 0;
	strcpy(binary, val);		
   	int sum = 0;
   	int size = strlen(binary);
	if(size < 9){//Padding
		for(int j = size; j < 9; j++){
         	binary[j] = '0';
        }
        binary[8] = '\0';
   	}
	for(int i = 0; i < 8; i++){
		sum +=(int)binary[i];
	}
	for(int i = 1; i < 8; i++){
		decimal += (binary[i]-'0') << (7-i);
    }
	char ascii = (char)decimal;
	if((ascii >= 0 && ascii <= 32)){   
		printf("%s\t%s\t%i\t",binary, VALUES[decimal], decimal);
    }else if(ascii == 127){
    }else{
		printf("%s\t%c\t%i\t",binary, ascii, decimal);
    }
	if(sum % 2 == 0){
		printf("EVEN\n");
    }else{
		printf("ODD\n");
    }	     
}

int main(int argc, char** argv){
	if(argc < 2){
		printf("No Input");	
		return 0;
	}
	char c;
	int pos = 0;
	char line[9];
	int startPos = 1;	
	if(argv[1][0] == '-' || argv[1][0] == '0' || argv[1][0] == '1'){

		if(argc == 2 && argv[1][0] == '-'){
			printf("Wrong input!\n");
			return 0;
		}
		if(argv[1][0] == '-'){
			startPos = 2;
        }
		for(int i = startPos; i < argc; i++){
		 	for(unsigned int j =0; j < strlen(argv[i]); j++){
		 		if(argv[i][j] != '0' && argv[i][j] != '1'){
		 			printf("Wrong input!\n");
		 			return 0;
		 		}
		 	}
		}
		printf("\nOriginal ASCII    Decimal  Parity\n");
		printf(  "-------- -------- -------- -------- \n");
		for(int i = startPos ; i < argc; i++){
			calc(argv[i]);
		}
	}else if(argc == 2 && isascii(argv[1][0]) && (argv[1][0] >= 97 && argv[1][0] <= 122)){
		if(open(argv[1], O_RDONLY) == -1){
			printf("Cant Open File");
        }
		int fd = open(argv[1], O_RDONLY);
		while(read(fd, &c, 1) != 0 ){
			if (c != '0' && c != '1' && c != ' '){
				printf("Your file had invalid data\n");
				return 0;
			}
		}
        printf("\nOriginal ASCII    Decimal  Parity\n");
		printf(  "-------- -------- -------- -------- \n");
		fd = open(argv[1], O_RDONLY);
		while(read(fd, &c, 1) != 0 ){
			if(c == ' ' ){
				line[pos] = '\0'; 			
				calc(line);
				pos = 0;
			}else{
				line[pos] = c;
				pos++;
			}
		}
			line[pos] = '\0';
			calc(line);
	}else{ 
		printf("Invalid Input");
    }
	return 0;
}
