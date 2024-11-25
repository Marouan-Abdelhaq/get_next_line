/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:10:34 by mabdelha          #+#    #+#             */
/*   Updated: 2024/11/25 13:57:58 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_read_from_fd(int fd, char *tab)
{
	int	count;

	count = read(fd, tab, BUFFER_SIZE);
	if (count < 0)
	{
		tab[0] = '\0';
		return (-1);
	}
	tab[count] = '\0';
	return (count);
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

static char	*ft_append_char(char *ligne, char c)
{
	int		len;
	char	*n_ligne;
	int		i;

	len = ft_strlen(ligne);
	n_ligne = malloc(len + 2);
	i = 0;
	if (!n_ligne)
	{
		free(ligne);
		return (NULL);
	}
	while (i < len)
	{
		n_ligne[i] = ligne[i];
		i++;
	}
	n_ligne[len] = c;
	n_ligne[len + 1] = '\0';
	free(ligne);
	return (n_ligne);
}

static int	ft_ster_bster(int fd, char *tab, char **ligne)
{
	static int	j;
	static int	i;

	if (i >= j)
	{
		j = ft_read_from_fd(fd, tab);
		i = 0;
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
	}
	*ligne = ft_append_char(*ligne, tab[i]);
	if (!*ligne)
		return (0);
	if (tab[i] == '\n' || tab[i] == '\0')
	{
		i++;
		return (1);
	}
	i++;
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	tab[BUFFER_SIZE + 1];
	char		*ligne;
	int			result;

	result = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ligne = ft_alloc();
	if (!ligne)
		return (NULL);
	while (1)
	{
		result = ft_ster_bster(fd, tab, &ligne);
		if (result == 1)
			break;
		if (result == 0)
			return (NULL);
	}
	return (ligne);
}
