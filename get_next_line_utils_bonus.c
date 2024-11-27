/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:06:02 by mabdelha          #+#    #+#             */
/*   Updated: 2024/11/26 17:04:57 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	ft_read_from_fd(int fd, char *tab)
{
	int	count;

	if (!tab)
		return (-1);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	count = read(fd, tab, BUFFER_SIZE);
	if (count < 0)
	{
		tab[0] = '\0';
		return (-1);
	}
	tab[count] = '\0';
	return (count);
}

char	*ft_append_char(char *ligne, char c)
{
	int		len;
	char	*n_ligne;
	int		i;

	len = ft_strlen(ligne);
	n_ligne = malloc(len + 2);
	if (!n_ligne)
	{
		free(ligne);
		return (NULL);
	}
	i = 0;
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
