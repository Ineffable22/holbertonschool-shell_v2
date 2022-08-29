# Shell v2 By Ineffable
<img src="https://raw.githubusercontent.com/Ineffable22/holbertonschool-shell_v2/main/img/shell.jpeg"/>

## Overview
The Shell_v2 repository contains files from my version of Shell, but a second version more advanced to [Simple_shell](https://github.com/Ineffable22/simple_shell), which is a UNIX shell based on bash and Sh.  This  is  my  command line version of the interpreter it is written in C language. 

<div align="center">
<img src="https://raw.githubusercontent.com/Ineffable22/holbertonschool-shell_v2/main/img/Ken_thompson_japan_prize_68.jpg"/>

### [Kenneth Lane Thompson](https://en.wikipedia.org/wiki/Ken_Thompson)
He designed and implemented the original Unix operating system.
</div>

## Description
This shell starts reading .hshrc and then optionally reads the first argument represented by a file and executes all internal commands. Then it prints a prompt and starts reading the commands. And what's more, it creates a history per command inserted.

## Commands
### Path commands
- Commands inside the path.

### Built-in

| Command      | Description |
|--|--|
| **env**      | Prints Environment                               |
| **whoami**   | Display the effective user ID                    |
| **clear**    | Clears the terminal screen                       |
| **cd**       | Changes the working directory                    |
| **pwd**      | Prints the name of the current working directory |
| **exit**     | Exits the program with a status code             |
| **setenv**   | Set a value in the Environment                   |
| **unsetenv** | Unset a value in the Environment                 |
| **history**  | Prints the command history                       |
| **help**     | Prints the help manual                           |
| **alias**    | Prints alias                                     |
| **PS1**      | Changes the prompt                               |

### Advance commands
- Redirections:
    - `n>` Right stream redirection (n is a file descriptor).
    - `>>` Double right stream redirection (Append).
    - `<`  Left stream redirection.
    - `<<` Heredoc (Double left stream redirection).
- Logical operators:
    - `&&` Handle the AND logical operator
    - `||` Handle the OR logical operator
- Separator:
    - `;` Handle the commands separator.
- Comments: 
    - `#` Handle comments.
- Variables:
    - `$?` Status Code
    - `$$` Currend PID(Process ID)
    - `$variable` Handles an Environment variable like `$PATH`
- Signal:
    - `^C` Ctrl + C

## Compilation
Usage: `hsh`
- Shell_v2 is started with the standard input connected to the terminal. To start, compile all .c located in this repository by using this command:
```Bash
$ make all
$ ./hsh [File optional]
```

## Example
```Bash
#Cisfun:~/holbertonschool-shell_v2$ echo Hello ; echo World
Hello
World
#Cisfun:~/holbertonschool-shell_v2$ cd
#Cisfun:~$ cd /tmp
#Cisfun:/tmp$ pwd
/tmp
#Cisfun:/tmp$ cat -e << Heredoc
Hello
This is a document
Which is inserted into the standard input
to cat command with the e option
Heredoc
Hello$
This is a document$
Which is inserted into the standard input$
to cat command with the e option$
```
## Author
Please, read the AUTHORS file
<div align="center">
<a href="https://www.linkedin.com/in/miguel-enrique-grillo-orellana/">
<img src="https://img.shields.io/badge/Miguel-Linkedind-blue"></a>

<a href="https://medium.com/@Miguel_Grillo"><img src="https://miro.medium.com/max/1200/0*jTIO9a1_5T3mv-pR.png" alt="Link Medium" width="100px" height= "50px"></a>
</div>
