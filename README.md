# GNL
# Get Next Line

## Description

`get_next_line` is a 42 project that teaches how to read a file line by line using the `read()` function.

The function returns one line at a time from a file descriptor.

Example:

```text
Hello
World
42
```

Calling:

```c
get_next_line(fd);
```

returns:

```text
"Hello\n"
```

The next call returns:

```text
"World\n"
```

And so on until the end of the file, where it returns:

```c
NULL
```

---

## Main Idea

The main idea of GNL is:

```text
READ → JOIN → FIND '\n' → GET LINE → GET LEFTOVER
```

We use a `static` variable called `leftover` to keep the data that was read but belongs to the next line.

For example, if `read()` gives us:

```text
hello\nworld\n
```

we return:

```text
hello\n
```

and keep:

```text
world\n
```

inside `leftover` for the next call.

---

## `read()`

The `read()` function reads bytes from a file descriptor.

```c
read(fd, buffer, BUFFER_SIZE);
```

It can return:

```text
> 0  → number of bytes read
= 0  → End Of File (EOF)
< 0  → error
```

### EOF

EOF means **End Of File**.

When:

```c
read(...) == 0
```

there is no more data to read.

If there is still data in `leftover`, we return that last line.

After that, the next call returns `NULL`.

---

## `BUFFER_SIZE`

`BUFFER_SIZE` determines how many bytes we try to read each time.

For example:

```text
BUFFER_SIZE = 10
```

means:

```c
read(fd, buffer, 10);
```

The important thing is that one `read()` does not necessarily equal one line.

A single read can contain:

* part of a line
* exactly one line
* several lines

This is why we need `leftover`.

---

## Static Variable

We use:

```c
static char *leftover;
```

A static variable keeps its value between function calls.

For example:

```text
First call:
leftover = "world\n"

Second call:
leftover is still "world\n"
```

Without `static`, the information would be lost when `get_next_line()` returns.

---

## Algorithm

### 1. Allocate the buffer

```c
buffer = malloc(BUFFER_SIZE + 1);
```

The buffer temporarily stores data returned by `read()`.

### 2. Read until newline

`read_until_newline()` keeps reading while there is no `\n` in `leftover`.

```text
read()
   ↓
join with leftover
   ↓
find '\n'
   ↓
newline found?
   ↓
yes → stop
no  → read again
```

### 3. Get the line

`get_line()` takes everything from the beginning of `leftover` until `\n`.

Example:

```text
leftover = "hello\nworld"
```

becomes:

```text
line = "hello\n"
```

### 4. Get the remaining data

`get_leftover()` keeps everything after the newline.

```text
"hello\nworld"
      ↓
"world"
```

### 5. Save leftover

The new leftover is stored in the static variable.

The next call starts from there.

---

## Functions

### `strlen()`

Returns the length of a string.

```c
strlen("hello");
```

returns:

```text
5
```

### `ft_strdup()`

Creates a new allocated copy of a string.

### `strjoin()`

Creates a new string containing two strings together.

Example:

```text
"hello" + "world"
        ↓
"helloworld"
```

### `join_buffer()`

Joins `buffer` with the current `leftover` and frees the old `leftover`.

### `find_newline()`

Searches for `\n` and returns its index.

### `get_line()`

Extracts the next line from `leftover`.

### `get_leftover()`

Extracts everything after the first newline.

### `read_until_newline()`

Reads and joins data until a newline is found or EOF is reached.

### `get_next_line()`

Controls the whole process:

```text
allocate buffer
      ↓
read until '\n'
      ↓
get line
      ↓
get leftover
      ↓
free old leftover
      ↓
return line
```

---

## Memory Management

GNL uses dynamic memory, so every allocated memory block must eventually be freed.

Important allocations include:

```c
malloc()
```

inside:

* `buffer`
* `ft_strdup`
* `strjoin`
* `get_line`
* `get_leftover`

The old `leftover` must be freed when it is replaced by a new one.

---

## Compilation

Example:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c main.c
```

Then:

```bash
./a.out
```

You can change the buffer size:

```bash
-D BUFFER_SIZE=1
```

or:

```bash
-D BUFFER_SIZE=100
```

Testing with different buffer sizes is important because the behavior of `read()` changes depending on the buffer size.

---

## Important Cases To Test

The project should be tested with:

1. A normal file with several lines.
2. An empty file.
3. A file containing one line.
4. A file where the last line has no `\n`.
5. A file ending with `\n`.
6. A file smaller than `BUFFER_SIZE`.
7. A file larger than `BUFFER_SIZE`.
8. `BUFFER_SIZE = 1`.
9. A large `BUFFER_SIZE`.
10. Calling `get_next_line()` after EOF.

---

## Summary

The whole GNL algorithm can be remembered as:

```text
              get_next_line()
                     |
                     v
              read from fd
                     |
                     v
              join into leftover
                     |
                     v
              find '\n'
                /       \
              NO         YES
              |           |
            read       get_line
              |           |
              └─────> get_leftover
                           |
                           v
                     save leftover
                           |
                           v
                     return line
```

The most important concept is:

> `leftover` stores the data that was already read but belongs to the next line.
