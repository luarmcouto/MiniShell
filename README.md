# 🐚 Minishell

**Common Core 42 — Third Milestone**

---

## 📖 About

The goal of **minishell** is to build a simple Unix shell that mimics **bash** behavior for a subset of features.

Through this project, you will explore core operating system concepts such as:

* Process creation and termination
* File descriptor management
* Signal handling
* Tokenization and parsing
* Building a command interpreter

Additionally, this project was developed in a **team environment**, providing hands-on experience with **Git workflows and collaboration tools**.

---

## 🚀 Project Highlights

* Interactive prompt waiting for user input
* Command history & line editing (via Readline)
* Environment variable expansion (`$USER`, `$?`, etc.)
* Builtins executed in-process for performance
* Execution of external programs using `PATH`
* Support for pipes and redirections
* Signal handling aligned with bash behavior

---

## ✨ Features

### 🖥️ Prompt & Loop

* Interactive shell prompt
* EOF handling (Ctrl+D)
* Optional colored/fancy prompt

### 🔍 Parsing

* Tokenization and syntax analysis
* Support for quotes (`'`, `"`)
* Escape sequences
* Environment variable expansion (`$VAR`)
* Logical operators (`&&`, `||`) *(if implemented)*

### 📂 Redirections

* Input: `<`
* Output: `>`
* Append: `>>`
* Here-doc: `<<`
* Advanced error handling

### 🔗 Pipes

* Multi-command pipelines
* Example: `cmd1 | cmd2 | cmd3`
* Robust file descriptor management

### ⚙️ Builtins

* `echo`
* `cd`
* `pwd`
* `export`
* `unset`
* `env`
* `exit`
* *(optional)* `alias`, history wrapper

### 🌱 Environment

* Environment inheritance and modification
* `$SHLVL` management
* `$?` last exit status

### ⚡ Signals

* `Ctrl+C` → new prompt
* `Ctrl+D` → exit shell
* `Ctrl+\` → ignored (interactive mode)
* Context-aware signal handling

### ▶️ Execution

* `PATH` resolution
* `execve` usage
* Exit status propagation
* Optional caching for faster lookups

---

## 🧱 Usage

### 📥 Clone the repository

```
git clone https://github.com/luarmcouto/MiniShell.git
cd minishell
```

### ⚙️ Compile

```
make
```

### 🧹 Clean

```
make clean
make fclean
make re
```

### ▶️ Run

```
./minishell
```

### ⚠️ Dependencies

* `readline` must be installed

On macOS:

```
brew install readline
```

You may also need to adjust include/library paths in the Makefile.

---

## 🛠️ Behavior Overview

| Feature      | Description                             |
| ------------ | --------------------------------------- |
| Prompt       | Displays and waits for input            |
| Line Editing | Arrow navigation, history (Readline)    |
| Signals      | Ctrl-C resets prompt, Ctrl-D exits      |
| Quotes       | `'` literal, `"` allows `$` expansion   |
| Expansion    | `$VAR`, `$?`                            |
| Redirections | `<`, `>`, `>>`, `<<`                    |
| Pipes        | Chain multiple commands                 |
| Builtins     | echo, cd, pwd, export, unset, env, exit |
| Exit Codes   | Matches bash semantics                  |

---

## 💡 Examples

### External command

```
minishell$ ls -la
```

### Pipes

```
minishell$ ps aux | grep minishell | wc -l
```

### Redirection & Here-doc

```
minishell$ cat < file.txt << EOF
hello world
EOF
```

### Variables

```
minishell$ echo "Hello $USER, last status was $?"
```

### Builtins

```
minishell$ export PATH=/usr/bin:/bin
minishell$ cd src && pwd
minishell$ exit 42
```

---

## ⚠️ Error Handling

* Clear error messages sent to `stderr`
* Correct exit codes:

  * `127` → command not found
  * `126` → cannot execute
* Proper file descriptor cleanup
* No memory leaks on parsing/execution errors

---

## 🧠 Architecture

```
minishell/
├── src/
│   ├── main.c           # initialization & main loop
│   ├── control.c        # prompt & input handling
│   ├── parser/          # tokenization & AST/pipeline
│   ├── execution/       # execution logic
│   │   └── redirect.c   # redirections & pipes
│   ├── expander/        # environment & expansion
│   ├── builtins/        # shell builtins
│   ├── signals.c        # signal handling
│   └── utils/           # helpers
├── include/
│   └── minishell.h
├── Makefile
└── README.md
```

### 🔑 Design Notes

* Two execution contexts:

  * **Parent** → builtins affecting shell state
  * **Child** → external commands

* Pipeline/AST structure for execution flow

* Signal strategy:

  * Parent handles interactive signals
  * Children restore default behavior

* Here-doc implementation with proper signal control

* Memory management:

  * Clean allocations between prompts
  * Minimal/global state usage

---

## 📚 References

* Bash Manual
* POSIX.1-2017 — Shell & Utilities
* GNU Readline
* System calls:

  * `fork`, `execve`, `pipe`, `dup2`, `waitpid`, `signal`
* `termios` (optional advanced prompt handling)

---

## 🏁 Acknowledgements

* Thanks to the **42 community** for support, testing, and feedback
