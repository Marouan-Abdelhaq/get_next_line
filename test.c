#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42 // Valeur par défaut si BUFFER_SIZE n'est pas défini
#endif

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42 // Valeur par défaut si BUFFER_SIZE n'est pas défini
#endif

size_t	ft_strlen(const char *str)
{
	size_t i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len_s1)
	{
		str[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		str[i++] = *s2++;
	}
	str[i] = '\0';
	return (str);
}

static int ft_read(int fd, char *tab)
{
	int count = read(fd, tab, BUFFER_SIZE);
	if (count < 0)
	{
		return -1;
	}
	tab[count] = '\0'; // Null terminate the buffer
	return count;
}

static char *append_c(char *ligne, char c)
{
	char tmp[2] = {c, '\0'};
	char *n_ligne = ft_strjoin(ligne, tmp);
	free(ligne);
	return n_ligne;
}

static char *build_l(char *ligne)
{
	return append_c(ligne, '\n');
}

static char *fun_lin(int fd, char *tab)
{
	static int i = 0;
	static int j = 0;
	char *ligne = malloc(1);
	if (!ligne)
		return NULL;
	ligne[0] = '\0';

	if (i == j)
	{
		j = ft_read(fd, tab);
		if (j <= 0)
		{
			free(ligne);
			return NULL; // Return NULL if no more data
		}
		i = 0;
	}

	while (i < j && tab[i] != '\n')
	{
		ligne = append_c(ligne, tab[i]);
		i++;
	}
	if (i < j && tab[i] == '\n')
	{
		ligne = build_l(ligne);
		i++;
	}
	return ligne;
}

char *get_next_line(int fd)
{
	static char tab[BUFFER_SIZE + 1]; // Use BUFFER_SIZE defined at compile time
	return fun_lin(fd, tab);
}

// Example usage
int main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return 1;
	}

	int fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return 1;
	}

	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return 0;
}