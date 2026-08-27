# get_next_line

## Description

`get_next_line` is a function that reads a line from a file descriptor,
one call at a time, developed as part of the 1337 / 42 curriculum.

The goal of this project is to implement a function that returns a line
read from a file descriptor without knowing in advance the size of the
file or the length of the line, and without leaking memory between calls.

## Project Structure

```text
get_next_line/
├── get_next_line.h              # Mandatory part header
├── get_next_line.c              # Mandatory part implementation
├── get_next_line_utils.c        # Mandatory part helper functions
├── get_next_line_bonus.h        # Bonus part header
├── get_next_line_bonus.c        # Bonus part implementation
└── get_next_line_utils_bonus.c  # Bonus part helper functions
```

## How It Works

`get_next_line` reads from the given file descriptor in chunks of
`BUFFER_SIZE` bytes, using a `static` buffer to preserve leftover data
between successive calls. Each call:

1. Reads more data from the file descriptor if the current buffer has
   been fully consumed.
2. Appends characters to the line being built, one at a time.
3. Stops as soon as a newline (`\n`) or the end of the file is reached.
4. Returns the resulting line (including the trailing `\n`, if present),
   or `NULL` when there is nothing left to read.

## Mandatory vs Bonus

| | Mandatory | Bonus |
|---|---|---|
| Handles multiple file descriptors simultaneously | ❌ | ✅ |
| Handles multiple `BUFFER_SIZE` values in the same program | ❌ | ✅ |
| State tracking | `static` variables local to the function | `static` array of states indexed by file descriptor |

The bonus version introduces a `t_gnl_state` structure that stores the
read buffer and reading position for each file descriptor independently,
allowing the function to read from several files at once without mixing
up their progress.

## Compilation

This project does not include its own `Makefile`; the source files are
meant to be compiled directly or included in another project.

Compile the mandatory part:

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o gnl
```

Compile the bonus part (set `BUFFER_SIZE` as needed):

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=5 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

## Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```

## Technologies

- C
- Unix/POSIX development environment

## Context

Academic project completed as part of the 1337 / 42 curriculum.