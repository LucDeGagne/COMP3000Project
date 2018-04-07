//https://www.cyberciti.biz/faq/linuxunix-rules-for-naming-file-and-directory-names/

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//https://www.liquidweb.com/kb/new-user-tutorial-basic-shell-commands/

char name[20];

void checkInput(char desired[]){
    setbuf(stdin, NULL);
    char inputted[100];
    fgets(inputted, 100, stdin);
    srand(time(NULL));
    int r;
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
    printf("\nusing various commands. %s, let's start with the basic command, please type in man man:\n",name);
    checkInput("man man\n");
    printf("\n\n\nExcellent work! Lets see what happens when this command is called.");
    printf("\nNOTE:");
    printf("\n\nIN ORDER TO ESCAPE THIS MENU YOU WILL HAVE TO PRESS q!\n\n");
    printf("A few commands that may help include the arrow keys to scroll trough the information.\n");
    printf("Tapping the h key will pull up a helper menu for the man page. ");
    printf("When you're ready, press the enter key\n");
    c = getchar();
    system("man man");
    printf("\n\n\nAlthough that was a lot of information, as you become a better programmer,\n"
            "it will start to help you sift through pages and pages of information and how to\n"
            "use them.\nThese pages typically have 9 sections that they help:\n\n1. executable\n"
            "programs or shell commands\n2. system calls\n3. library routines\n4. special\n"
            "files (i.e., devices in the /dev directory)\n5. file formats\n6. games\n"
            "7. macro packages\n8. system administration commands\n9. kernel routines\n\n"
            "But as beginner programmers, we don't need to know what a kernel routine is.\n"
            "What we do want to focus on is how to open a man page as well as learning about a\n"
            "flag.\nThis time, type \"man ls\" and see if you can find what the -l character does.\n"
            "Hint: Look under description\n");
    checkInput("man ls\n");
    system("man ls");
    printf("\n\n\n\nThe \"-\" is a flag, %s. We will learn more about that later. This was just\n"
    "a brief taste of what the man pages can do. A little confusing in the hands of a beginner\n"
    "user, but as you get better, the man pages will become clearer and clearer!\n", name);
    printf("Press enter to continue to the next section when ready, %s.\n",name);
    c = getchar();
}

void ls(){
    char c;
    printf("In this section, we will begin to learn about the ls command. This command\n"
    "helps us to determine what files and folders are located in our directory. The ls\n"
    "command stands for list. And that's exactly what we're going to do. Try typing in\n"
    "the command and see what happens:\n");
    checkInput("ls\n");
    system("ls");
    printf("\n\n\nIf you look closely, this printed out a list of files and folders onto\n"
        "your page so you can see what's going on. Anything in white is a file that can be\n"
        "manipulated. Anything in blue is a folder (called a directory here) that you can\n"
        "navigate into and anything in green is executable, but you don't have to worry\n"
        "about that in this tutorial.\n Next lets try using a flag. Lets sort our files by\n"
        "time and date: try typing \"ls -t\"\n\n");
    checkInput("ls -t\n");
    system("ls -t");
    printf("\n\nThat didn't give us very much information, instead, lets try combining\n"
        "two flags together to really see what's going on in the file. %s, try typing \"ls -la\"\n\n", name);
    checkInput("ls -la\n");
    system("ls -la");
    printf("We have two unexpected files that we hadn't seen before! They are both\n"
        "represented by \".\"\nA single dot means the current directory, meaning the file\n"
        "we are presently litsing the contents of and the two dots \"..\" represents the\n"
        "parent file, and will be discused in more detail later. Once you feel confident\n"
        "with this information, hit enter to continue.");
    scanf("%c", &c);
}

void pwd(){
    char c;
    printf("We'll now look at the pwd command, which stands for pathway directory. Much\n"
        "like in a mall kiosk map, pwd represents the \'you are here\' sign.\n");
    printf("There's no bells and whistles, it just shows you all the directories you have\n"
        "to take to get back to your home page. Try typing in the command \"pwd\"\n");
    checkInput("pwd\n");
    system("pwd");
    printf("This location above is synonymous with the \".\" value, which we'll discuss in\n"
        "more detail later.\n");
    printf("%s, hit enter when you're ready to proceed.\n",name);
    scanf("%c", &c);
}

