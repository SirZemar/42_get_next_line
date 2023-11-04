/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:26:54 by jose-ero          #+#    #+#             */
/*   Updated: 2023/11/04 17:59:38 by jose-ero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_new_line(char *stash);
char	*get_rest(char *stash);
void	*ft_free(char **stash, char **buffer);

char	*get_next_line(int fd)
{
	int				read_len;
	char			*buffer;
	char			*line;
	static char		*stash;

	read_len = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (!(ft_find_newline(buffer)) && read_len != 0)
	{
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len == -1)
			return (ft_free(&stash, &buffer));
		buffer[read_len] = '\0';
		stash = ft_join_stash(stash, buffer);
	}
	line = get_new_line(stash);
	stash = get_rest(stash);
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
	int		j;

	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!*stash)
	{
		free(stash);
		return (NULL);
	}
	rest = ft_calloc(ft_strlen(stash) - i + 1, sizeof(char));
	while (stash[i])
		rest[j++] = stash[++i];
	rest[j] = '\0';
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

// int main()
// {
//     int fd1;

//     char *ptr;
	
//     fd1 = open("text.txt", O_RDONLY);
//     ptr = get_next_line(fd1);
//     printf("%s", ptr);
//     free(ptr);
// }
