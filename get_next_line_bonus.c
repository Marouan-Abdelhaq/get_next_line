/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:10:34 by mabdelha          #+#    #+#             */
/*   Updated: 2024/11/26 16:45:17 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
static int	ft_eof(int j, char **ligne)
{
	if (j == -1)
	{
		free(*ligne);
		return (0);
	}
	if (j == 0)
	{
		if (**ligne == '\0')
		{
			free(*ligne);
			return (0);
		}
		return (1);
	}
	return (-1);
}

static int	ft_ster_bster(int fd, char tab[1024][BUFFER_SIZE + 1], char **ligne)
{
	static int	j[1024] = {0};
	static int	i[1024] = {0};

	if (i[fd] >= j[fd])
	{
		j[fd] = read(fd, tab, BUFFER_SIZE);
		if (j[fd] <= 0)
			return (ft_eof(j[fd], ligne));
		i[fd] = 0;
	}
	*ligne = ft_append_char(*ligne, tab[fd][i[fd]]);
	if (!*ligne)
		return (0);
	if (tab[fd][i[fd]] == '\n' || tab[fd][i[fd]] == '\0')
	{
		i[fd]++;
		return (1);
	}
	i[fd]++;
	return (-1);
}

static void	*ft_alloc(void)
{
	char	*ligne;

	ligne = malloc(1);
	if (!ligne)
		return (NULL);
	ligne[0] = '\0';
	return (ligne);
}

char	*get_next_line(int fd)
{
	static char	tab[1024][BUFFER_SIZE + 1];
	char		*ligne;
	int			result;

	result = 0;
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	ligne = ft_alloc();
	if (!ligne)
		return (NULL);
	while (1)
	{
		result = ft_ster_bster(fd, tab, &ligne);
		if (result == 1)
			break ;
		if (result == 0)
			return (NULL);
	}
	return (ligne);
}
#include <fcntl.h>
#include <stdio.h>
int main()
{
	int fd = open("test.txt", O_RDONLY);
	int jd = open("t.txt", O_RDONLY);
	int cd = open("te.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(jd));
	printf("%s", get_next_line(cd));
	
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(jd));
	printf("%s", get_next_line(cd));
	
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(jd));
	printf("%s", get_next_line(cd));
}