void cd(){
    char c;
    system("mkdir tutorial");
    printf("%s, We're now going to look at a command called cd, which stands for change directory.\n",name);
    printf("cd is a navigational command for us to enter and exit directories, like clicking on\n"
    "folders to enter and exit them in Mac or Windows. First, we will type pwd, so we know where\n"
    "we are. Once the pathway appears, try typing \"cd tutorial\"\n");
    checkInput("pwd\n");
    system("pwd");
    checkInput("cd tutorial\n");
    system("cd tutorial");
    printf("We're now in a new directory, called tutorial, below is the pathway.\n");
    system("cd tutorial; pwd");
    printf("In order to get back to our original directory, we have to go back up.\n"
        "The \"../\" represents our parent directory, so we want togo back one directory.\n"
        "in order to advance, we need to return to our current file. Try typing \"cd ../\"\n");
    checkInput("cd ../\n");
    printf("Now we're back where we originally started.\n");
    system("pwd");
    printf("Once you're ready, hit enter to advance to the next section, %s.\n",name);
    system("rm -r tutorial");
    scanf("%c", &c);
}

void mkdir(){
    char c;
    char* result = malloc(strlen("mkdir ")+strlen(name)+1);
    char* input = malloc(strlen(result)+strlen("\n")+1);
    strcpy(result,"mkdir ");
    strcat(result,name);
    strcpy(input,result);
    strcat(input,"\n");
    printf("Our next command to view is the mkdir command. This will allow us to create a new\n"
        "directory and stands for make directory. First, we'll look at all the current files in\n"
        "our current directory:\n");
    system("ls -l");
    printf("Now we'll try creating a new directory. Try typing the command \"mkdir test\"\n");
    checkInput("mkdir test\n");
    system("mkdir test");
    printf("Let's see if that worked, here's a new list of the files in our directory:\n");
    system("ls -l");
    printf("Notice the newest file? It's out test folder we created! Try creating another folder\n"
        "called %s. Remember, all file names are case sensitive, so Test is a different directory from test\n",name);
    checkInput(input);
    system(result);
    system("ls -l");
    printf("Look at our newest file! It's you!\n\nSome other naming conventions before we continue include\n"
        "avoiding the use of blank space in a directory (or file) name, a good alternative is the underscore\n"
        "or dash symbol. And all files need to be unique.\nPress the enter key when you're ready to continue.\n");
    system("rm -r test");
    char* end = malloc(strlen("rm -r ")+strlen(name)+1);
    strcpy(end,"rm -r ");
    strcat(end,name);
    system(end);
    scanf("%c", &c);
}

void rm(){
    char c;
    printf("We will now look at the rm command, which stands for remove. This command allows you to delete\n"
        "files and directories alike, it does not send it to any sort of recycling bin so once you've typed\n"
        "rm with a file it's gone. Let's try on a simple practice file. Below is the current file contents:\n");
    system("touch test");
    system("mkdir example");
    system("ls -l");
    printf("\nTry typing \"rm test\":\n");
    checkInput("rm test\n");
    system("rm test");
    printf("Now here's a list of the file contents, notice how test is gone?\n");
    system("ls -l");
    printf("A quick note on this command, typing \"rm *\" removes all the files in the directory except folders.\n"
        "This has to be used carefully because once removed, the files are gone forever. Now how do we remove\n"
        "a directory? Let's try removing it with a flag, try typing \"rm -r example\":\n");
    checkInput("rm -r example\n");
    system("rm -r example");
    printf("Now the file has been removed, check out our current directory contents:\n");
    system("ls -l");
    printf("Type enter to continue when you're ready.\n");
    scanf("%c", &c);
}

