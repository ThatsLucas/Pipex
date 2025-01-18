# Pipex

## Description

**Pipex** is a custom implementation of command chaining, similar to the behavior of a shell pipeline. This program supports:

- Unlimited pipes (`|`) for chaining commands.
- A **heredoc** mode to handle multi-line input terminated by a custom delimiter.

## Features

1. **Command Chaining:**
   - Pipex can chain multiple commands through standard pipes.
   - Commands are executed with proper input and output redirections.

2. **Heredoc Mode:**
   - Allows the user to provide multi-line input using a custom-defined delimiter.

3. **Robust Error Handling:**
   - Clear error messages for failures in access, pipes, forks, or execution.

## Installation

Clone this repository and compile the source files using the `Makefile`:

```bash
make
```

This will generate the `pipex` executable.

## Usage

### Basic Usage

```bash
./pipex infile "command1" "command2" ... "commandN" outfile
```

- `infile`: The input file to read data from.
- `outfile`: The output file to write data to.
- `command1` ... `commandN`: Commands to execute sequentially, separated by pipes.

Example:

```bash
./pipex input.txt "grep keyword" "wc -l" output.txt
```

This example will:
1. Read data from `input.txt`.
2. Pass it through `grep keyword`.
3. Count the lines using `wc -l`.
4. Save the result in `output.txt`.

### Heredoc Mode

```bash
./pipex here_doc DELIMITER "command1" "command2" ... "commandN" outfile
```

- `DELIMITER`: The custom delimiter to mark the end of heredoc input.
- The rest of the arguments are similar to basic usage.

Example:

```bash
echo -e "line1\nline2\nDELIMITER" | ./pipex here_doc DELIMITER "cat" "wc -c" output.txt
```

This will:
1. Accept multi-line input terminated by `DELIMITER`.
2. Pass the input through `cat`.
3. Count the characters using `wc -c`.
4. Save the result in `output.txt`.

## Error Handling

Pipex includes robust error handling to manage common issues such as:

- Invalid arguments.
- Failure to create pipes.
- Forking errors.
- Command execution errors (e.g., command not found).

## Notes

- Ensure all commands provided are valid and exist in the system PATH.
- Input and output files must have proper read/write permissions.

## Author

Developed by [lle-duc](mailto:lle-duc@student.42.fr).

## License

This project is licensed under the [MIT License](LICENSE).

