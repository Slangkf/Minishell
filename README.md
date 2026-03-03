*This project was created in July 2025 as part of the 42 curriculum by seruff and tclouet.*

![](/readme_utils/notation.png)

![](/readme_utils/feedback.png)

# Description

*This section presents the project, its goals and a brief overview :*

**Minishell** is a lightweight shell interpreter written in C, based on POSIX bash. It replicates the core functionality of a Unix-like shell, allowing users to execute commands and interact with the system through a command-line interface.

#### Goals

The primary objectives of this project are to:

1. **Understand shell mechanics** - Explore how shells parse, tokenize, and execute user input.
2. **Build robust parsing logic** - Create a lexer and parser to correctly interpret shell syntax.
3. **Master process management** - Implement pipes, redirections, and process spawning using system calls.
4. **Implement key shell features** - Support built-in commands, variable expansion, and signal handling.

#### Key Features

- **Built-in Commands**: Implements `echo`, `cd`, `pwd`, `export`, `unset`, `env` and `exit` commands.
- **Input/Output Redirection**: Supports `<`, `>`, `>>`, and heredoc (`<<`) operators.
- **Piping**: Enables chaining multiple commands with pipes (`|`).
- **Variable Expansion**: Expands environment variables.
- **Signal Handling**: Properly manages signals.
- **Word Splitting**: Correctly parses and splits command arguments.
- **Quote Handling**: Supports single and double quotes for escaping special characters.

#### Architecture

The project is organized into several modules:

- **Lexer**: Tokenizes input into manageable units.
- **Parser**: Builds an abstract syntax tree from tokens.
- **Execution**: Manages command execution, pipes, and redirections.
- **Expander**: Handles variable and parameter expansion.
- **Built-ins**: Implements shell built-in commands.
- **libft**: Custom utility library providing standard C functions and helpers.

# Instructions

*This section contains information about compilation, installation, and/or execution :*

#### Prerequisites

Before building and running `minishell`, install the following tools:

- GCC or Clang (C compiler)
- GNU Make (build tool)
- A POSIX-compatible shell for testing

#### Compilation

1. Open a terminal and navigate to the project root:

```bash
cd minishell
```

2. Build the project:

```bash
make
```

This invokes the provided `Makefile` to compile sources and produce the `minishell` executable. The `libft` library is built automatically by the Makefile.

3. Optional: clean build artifacts

```bash
make clean   # remove object files
make fclean  # remove object files and executables
make re      # fclean + make
```

#### Running the shell

Start `minishell` from the project root:

```bash
./minishell
```

Prompt example:
```bash
Minishell@Tclouet-Seruff$> 
```

#### Exiting

Type `exit` or press `Ctrl+D` to quit `minishell`.

# Resources

*This section lists references related to the topic, as well as a description of how AI has been used :*

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/html_node/Bash-POSIX-Mode.html)
- [How to start the project](https://medium.com/@mostafa.omrane/mes-conseils-si-je-devais-recommencer-minishell-a9783c51ba1b)
- [How to use GitHub](https://docs.github.com/en/get-started)
- [Numerous tests to improve our Minishell](https://docs.google.com/spreadsheets/d/18U0LXtxsC_SZEJ0KNBKvnPxypCNznXuwyQfm5n_mpUA/edit?pli=1&gid=0#gid=0)

#### Use of AI :
At the start of the project, AI helped us understand new concepts by explaining them in clear and accessible terms.

# Team Contribution

This project was developed collaboratively by **seruff** and **tclouet**. The work was divided as follows:

- **seruff** implemented the lexer, parser, and variable expansion parts, handling tokenization, syntax analysis, and environment variable substitution.

- **tclouet** implemented the execution engine and signal handling, managing process creation, pipes, redirections, and proper signal management.

- Both team members collaborated on implementing and testing the built-in commands (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`).

By distributing these responsibilities, we worked efficiently while developing our technical skills, team spirit, and communication abilities.