void cp(){
    char c;
    printf("The cp command stands for copy. It creates a copy of a file either within the current directory\n"
        "with a different name or in a new directory. Let's try this with an example directory and file.\n"
        "First you type cp then you'll type the file you want to copy's current location and the location\n"
        "you want to copy it to. Try \"cp test temp\".\n");
    system("touch test");
    system("mkdir temp");
    checkInput("cp test temp\n");
    system("cp test temp");
    printf("Now when we look in the temp file, a new file has been created called test. This means we were\n"
        "able to copy our test file into a new dircetory, see the contents of the directory below:\n");
    system("ls -l ./temp/");
    printf("Let's try copying the file back to our original folder but with a new name. Try\n"
        "using \"cp ./temp/test ./newTest\" the single dot represents the current directory.\n");
    checkInput("cp ./temp/test ./newTest\n");
    system("cp ./temp/test ./newTest");
    printf("\nLet's look at this, now we have in our directory:\n");
    system("ls -l");
    system("rm test newTest;rm -r temp");
    printf("Hit enter to move on.\n");
    scanf("%c", &c);
}

void mv(){
    char c;
    printf("We're almost done. One of the most important last minute commands is mv which stands for move. As in\n"
        "moving or renaming files. Instead of copy, it acts more as a cut and paste as well as a rename\n"
        "function. Let's try renaming a file from test to myFile. Below are the files we currently have:\n\n");
    system("touch test;mkdir other;ls -l");
    printf("\n\nNow try typing mv test myFile\n");
    checkInput("mv test myFile\n");
    system("mv test myFile");
    printf("Now when we check our current files, test is gone and myFile is there instead!\n");
    system("ls -l");
    printf("Let's try moving a file to a new location. Let's take myFile and move it into the directory called\n"
        "other. Try typing the command \"mv myFile other\", the name of your source file goes first and then\n"
        "the second name is the destination location or the new name.\n");
    checkInput("mv myFile other\n");
    system("mv myFile other");
    printf("The new contents of the other directory are shown below.\n");
    system("ls -l ./other/");
    printf("\n\nAnd now the contents of our current directory are shown\n");
    system("ls -l");
    printf("Our newFile has moved from its original destination to a new one and is gone from our original\n"
        "directory. Press enter when you're ready.\n");
    system("rm -r other");
    scanf("%c", &c);
}

void cat(){
    char c;
    printf("Our last command we'll be learning is called the cat command. It simply allows us to view the\n"
        "contents of a file, it has other uses but for now, we'll just stick to this one. Try\n"
        "typing \"cat lastCommand\"\n");
    system("touch lastCommand;echo \"Congrats! This is the last command!\">>lastCommand");
    checkInput("cat lastCommand\n");
    system("cat lastCommand");
    printf("Hit enter to finish.\n");
    system("rm lastCommand");
    scanf("%c", &c);
}

int menu() {
   int option = 0;

   printf( "Please enter your name: ");
   scanf("%s", name);

   printf("Hello %s, welcome to a tutorial on basic shell commands\n", name);
   while(option != -1){
       printf("If you would like to learn a specific command, please select the number associated with it.\n");
       printf("Or type 0 for all\n");
       printf("Type -1 to exit.\n\n");
       printf("0 - full tutorial\n");
       printf("1 - manuals\n");
       printf("2 - list\n");
       printf("3 - pathway directory\n");
       printf("4 - change directory\n");
       printf("5 - make directory\n");
       printf("6 - remove\n");
       printf("7 - copy\n");
       printf("8 - move\n");
       printf("9 - cat\n");
       printf("Please enter response: ");
       scanf("%d", &option);
       if(option == 0){
           man();
           ls();
           pwd();
           cd();
           mkdir();
           rm();
           cp();
           mv();
           cat();
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
       else if(option == 4){
           cd();
       }
       else if(option == 5){
           mkdir();
       }
       else if(option == 6){
           rm();
       }
       else if(option == 7){
           cp();
       }
       else if(option == 8){
           mv();
       }
       else if(option == 9){
           cat();
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