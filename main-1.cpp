#include <iostream>
#include <unistd.h>
#include <string.h>
#include <string>
#include <wait.h>
#include <vector>
#include <algorithm>
using namespace std;
void exit()
{
    _exit(0);
}
vector<char*> command_tokenizer(char* command)
{
    char *token = strtok(command, " ");
    vector<char*> args;
    while(token != NULL)
    {
        args.push_back(token);
        token = strtok(NULL, " ");
    }
    return args;
}

void log(int sig)
{
    pid_t pid;
    pid = wait(NULL);
    FILE *log_file = fopen("log.txt","a");
    fprintf(log_file,"%s\n","child has been terminated");
    fclose(log_file);
}
void exec_command(vector<char*> args)
{
    int argv_size = args.size() + 1; // for the NULL terminator
    char* argv[argv_size];
    int i, j;
    bool waitChild = true;
    for(i = 0, j = 0; j < argv_size - 1; j++)
    {
        if(strcmp(args[j],"&") == 0)
        {
            waitChild = false;
            continue;
        }
        argv[i++] = args[j];
    }
    argv[j > i ? i : j] = NULL;

    signal(SIGCHLD, log);
    int pid = fork();
    if(pid > 0)
    {
        if(waitChild)
        {
            wait(NULL);
        }
    }
    else
    {
        execvp(argv[0], argv);
    }
}
int main()
{
    string input;
    do
    {
        cout << "shell > ";
        getline(cin,input);
        char* command = new char(input.length() + 1);
        strcpy(command, input.data());

        vector<char*> c = command_tokenizer(command);
        exec_command(c);
    }
    while(input.compare("exit"));
    exit();
}
