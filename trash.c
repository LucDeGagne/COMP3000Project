/**
 * COMP3000 Operating Systems w/ Dr. M Barbeau
 * Final Project: Tutrial-Run Assisted SHell
 *
 * Author:   David Nelson  100988794
 *           Luc DeGané
 *
 * Compile:  gcc trash.c -o trash -lreadline
 *
 * Revision: 0.01 April 06/18
 *
 * Sources: built using
**/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

#define MAXCOM 1000 // max number of letters to be supported
#define MAXLIST 100 // max number of commands to be supported

#define SH_NAME		"TRAsh"
#define SH_VERSION	"0.01"

// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")

// Function to take input
int takeInput(char* str)
{
    char* buf;

    buf = readline("\n> ");
    if (strlen(buf) != 0) {
        add_history(buf);
        strcpy(str, buf);
        return 0;
    } else {
        return 1;
    }
}

// Function to print Current Directory.
void printDir()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\nDir: %s", cwd);
}

// Function where the system command is executed
void execArgs(char** parsed)
{
    // Forking a child
    pid_t pid = fork();

    if (pid == -1) {
        printf("\nFailed forking child..");
        return;
    } else if (pid == 0) {
        if (execvp(parsed[0], parsed) < 0) {
            printf("\nCould not execute command..");
        }
        exit(0);
    } else {
        // waiting for child to terminate
        wait(NULL);
        return;
    }
}

// Function where the piped system commands is executed
void execArgsPiped(char** parsed, char** parsedpipe)
{
    // 0 is read end, 1 is write end
    int pipefd[2];
    pid_t p1, p2;

    if (pipe(pipefd) < 0) {
        printf("\nPipe could not be initialized");
        return;
    }
    p1 = fork();
    if (p1 < 0) {
        printf("\nCould not fork");
        return;
    }

    if (p1 == 0) {
        // Child 1 executing..
        // It only needs to write at the write end
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        if (execvp(parsed[0], parsed) < 0) {
            printf("\nCould not execute command 1..");
            exit(0);
        }
    } else {
        // Parent executing
        p2 = fork();

        if (p2 < 0) {
            printf("\nCould not fork");
            return;
        }

        // Child 2 executing..
        // It only needs to read at the read end
        if (p2 == 0) {
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            if (execvp(parsedpipe[0], parsedpipe) < 0) {
                printf("\nCould not execute command 2..");
                exit(0);
            }
        } else {
            // parent executing, waiting for two children
            wait(NULL);
            wait(NULL);
        }
    }
}

// Help command builtin
void openHelp()
{
    puts("\n***WELCOME TO TRA.sh HELP***"
        "\n-Use the shell at your own risk..."
        "\nList of Commands supported:"
        "\n>cd"
        "\n>ls"
        "\n>exit"
        "\n>all other general commands available in UNIX shell"
        "\n>pipe handling"
        "\n>improper space handling");

    return;
}

