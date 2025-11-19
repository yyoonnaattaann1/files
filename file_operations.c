/*------------------------------------------------------
* Filename: file_operations.c
* Description: in this program we will write some functions that operates over files.
* Author:Yonatan shami
-------------------------------------------------------*/

/*------------------------------------------------------
* Function Name - printFile
*
* Function Purpose - void function that prints the file's text.
*
* Parameters –  [IN first_parameter - char * p] 
*
* Return Values - "hello world"
*
* Author - Yonatan Shami
-------------------------------------------------------*/

/*------------------------------------------------------
* Function Name - copyFile
*
* Function Purpose - void function that copies one file to anouter.
*
* Parameters –  [IN first_parameter - char * fro, char * des] 
*
* Return Values - ...
*
* Author - Yonatan Shami
-------------------------------------------------------*/

/*------------------------------------------------------
* Function Name - printCount
*
* Function Purpose - void function that prints the number of lines, worde and letters in the file.
*
* Parameters –  [IN first_parameter - char * fro] 
*
* Return Values - 2
                  7
                  36
*
* Author - Yonatan Shami
-------------------------------------------------------*/

/*------------------------------------------------------
* Function Name - delete_line
*
* Function Purpose - function that delete a specific line from its text.
*
* Parameters –  [IN first_parameter - char * fro, int delete_line] 
*
* Return Values - ...
*
* Author - Yonatan Shami
-------------------------------------------------------*/

/*------------------------------------------------------
* Function Name - countStr
*
* Function Purpose - void function that counts how many times a string appears in the text.
*
* Parameters –  [IN first_parameter - char * fro, char * str] 
*
* Return Values - 8
*
* Author - Yonatan Shami
-------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

static void printFile(char * p){
    int c=0;
    FILE *f= fopen(p, "r");
    if(f==NULL){
        printf("Could not open the file\n");
        fclose(f);
    }
    
    while(EOF!=(c=fgetc(f))){
        printf("%c", c);
    }
    fclose(f);
}

static void copyFile(char * fro, char * des){
    int c=0;
    FILE *f= fopen(fro, "r");
    if(f==NULL){
        printf("Could not open the file\n");
        fclose(f);
    }
    FILE *d= fopen(des, "w");/*creats a file if does not exist*/
    if(d==NULL){
        printf("Could not open the file\n");
        fclose(f);
        fclose(d);
    }
    while(EOF!=(c=fgetc(f))){
        fputc(c, d);
    }
    fclose(f);
    fclose(d);
}

static void printCount(char * fro){
    int c=0;
    long lines=0, words=0, letters=0;
    int in_word=0, in_line=0; 
    FILE *f= fopen(fro, "r");
    if(f==NULL){
        printf("Could not open the file\n");
        fclose(f);
    }
    while(EOF!=(c=fgetc(f))){
        if(isalpha((unsigned char) c)){
            letters++;
            in_line=1;
        }
        if(isspace((unsigned char) c)){/*chacing spaces*/
            if(c == '\n'){/*going to next line*/
                if(in_line){
                    lines++;
                    in_line=0;
                }
            }
            if(in_word){/*going to next word*/
                words++;
                in_word=0;
            }else{
                in_word=1;
            }
        }
    }
    if(in_word){/*adds the last word*/
        words++;
    }
    if(in_line){/*adds the lasst line*/
        lines++;
    }
    printf("the number of lines: %d\nthe number of words: %d\nthe number of letters: %d", lines, words, letters);
    fclose(f);
}

static void delete_line(char * fro, int delete_line){
    int c=0;
    int line_number=1;
    FILE *f= fopen(fro, "r");
    if(f==NULL){
        printf("Could not open the file\n");
        fclose(f);
        return;
    }
    FILE *help = fopen("help.txt", "w");/*creats text file help*/
    if(help==NULL){
        printf("Could not open the file\n");
        fclose(f);
        fclose(help);
        return;
    }

    char s[1024];/*empty char array that will get a line from the given file*/

    while(fgets(s, sizeof(s) ,f)){
        if(delete_line!=line_number){
            fputs(s, help);
        }
        line_number++;
    }
    fclose(f);
    fclose(help);

    remove(fro);/*remove the original file that contains the extra line*/
    rename("help.txt", fro);/*replace the exsisting file with the original name*/
}

void countStr(char * fro, char * str){
    int c=0;
    int counter=0;/*counter of str apperens*/
    size_t len= strlen(str);
    int i=0;/*index of the for loop*/
    FILE *f= fopen(fro, "r");
    if(f==NULL){
        printf("Could not open the file\n");
        fclose(f);
        return;
    }
    while (EOF != (c = getchar())) {
        if(c == str[0]){/*checks if the fiset letter in str matches c*/
            for(i=0; i<len; i++){/*interats over the str length*/
                if(c==str[i]){/*checks char by char*/
                    c = getchar();/*next char in the file*/
                }else{
                    break;
                }
            }
            if(i==len){/*the for loop ends and didnt break*/
                counter++;
            }
        }
    }
    printf("the number of times the string %s showed in the file is: %d", str, counter);
    fclose(f);
}


int main(){

    printFile("Document.txt");
    printf("\n");
    copyFile("Document.txt", "des.txt");
    printf("\n");
    printCount("Document.txt");
    printf("\n");
    delete_line("Document.txt", 2);
    printf("\n");
    countStr("Document.txt", "last");

    return 0;
}