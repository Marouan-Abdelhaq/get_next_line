/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:10:34 by mabdelha          #+#    #+#             */
/*   Updated: 2024/11/24 11:56:54 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int ft_chehal_9rity(int fd, char *tab)
{
    int count;

    count = read(fd, tab, BUFFER_SIZE);
    if (count < 0)
        return (-1);
    tab[count] = '\0';
    return (count);
}

static char *ft_href_bheref(char *ligne, char c)
{
    char tmp[2];
    char *n_ligne;

    tmp[0] = c;
    tmp[1] = '\0';
    n_ligne = ft_strjoin(ligne, tmp);
    if (!n_ligne)
    {
        free (ligne);
        return (NULL);
    }
    free (ligne);
    return (n_ligne);
}
static void *ft_alloc()
{
    char *ligne;

    ligne = malloc(1);
    if (!ligne)
        return (NULL);
    ligne[0] = '\0';
    return (ligne);
}
static char *ft_ster_bster(int fd, char *tab)
{
    static int  j;
    static int  i;
    char *ligne;

    ligne = ft_alloc();
    while (1)
    {
        if (i == j)
        {
            j = ft_chehal_9rity(fd, tab);
            if (j <= 0)
            {
                if (ligne[0] == '\0') return (NULL);
                break;
            }
            i = 0;
        }
        ligne = ft_href_bheref(ligne, tab[i]);
        if (tab[i] == '\n' || tab[i] == '\0')
        {
            i++;
            break;
        }
        i++;
    }
    return (ligne);
}

char *get_next_line(int fd)
{
    static char tab[BUFFER_SIZE + 1];
    char    *ligne;

    ligne = ft_ster_bster(fd, tab);
    if (!ligne || ligne[0] == '\0')
        return (NULL);
    return (ligne);
}
