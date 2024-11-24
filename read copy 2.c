#include <unistd.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>

static int read_from_fd(int fd, char *buffer, int *buffer_index, int *buffer_size)
{
    // Read into the buffer if it's empty
    if (*buffer_index == *buffer_size)
    {
        *buffer_size = read(fd, buffer, 42);  // Read data into buffer
        if (*buffer_size < 0)  // Error reading
            return -1;
        if (*buffer_size == 0)  // End of file
            return 0;

        *buffer_index = 0;  // Reset the buffer index for the new data
    }
    return 1;
}

static char *build_line_from_buffer(char *buffer, int *buffer_index, int buffer_size)
{
    char *line = NULL;
    char *temp = NULL;

    // Process characters in the buffer until we hit a newline
    while (*buffer_index < buffer_size && buffer[*buffer_index] != '\n')
    {
        temp = malloc(1);
        if (!temp)
            return NULL;

        temp[0] = buffer[*buffer_index];
        line = ft_strjoin(line, temp); // Append the character to the line
        free(temp);
        (*buffer_index)++;
    }

    // If we encountered a newline, add it to the line
    if (*buffer_index < buffer_size && buffer[*buffer_index] == '\n')
    {
        temp = malloc(1);
        if (!temp)
            return NULL;

        temp[0] = '\n';  // Add newline to line
        line = ft_strjoin(line, temp);  // Append the newline
        free(temp);

        (*buffer_index)++;  // Move past the newline
    }

    return line;
}

char *fun(int fd)
{
    static char buffer[42];
    static int buffer_index = 0;
    static int buffer_size = 0;
    char *line;

    // Read from file if necessary
    if (read_from_fd(fd, buffer, &buffer_index, &buffer_size) <= 0)
        return NULL;

    // Build and return the next line from the buffer
    line = build_line_from_buffer(buffer, &buffer_index, buffer_size);
    if (!line)
        return NULL;

    return line;
}
