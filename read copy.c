
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>

static char *read_line(int fd, char *buffer)
{
    char *line = NULL;
    char *temp = NULL;
    int count;
    static int i = 0;
    static int j = 0;

    while (1)
    {
        // If buffer is empty, fill it
        if (i == j)
        {
            count = read(fd, buffer, 42);
            if (count == 0)  // End of file
                break;
            if (count < 0)  // Read error
                return (NULL);
            j = count;
            i = 0;
        }
        
        // Look for a newline in the current buffer
        while (i < j && buffer[i] != '\n')
        {
            temp = malloc(1);
            if (!temp)
                return (NULL);

            temp[0] = buffer[i];
            line = ft_strjoin(line, temp); // Append the character to the line
            free(temp);

            i++;
        }

        // If we find a newline, break
        if (i < j && buffer[i] == '\n')
        {
            temp = malloc(1);
            if (!temp)
                return (NULL);
            
            temp[0] = '\n';
            line = ft_strjoin(line, temp); // Append the newline
            free(temp);

            i++;  // Skip over the newline
            break;
        }
    }
    return (line);
}

char *fun(int fd)
{
    static char buffer[42];
    char *line;

    line = read_line(fd, buffer);
    if (!line || line[0] == '\0') // End of file or error
        return (NULL);
    return (line);
}
