#include "get_next_line.h"

static int	ft_read_from_fd(int fd, char *buffer)
{
	int bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (-1);
	buffer[bytes_read] = '\0';
	return (bytes_read);
}

static char	*ft_alloc(void)
{
	char	*line;

	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	return (line);
}

static char	*ft_append_char(char *line, char c)
{
	char	*new_line;
	size_t len = 0;

	while (line[len])
		len++;
	new_line = malloc(len + 2); // +1 for the new char, +1 for '\0'
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	for (size_t i = 0; i < len; i++)
		new_line[i] = line[i];
	new_line[len] = c;
	new_line[len + 1] = '\0';
	free(line);
	return (new_line);
}

static int	ft_process_buffer(int fd, char *buffer, char **line)
{
	static int buffer_index = 0;
	static int bytes_in_buffer = 0;

	if (buffer_index >= bytes_in_buffer)
	{
		bytes_in_buffer = ft_read_from_fd(fd, buffer);
		buffer_index = 0;
		if (bytes_in_buffer <= 0)
		{
			if (**line == '\0')
			{
				free(*line);
				return (0);
			}
			return (1);
		}
	}
	*line = ft_append_char(*line, buffer[buffer_index]);
	if (buffer[buffer_index] == '\n' || buffer[buffer_index] == '\0')
	{
		buffer_index++;
		return (1);
	}
	buffer_index++;
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_alloc();
	if (!line)
		return (NULL);
	while (1)
	{
		int result = ft_process_buffer(fd, buffer, &line);
		if (result == 0 || result == -1)
			return (NULL);
		if (result == 1)
			break;
	}
	return (line);
}
