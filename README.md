# Simple-shell
A Shell is simply a program that conveniently
allows you to run other programs.

# Features

1. The internal shell command "exit" which terminates the shell

- System calls: exit()

2. A command with no arguments

- Example: ls, cp, rm ...etc
- Details: the shell must block until the command completes and, if the return code
  is abnormal, print out a message to that effect.
- System calls: fork(), execvp(), exit(), wait()

3. A command with arguments

- Example: ls –l
- Details: Argument 0 is the name of the command.

4. A command, with or without arguments, executed in the background using &.

- Example: firefox &
- Details: In this case, the shell must execute the command and return immediately,
  not blocking until the command finishes.
