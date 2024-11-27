/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:10:34 by mabdelha          #+#    #+#             */
/*   Updated: 2024/11/27 16:56:53 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

typedef struct s_gnl_state {
    char tab[BUFFER_SIZE + 1];
    int j;
    int i;
} t_gnl_state;

static int ft_eof(int j, char **ligne) {
    if (j == -1 || (j == 0 && **ligne == '\0')) {
        free(*ligne);
        *ligne = NULL;
        return (0);
    }
    return (1);
}

static int	ft_ster_bster(int fd, t_gnl_state state[1024], char **ligne) {
    if (state[fd].i >= state[fd].j) {
        state[fd].j = ft_read_from_fd(fd, state[fd].tab);
        if (state[fd].j <= 0)
            return (ft_eof(state[fd].j, ligne));
        state[fd].i = 0;
    }
    *ligne = ft_append_char(*ligne, state[fd].tab[state[fd].i]);
    if (!*ligne)
        return (0);
    if (state[fd].tab[state[fd].i] == '\n' || state[fd].tab[state[fd].i] == '\0') {
        state[fd].i++;
        return (1);
    }
    state[fd].i++;
    return (-1);
}

static char	*ft_alloc(void) {
    char *ligne;

    ligne = malloc(1);
    if (!ligne)
        return (NULL);
    ligne[0] = '\0';
    return (ligne);
}

char *get_next_line(int fd) {
    static t_gnl_state state[1024] = {{{0}, 0, 0}};
    char *ligne;
    int result;

    if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
        return (NULL);

    ligne = ft_alloc();
    if (!ligne)
        return (NULL);

    while (1) {
        result = ft_ster_bster(fd, state, &ligne);
        if (result == 1)
            break;
        if (result == 0) {
            return (NULL);
        }
    }
    return (ligne);
}
