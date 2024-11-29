/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:10:34 by mabdelha          #+#    #+#             */
/*   Updated: 2024/11/29 11:18:56 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

typedef struct s_gnl_state
{
	char	tab[BUFFER_SIZE];
	int		j;
	int		i;
}			t_gnl_state;

static int	ft_eof(int j, char **ligne)
{
	if (j == -1 || (j == 0 && **ligne == '\0'))
	{
		free(*ligne);
		*ligne = NULL;
		return (0);
	}
	return (1);
}

static int	ft_ster_bster(int fd, t_gnl_state tab[1024], char **ligne)
{
	if (tab[fd].i >= tab[fd].j)
	{
		tab[fd].j = ft_read_from_fd(fd, tab[fd].tab);
		if (tab[fd].j <= 0)
			return (ft_eof(tab[fd].j, ligne));
		tab[fd].i = 0;
	}
	*ligne = ft_append_char(*ligne, tab[fd].tab[tab[fd].i]);
	if (!*ligne)
		return (0);
	if (tab[fd].tab[tab[fd].i] == '\n' || tab[fd].tab[tab[fd].i] == '\0')
	{
		tab[fd].i++;
		return (1);
	}
	tab[fd].i++;
	return (-1);
}

static char	*ft_alloc(void)
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
	static t_gnl_state	tab[1024] = {{{0}, 0, 0}};
	char				*ligne;
	int					result;

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
		{
			free(ligne);
			return (NULL);
		}
	}
	return (ligne);
}
