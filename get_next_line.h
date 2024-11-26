/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:07:18 by mabdelha          #+#    #+#             */
/*   Updated: 2024/11/26 17:43:16 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 40
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*ft_append_char(char *ligne, char c);
int		ft_read_from_fd(int fd, char *tab);

#endif
