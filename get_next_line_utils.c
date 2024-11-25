/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:06:02 by mabdelha          #+#    #+#             */
/*   Updated: 2024/11/25 18:44:28 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

int	ft_read_from_fd(int fd, char *tab)
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

char	*ft_append_char(char *ligne, char c)
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