// Function to execute builtin commands
int ownCmdHandler(char** parsed)
{
    int NoOfOwnCmds = 32, i, switchOwnArg = 0;
    char* ListOfOwnCmds[NoOfOwnCmds];
    char* username;

    ListOfOwnCmds[0] = "exit";
    ListOfOwnCmds[1] = "cd";
    ListOfOwnCmds[2] = "help";
    ListOfOwnCmds[3] = "hello";
    //man 5,6,7,8
    ListOfOwnCmds[4] = "nan";
    ListOfOwnCmds[5] = "mman";
    ListOfOwnCmds[6] = "mam";
    ListOfOwnCmds[7] = "manual";
    //ls 9,10,11,12
    ListOfOwnCmds[8] = "lss";
    ListOfOwnCmds[9] = "sl";
    ListOfOwnCmds[10] = "l";
    ListOfOwnCmds[11] = "l";
    //pwd
    ListOfOwnCmds[12] = "pwdd";
    ListOfOwnCmds[13] = "ppwd";
    ListOfOwnCmds[14] = "pd";
    ListOfOwnCmds[15] = "here";
    //cd
    ListOfOwnCmds[16] = "ccd";
    ListOfOwnCmds[17] = "cdd";
    ListOfOwnCmds[18] = "c";
    ListOfOwnCmds[19] = "d";
    //mkdir
    ListOfOwnCmds[20] = "mk";
    ListOfOwnCmds[21] = "mkder";
    ListOfOwnCmds[22] = "makedir";
    ListOfOwnCmds[23] = "mkdr";
    //rm
    ListOfOwnCmds[24] = "rrm";
    ListOfOwnCmds[25] = "rmm";
    ListOfOwnCmds[26] = "r";
    ListOfOwnCmds[27] = "m";
    //cp
    ListOfOwnCmds[28] = "ccp";
    ListOfOwnCmds[29] = "cpp";
    ListOfOwnCmds[30] = "c";
    ListOfOwnCmds[31] = "p";

    for (i = 0; i < NoOfOwnCmds; i++) {
        if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0) {
            switchOwnArg = i + 1;
            break;
        }
    }

    switch (switchOwnArg) {
    case 1:
        printf("\nGoodbye\n");
        exit(0);
    case 2:
        chdir(parsed[1]);
        return 1;
    case 3:
        openHelp();
        return 1;
    case 4:
        username = getenv("USER");
        printf("\nHello %s.\nMind that this is "
            "not a place to play around."
            "\nUse help to know more..\n",
            username);
        return 1;

      //man
      case 5:
      case 6:
      case 7:
      case 8:
          printf(YELLOW"%s did you mean to type 'man'?\n" RESET, getenv("USER"));
          return 1;

      //ls
      case 9:
      case 10:
      case 11:
      case 12:
          printf(YELLOW"%s did you mean to type 'ls'?\n"RESET, getenv("USER"));
          return 1;

      //pwd
      case 13:
      case 14:
      case 15:
      case 16:
          printf(YELLOW"%s did you mean to type 'pwd'?\n"RESET, getenv("USER"));
          return 1;

      //cd
      case 17:
      case 18:
      case 19:
      case 20:
          printf(YELLOW"%s did you mean to type 'cd'?\n"RESET, getenv("USER"));
          return 1;

      //mkdir
      case 21:
      case 22:
      case 23:
      case 24:
          printf(YELLOW"%s did you mean to type 'mkdir'?\n"RESET, getenv("USER"));
          return 1;

      //rm
      case 25:
      case 26:
      case 27:
      case 28:
          printf(YELLOW"%s did you mean to type 'rm'?\n"RESET, getenv("USER"));
          return 1;

      //cp
      case 29:
      case 30:
      case 31:
      case 32:
          printf(YELLOW"%s did you mean to type 'cp'?\n"RESET, getenv("USER"));
          return 1;

    default:
        break;
    }

    return 0;
}

// function for finding pipe
int parsePipe(char* str, char** strpiped)
{
    int i;
    for (i = 0; i < 2; i++) {
        strpiped[i] = strsep(&str, "|");
        if (strpiped[i] == NULL)
            break;
    }

    if (strpiped[1] == NULL)
        return 0; // returns zero if no pipe is found.
    else {
        return 1;
    }
}

// function for parsing command words
void parseSpace(char* str, char** parsed)
{
    int i;

    for (i = 0; i < MAXLIST; i++) {
        parsed[i] = strsep(&str, " ");

        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)
            i--;
    }
}

int processString(char* str, char** parsed, char** parsedpipe)
{

    char* strpiped[2];
    int piped = 0;

    piped = parsePipe(str, strpiped);

    if (piped) {
        parseSpace(strpiped[0], parsed);
        parseSpace(strpiped[1], parsedpipe);

    } else {

        parseSpace(str, parsed);
    }

    if (ownCmdHandler(parsed))
        return 0;
    else
        return 1 + piped;
}

int main()
{
    char inputString[MAXCOM], *parsedArgs[MAXLIST];
    char* parsedArgsPiped[MAXLIST];
    int execFlag = 0;

    while (1) {
        // print shell line
        printDir();
        // take input
        if (takeInput(inputString))
            continue;
        // process
        execFlag = processString(inputString,
        parsedArgs, parsedArgsPiped);
        // execflag returns zero if there is no command
        // or it is a builtin command,
        // 1 if it is a simple command
        // 2 if it is including a pipe.

        // execute
        if (execFlag == 1)
            execArgs(parsedArgs);

        if (execFlag == 2)
            execArgsPiped(parsedArgs, parsedArgsPiped);
    }
    return 0;
}
