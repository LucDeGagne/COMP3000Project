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
    srand(time(NULL));
    int r = rand() % 4;
    while(strcmp(desired,inputted) != 0){
        r = rand() % 4;
        if(r == 0){
            printf("Not quite right, please try again\n");
        }
        else if(r == 1){
            printf("Almost there, give it another go\n");
        }
        else if(r == 2){
            printf("Incorrect\n");
        }
        else{
            printf("I'm sorry, you'll have to try again\n");
        }
        fgets(inputted, 100, stdin);
    }
}

void man(){
    char c;
    printf("We will start by looking at the man command. This command pulls up a manual with information on ");
    printf("using various commands. %s, let's start with the basic command, please type in man man:\n",name);
    checkInput("man man\n");
    printf("\n\n\nExcellent work! Lets see what happens when this command is called.");
    printf("\nNOTE:");
    printf("\n\nIN ORDER TO ESCAPE THIS MENU YOU WILL HAVE TO PRESS q!\n\n");
    printf("A few commands that may help include the arrow keys to scroll trough the information.\n");
    printf("Tapping the h key will pull up a helper menu for the man page. ");
    printf("When you're ready, press the enter key\n");
    scanf("%c", &c);
    system("man man");
    printf("\n\n\nAlthough that was a lot of information, as you become a better programmer, it will start to help you sift through pages and pages of information and how to use them.\nThese pages typically have 9 sections that they help:\n\n1. executable programs or shell commands\n2. system calls\n3. library routines\n4. special files (i.e., devices in the /dev directory)\n5. file formats\n6. games\n7. macro packages\n8. system administration commands\n9. kernel routines\n\nBut as beginner programmers, we don't need to know what a kernel routine is.\nWhat we do want to focus on is how to open a man page as well as learning about a flag.\nThis time, type \"man ls\" and see if you can find what the -l character does. Hint: Look under description\n");
    checkInput("man ls\n");
    system("man ls");
    printf("\n\n\n\nThe \"-\" is a flag, %s. We will learn more about that later. This was just a brief taste of what the man pages can do. A little confusing in the hands of a beginner user, but as you get better, the man pages will become clearer and clearer!\n", name);
    printf("Press enter to continue to the next section when ready, %s.\n",name);
    scanf("%c", &c);
}

void ls(){
    char c;
    printf("In this section, we will begin to learn about the ls command. This command helps us to determine what files and folders are located in our directory. The ls command stands for list. And that's exactly what we're going to do. Try typing in the command and see what happens:\n");
    checkInput("ls\n");
    system("ls");
    printf("\n\n\nIf you look closely, this printed out a list of files and folders onto your page so you can see what's going on. Anything in white is a file that can be manipulated. Anything in blue is a folder (called a directory here) that you can navigate into and anything in green is executable, but you don't have to worry about that in this tutorial.\n Next lets try using a flag. Lets sort our files by time and date: try typing \"ls -t\"\n\n");
    checkInput("ls -t\n");
    system("ls -t");
    printf("\n\nThat didn't give us very much information, instead, lets try combining two flags together to really see what's going on in the file. %s, try typing \"ls -la\"\n\n", name);
    checkInput("ls -la\n");
    system("ls -la");
    printf("We have two unexpected files that we hadn't seen before! They are both represented by \".\"\nA signle dot means the current directory, meaning the file we are presently litsing the contents of and the two dots \"..\" represents the parent file, and will be discused in more detail later. Once you feel confident with this information, hit enter to continue.");
    scanf("%c", &c);
}

void pwd(){
    char c;
    printf("We'll now look at the pwd command, which stands for pathway directory. Much like in a mall kiosk map, pwd represents the \'you are here\' sign.\n");
}

int main() {
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
       else if(option == 2){
           ls();
       }
       else if(option == 3){
           pwd();
       }
       else if(option == -1){
           break;
       }
       else{
           printf("Not an available option, please try again.\n");
       }
   }

   return 0;
}