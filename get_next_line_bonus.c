/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:27:52 by jose-ero          #+#    #+#             */
/*   Updated: 2023/11/04 18:00:22 by jose-ero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_new_line(char *stash);
char	*get_rest(char *stash);
void	*ft_free(char **stash, char **buffer);

char	*get_next_line(int fd)
{
	int				read_len;
	char			*buffer;
	char			*line;
	static char		*stash[MAX_OFILE];

	read_len = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_OFILE)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (!(ft_find_newline(buffer)) && read_len != 0)
	{
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len == -1)
			return (ft_free(&stash[fd], &buffer));
		buffer[read_len] = '\0';
		stash[fd] = ft_join_stash(stash[fd], buffer);
	}
	line = get_new_line(stash[fd]);
	stash[fd] = get_rest(stash[fd]);
	free(buffer);
	return (line);
}

char	*get_new_line(char *stash)
{
	char	*line;
	int		i;

	if (!*stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = stash[i];
	return (line);
}

char	*get_rest(char *stash)
{
	char	*rest;
	int		i;
	int		index;

	index = 0;
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	rest = ft_calloc(ft_strlen(stash) - i + 1, sizeof(char));
	while (stash[i])
		rest[index++] = stash[++i];
	rest[index] = '\0';
	free(stash);
	return (rest);
}

void	*ft_free(char **stash, char **buffer)
{
	free(*buffer);
	free(*stash);
	*stash = NULL;
	return (NULL);
}

// int main(void)
// {
// 	int 	fd;
// 	int		i;
// 	char 	*ptr;

// 	i = 0;
// 	while (i < 22)
// 	{
// 		fd = open("text.txt", O_RDONLY);
// 		ptr = get_next_line(fd);
// 		printf("%s", ptr);
// 		free(ptr);
// 		i++;
// 	}
// }
