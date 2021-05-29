/*
Name: Jiten Sidhpura
Class: TE COMPS
Batch: D
UID: 2018140051
Roll No. 57
Experiment No. 4b  - To develop lexical analyzer specification for Pascal language with a C program
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

 // represents the number of lexumes in the Symbol Table
int unique = 0;

// represents the number of lexumes which are keywords and identifiers
int only_keyword_and_id = 0;

// 0 is the initial state and is the global variable
int state = 0;

// to store sequence of characters in the memory
char buffer[100];

// to store current index of the buffer
int buffer_index = 0;

// Represents the character which is read
char current_character;

int position;

// Implementation of Symbol table with the help of a struct
struct SymbolTable{
    char type[100];
    char value[100];
};

// File pointer 
FILE *fp = NULL;

// Array to store lexumes
struct SymbolTable symboltable[1000];

// To reset the state
void reset_state(){
    strcpy(buffer,"");
    buffer_index = 0;
    state = 0;
}

// To check if character is initial part of operator
bool starts_with_operator(char a){
    
    if(a == '>' || a == '<' || a == ':' || a == '.'){
        return true;
    }

    return false;
}

// To check if character is delimiter
bool isdelimiter(char a){

    if(a == ';' || a == ' ' || a == ',' || a == ')' || a == '(' || a == '[' || a == ']'){
        return true;
    } 

    return false;
}

// To check if character is arithmetic operator
bool isarithmeticoperator(char a){
    if(a == '+' || a == '-' || a == '*') return true;

    return false;
} 

// To push value inside the symbol table
int push_into_symbol_table(char type[]){
    int position = 0;

    for(int i=0;i<unique;i++){
        if(strcmp(buffer,symboltable[i].value) == 0){
            return i;
        }
    }

    if(strcmp(type,"keyword") == 0 || strcmp(type,"id") == 0){
        only_keyword_and_id++;
    }

    strcpy(symboltable[unique].type,type);
    strcpy(symboltable[unique].value,buffer);
    
    unique++;

    return (unique-1);
}

// To print the symbol table
void print_symbol_table(){
    
    printf("\n");
    printf("\n");
    printf("SYMBOL TABLE FOR THE GIVEN PROGRAM \n\n");
    printf("\n");

    for(int i=0;i<unique;i++){
        printf("%s\t\t%s\n",symboltable[i].type,symboltable[i].value);
    }

    printf("\n");
    printf("Number of unique keywords and idenitifiers ==> %d\n\n",only_keyword_and_id);
    printf("END OF THE SYMBOL TABLE \n\n");

}
 
// To print the symbol table keywords and indentifiers
void print_symbol_table_for_keyword_and_identifiers(){

    printf("\n");
    printf("\n");
    printf("SYMBOL TABLE FOR THE GIVEN PROGRAM \n\n");
    printf("\n");

    for(int i=0;i<unique;i++){

        if(strcmp("keyword",symboltable[i].type) == 0 || strcmp("id",symboltable[i].type) == 0){
            printf("%s\t\t%s\n",symboltable[i].type,symboltable[i].value);
        }
    }

    printf("\n");
    printf("Number of unique keywords and idenitifiers ==> %d\n\n",only_keyword_and_id);
    printf("END OF THE SYMBOL TABLE \n\n");

}

// states 5 and 6 are final states
// states [1-4] are non final states
void check_for_operator(){
    while(1){
        switch(state){
            case 0:

                if(current_character == '<'){
                    state = 1;
                    buffer[buffer_index++] = current_character;
                }

                else if(current_character == '>'){
                    state = 2;
                    buffer[buffer_index++] = current_character;
                }

                else if(current_character == ':'){
                    state = 3;
                    buffer[buffer_index++] = current_character;
                }

                else if(current_character == '.'){
                    state = 4;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    reset_state();
                    return;
                }
            break;

            case 1:
                current_character = tolower(fgetc(fp));

                if(current_character == '>' || current_character == '='){
                    buffer[buffer_index++] = current_character;
                    state = 5;
                }

                else{
                    state = 6;
                }
            break;

            case 2:
                current_character = fgetc(fp);

                if(current_character == '='){
                    state = 5;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 6;
                }
            break;
            
            case 3:
                current_character = fgetc(fp);

                if(current_character == '='){
                    state = 5;
                    buffer[buffer_index++] = current_character;
                }

                //should not exist I guess 
                else{
                    state = 6;
                }
            break;

            case 4:
                current_character = fgetc(fp);

                if(current_character == '.'){
                    state = 5;
                    buffer[buffer_index++] = current_character;
                }

                //should not exist I guess 
                else{   
                    reset_state();
                    return;
                }
            break;
  
            case 5:
                buffer[buffer_index++] = '\0';
                position = push_into_symbol_table("operator");
                printf("< %s , %d >\n",symboltable[position].value,position);
                reset_state();
                return;
            break;

            case 6:
                buffer[buffer_index++] = '\0';

                position = push_into_symbol_table("operator");
                printf("< %s , %d >\n",symboltable[position].value,position);

                reset_state();
                return;
            break;
        }
    }
}

// States 45 and 46 are final states
// 7-44 are non-final states 
void check_for_keyword(){
    while(current_character != EOF){
        switch(state){

            case 7:

                if(current_character == 'a'){
                    state = 48;
                    buffer[buffer_index++] = current_character;
                }

                else if(current_character == 'b'){
                    state = 8;
                    buffer[buffer_index++] = current_character;
                }

                else if(current_character == 'd'){
                    state = 12;
                    buffer[buffer_index++] = current_character;
                }

                else if(current_character == 'e'){
                    state = 13;
                    buffer[buffer_index++] = current_character;
                }

                else if(current_character == 'f'){
                    state = 17;
                    buffer[buffer_index++] = current_character;
                }

                else if(current_character == 'i'){
                    state = 19;
                    buffer[buffer_index++] = current_character;
                }

                else if(current_character == 'p'){
                    state = 25;
                    buffer[buffer_index++] = current_character;
                }

                else if(current_character == 't'){
                    state = 31;
                    buffer[buffer_index++] = current_character;
                }

                else if(current_character == 'u'){
                    state = 34;
                    buffer[buffer_index++] = current_character;
                }

                else if(current_character == 'o'){
                    state = 47;
                    buffer[buffer_index++] = current_character;    
                }

                else if(current_character == 'v'){
                    state = 37;
                    buffer[buffer_index++] = current_character;
                }

                else if(current_character == 'w'){
                    state = 39;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 8:
                current_character = tolower(fgetc(fp));

                if(current_character == 'e'){
                    state = 9;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }

            break;

            case 9:
                current_character = tolower(fgetc(fp));

                if(current_character == 'g'){
                    state = 10;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 10:
                current_character = tolower(fgetc(fp));

                if(current_character == 'i'){
                    state = 11;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 11:
                current_character = tolower(fgetc(fp));

                if(current_character == 'n'){
                    state = 45;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 12:
                current_character = tolower(fgetc(fp));

                if(current_character == 'o'){
                    state = 45;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 13:
                current_character = tolower(fgetc(fp));

                if(current_character == 'l'){
                    state = 14;
                    buffer[buffer_index++] = current_character;
                }

                else if(current_character == 'n'){
                    state = 16;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 14:
                current_character = tolower(fgetc(fp));

                if(current_character == 's'){
                    state = 15;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 15:
                current_character = tolower(fgetc(fp));

                if(current_character == 'e'){
                    state = 45;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 16:
                current_character = tolower(fgetc(fp));

                if(current_character == 'd'){
                    state = 45;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 17:
                current_character = tolower(fgetc(fp));

                if(current_character == 'o'){
                    state = 18;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 18:
                current_character = tolower(fgetc(fp));

                if(current_character == 'r'){
                    state = 45;
                    buffer[buffer_index++] = current_character;
                }
                else{
                    state = 46;
                }
            break;

            case 19:
                current_character = tolower(fgetc(fp));

                if(current_character == 'f'){
                    state = 45;
                    buffer[buffer_index++] = current_character;
                }

                else if(current_character == 'n'){
                    state = 20;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 20:
                current_character = tolower(fgetc(fp));

                if(current_character == 't'){
                    state = 21;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;
        
            case 21:
                current_character = tolower(fgetc(fp));

                if(current_character == 'e'){
                    state = 22;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 22:
                current_character = tolower(fgetc(fp));

                if(current_character == 'g'){
                    state = 23;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 23:
                current_character = tolower(fgetc(fp));

                if(current_character == 'e'){
                    state = 24;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 24:
                current_character = tolower(fgetc(fp));

                if(current_character == 'r'){
                    state = 45;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 25:
                current_character = tolower(fgetc(fp));

                if(current_character == 'r'){
                    state = 26;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 26:
                current_character = tolower(fgetc(fp));

                if(current_character == 'o'){
                    state = 27;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 27:
                current_character = tolower(fgetc(fp));

                if(current_character == 'g'){
                    state = 28;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 28:
                current_character = tolower(fgetc(fp));

                if(current_character == 'r'){
                    state = 29;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 29:
                current_character = tolower(fgetc(fp));

                if(current_character == 'a'){
                    state = 30;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 30:
                current_character = tolower(fgetc(fp));

                if(current_character == 'm'){
                    state = 45;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 31:
                current_character = tolower(fgetc(fp));

                if(current_character == 'h'){
                    state = 32;
                    buffer[buffer_index++] = current_character;
                }

                else if(current_character == 'o'){
                    state = 45;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 32:
                current_character = tolower(fgetc(fp));

                if(current_character == 'e'){
                    state = 33;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 33:
                current_character = tolower(fgetc(fp));

                if(current_character == 'n'){
                    state = 45;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 34:
                current_character = tolower(fgetc(fp));

                if(current_character == 's'){
                    state = 35;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 35:
                current_character = tolower(fgetc(fp));

                if(current_character == 'e'){
                    state = 36;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 36:
                current_character = tolower(fgetc(fp));

                if(current_character == 's'){
                    state = 45;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 37:
                current_character = tolower(fgetc(fp));

                if(current_character == 'a'){
                    state = 38;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 38:
                current_character = tolower(fgetc(fp));

                if(current_character == 'r'){
                    state = 45;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 39:
                current_character = tolower(fgetc(fp));

                if(current_character == 'r'){
                    state = 40;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 40:
                current_character = tolower(fgetc(fp));

                if(current_character == 'i'){
                    state = 41;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 41:
                current_character = tolower(fgetc(fp));

                if(current_character == 't'){
                    state = 42;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 42:
                current_character = tolower(fgetc(fp));

                if(current_character == 'e'){
                    state = 43;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 43:
                current_character = tolower(fgetc(fp));

                if(current_character == 'l'){
                    state = 44;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 44:
                current_character = tolower(fgetc(fp));

                if(current_character == 'n'){
                    state = 45;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 45:
                current_character = tolower(fgetc(fp));

                if(isdigit(current_character) || isalpha(current_character)){
                    state = 46;
                }

                else{
                
                buffer[buffer_index++] = '\0';

                position = push_into_symbol_table("keyword");
                printf("< %s , %d >\n",symboltable[position].value,position);
                reset_state();
                return;
                }
            break; 

            case 46:
                
                if(isdigit(current_character) || isalpha(current_character)){
                    buffer[buffer_index++] = current_character;
                    state = 46;
                }
            
                if(isdelimiter(current_character) || starts_with_operator(current_character) || isarithmeticoperator(current_character) || current_character == '\''){
                    buffer[buffer_index++] = '\0';
    
                    position = push_into_symbol_table("id");
                    printf("< %s , %d >\n",symboltable[position].value,position);
                    reset_state();
                    return;
                }

                current_character = tolower(fgetc(fp));
            break;

            case 47:

                current_character = tolower(fgetc(fp));

                if(current_character == 'f'){
                    state = 45;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 48:
                current_character = tolower(fgetc(fp));

                if(current_character == 'r'){
                    state = 49;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 49:
                current_character = tolower(fgetc(fp));

                if(current_character == 'r'){
                    state = 50;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }
            break;

            case 50:
                current_character = tolower(fgetc(fp));

                if(current_character == 'a'){
                    state = 51;
                    buffer[buffer_index++] = current_character;
                }
                else{
                    state = 46;
                }
            break;

            case 51:
                current_character = tolower(fgetc(fp));

                if(current_character == 'y'){
                    state = 45;
                    buffer[buffer_index++] = current_character;
                }

                else{
                    state = 46;
                }

            break;
    }
}

}

// 50 is the final state
// 48 and 49 are non final states
void check_for_strings(){
    while(1){
        switch(state){
            case 48:

                if(current_character == '\''){
                    state = 49;
                } 
            break;               
            
            case 49:
                current_character = tolower(fgetc(fp));

                if(current_character == '\''){
                    state = 50;
                }

                else{
                    state = 49;
                    buffer[buffer_index++] = current_character;
                }
            break;

            case 50:
                buffer[buffer_index++] = '\0';

				position = push_into_symbol_table("string");
                printf("< %s , %d >\n",symboltable[position].value,position);
                reset_state();
                current_character = tolower(fgetc(fp));
                return;
            break;
        }
    }
}

// State 53 is final state
// 51-52 are non-final states 
void check_for_number(){
    while(1){
        switch(state){
            case 51:
                if(isdigit(current_character)){
                    buffer[buffer_index++] = current_character;
                    state = 52;
                }

            break;

            case 52:
                current_character = tolower(fgetc(fp));

                if(isdigit(current_character)){
                    state = 52;
                    buffer[buffer_index++] = current_character;
                }  

                else{
                    state = 53;
                }         
            break;

            case 53:
                buffer[buffer_index++] = '\0';

                position = push_into_symbol_table("numbers");
                printf("< %s , %d >\n",symboltable[position].value,position);
                reset_state();
                return;
            break;
        }
    }
}

int main(){

    fp = fopen("sort.pas","r");

    current_character = tolower(fgetc(fp));

    while(current_character != EOF){

        if(starts_with_operator(current_character)){
            state = 0;
            check_for_operator();
        }   

        if(isalpha(current_character)){
            state = 7;
            check_for_keyword();
        }

        if(current_character == '\''){
            state = 48;
            check_for_strings();
        }

        if(isdigit(current_character)){
            state = 51;
            check_for_number();
            continue;
        }

        current_character = tolower(fgetc(fp));
    }

    fclose(fp);

    if(strcmp("",buffer) != 0){
        position = push_into_symbol_table("id");
        printf("< %s , %d >\n",symboltable[position].value,position);
        reset_state();
    }

    print_symbol_table();

    print_symbol_table_for_keyword_and_identifiers();

    return 0;
}  