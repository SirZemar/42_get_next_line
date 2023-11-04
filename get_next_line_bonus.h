/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:27:41 by jose-ero          #+#    #+#             */
/*   Updated: 2023/11/04 18:00:14 by jose-ero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_OFILE
#  define MAX_OFILE FOPEN_MAX
# endif

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_find_newline(char *ptr);
size_t	ft_strlen(const char *s);
char	*ft_join_stash(char *stash, char *buffer);
char	*get_next_line(int fd);

#endif