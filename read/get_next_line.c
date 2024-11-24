/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 02:23:08 by mabdelha          #+#    #+#             */
/*   Updated: 2024/11/24 02:23:09 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"


static int ft_read(int fd, char *tab)
{
	int count = 0;
	count = read(fd, tab, BUFFER_SIZE);
	if (count < 0)
	{
		return -1;
	}
	tab[count] = '\0';
	return (count);
}

static char *append_c(char *ligne, char c)
{
	char tmp[2];
	char *n_ligne;
	tmp[0] = c;
	tmp[1] = '\0';
	n_ligne = ft_strjoin(ligne, tmp);
	if (!n_ligne)
	{
		free(ligne);
		return NULL;
	}
	free(ligne);
	return n_ligne;
}
void *alloc()
{
	char *ligne = malloc(1);

	if (!ligne)
		return NULL;
	ligne[0] = '\0';
	return ligne;
}
char *ft_proce(char *ligne, char *tab, int *i)
{
		if (tab[*i] == '\n' || tab[*i] == '\0')
	{
		ligne = append_c(ligne, '\n');
		(*i)++;
	}
	else
	{
        ligne = append_c(ligne, tab[*i]);
        (*i)++;
	}
	return (ligne);
}

static char  *fun_lin(int fd, char *tab)
{
	static int i = 0;
	static int j = 0;
	char *ligne = alloc();

	while (1)
	{
		if (i == j)
	{
		j = ft_read(fd, tab);
		if (j <= 0)
		{
			if (ligne[0] == '\0')
				return NULL;
		}
		i = 0;
	}
	ligne = ft_proce(ligne, tab, &i);
	if (tab[i] == '\n' || tab[i] == '\0')
		break;;
	}
	return ligne;
}

char *get_next_line(int fd)
{
	static char tab[BUFFER_SIZE + 1];
	char *ligne;

	ligne = fun_lin(fd, tab);
	if (!ligne || ligne[0] == '\0')
		return NULL;
	return ligne;
}
