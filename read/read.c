#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len_s1;
	int		len_s2;
	int		i;
	int		j;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str)
		return (NULL);
	while (i < len_s1)
	{
		str[i] = s1[i];
		i++;
	}
	while (j < len_s2)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

static char  *fun_lin(int fd, char *tab)
{
	static int i = 0;;
	static int j = 0;
	int count = 0;
	char tmp[2];
	char *n_ligne;
	char *ligne = malloc(1);

	if (!ligne)
		return NULL;
	ligne[0] = '\0';
	tmp[1] = '\0';
	if (i == j)
	{
		count = read(fd, tab, 42);
		if (count < 0)
		{
			free(ligne);
			return NULL;
		}
		if (count == 0)
		{
			free(ligne);
			return NULL;
		}
		j = count;
		i = 0;
	}
	while (i < j && tab[i] != '\n')
	{
		tmp[0] = tab[i];
		if (!tmp)
			return NULL;
		n_ligne = ft_strjoin(ligne, tmp);
		if (!n_ligne)
		{
			free(ligne);
			return NULL;
		}
		free(ligne);
		ligne = n_ligne;
		i++;
	}
	if (i < j && tab[i] == '\n')
	{
                tmp[0] = '\n';
                n_ligne = ft_strjoin(ligne, tmp);
                if (!n_ligne)
                {
                        free(ligne);
                        return NULL;
                }
                free(ligne);
                ligne = n_ligne;
                i++;

	}
	return ligne;
}

char *fun(int fd)
{
	static char tab[42];
	char *ligne;

	ligne = fun_lin(fd, tab);
	if (!ligne || ligne[0] == '\0')
		return NULL;
	return ligne;
}

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }
        printf("%s", fun(fd));
	printf("%s", fun(fd));
	printf("%s", fun(fd));
printf("%s", fun(fd));


    close(fd);
    return (0);
}
