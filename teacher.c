#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//https://www.liquidweb.com/kb/new-user-tutorial-basic-shell-commands/

char name[20];

void checkInput(char desired[]){
    char inputted[100];
    fgets(inputted, 100, stdin);
    while(strcmp(desired,inputted) != 0){
        printf("Not quite right, please try again\n");
        fgets(inputted, 100, stdin);
    }
}

void man(){
    char *const cmdList[] = {"man", "man", NULL};
    char str[100];
    char c;
    printf("We will start by looking at the man command. This command pulls up a manual with information on ");
    printf("using various commands. %s, let's start with the basic command, please type in man man:\n",name);
    checkInput("man man\n");
    printf("Excellent work! Lets see what happens when this command is called.\n");
    printf("\nNOTE:");
    printf("\n\nIn order to escape this menu, you will have to hit q!\n\nwhen you're ready, press the enter key\n");
    scanf("%c", &c);
    execv("/usr/bin/man", cmdList);
    
}

int main() {
   char *const parmList[] = {"ls", NULL};
   int option = 0;

   printf( "Please enter your name: ");
   scanf("%s", name);

   printf("Hello %s, welcome to a tutorial on basic shell commands\n", name);
   while(option != -1){
       printf("If you would like to learn a specific command, please select the number associated with it.\n");
       printf("Or type 0 for all\n");
       printf("Type -1 to exit.\n\n");
       printf("0 - full tutorial\n");
       printf("1 - man\n");
       printf("2 - ls\n");
       printf("3 - pwd\n");
       printf("4 - cd\n");
       printf("5 - mkdir\n");
       printf("6 - rm\n");
       printf("7 - cp\n");
       printf("8 - mv\n");
       printf("9 - cat\n");
       printf("Please enter response: ");
       scanf("%d", &option);
       
       if(option == 0){
           return 0;
       }
       else if(option == 1){
           man();
       }
       else if(option == -1){
           break;
       }
       else{
           printf("Not an available option, please try again.\n");
       }
   }
   
   execv("/bin/ls", parmList);

   return 0;
}