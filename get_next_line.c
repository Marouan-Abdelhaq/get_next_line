/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:10:34 by mabdelha          #+#    #+#             */
/*   Updated: 2024/11/25 08:41:29 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_chehal_9rity(int fd, char *tab)
{
	int	count;

	count = read(fd, tab, BUFFER_SIZE);
	if (count < 0)
		return (-1);
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

static char	*ft_ster_bster(int fd, char *tab, char **ligne)
{
	static int	j;
	static int	i;

	if (i == j)
	{
		j = ft_chehal_9rity(fd, tab);
		if (j <= 0)
		{
			if (*ligne[0] == '\0')
			{
				free(*ligne);
				return (NULL);
			}
			break ;
		}
		i = 0;
	}
	*ligne = ft_href_bheref(*ligne, tab[i]);
	if (tab[i] == '\n' || tab[i] == '\0')
	{
		i++;
		return (1);
	}
	i++;
	return (-1);
}

static char	*ft_ster_bster2(int fd, char *tab)
{
	static int	j;
	static int	i;
	char		*ligne;

	ligne = ft_alloc();
	while (1)
	{
		if ((ft_ster_bster(fd, tab, &ligne)) == 0)
			break ;
		if ((ft_ster_bster(fd, tab, &ligne)) == -1)
			return (NULL);
	}
	return (ligne);
}

char	*get_next_line(int fd)
{
	static char	tab[BUFFER_SIZE + 1];
	char		*ligne;

	ligne = ft_ster_bster(fd, tab);
	if (!ligne || ligne[0] == '\0')
	{
		free(ligne);
		return (NULL);
	}
	return (ligne);
}
