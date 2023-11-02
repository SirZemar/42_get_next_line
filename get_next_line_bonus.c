/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-ero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:27:52 by jose-ero          #+#    #+#             */
/*   Updated: 2023/11/02 21:27:53 by jose-ero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_new_line(char *stash)
{
	char	*tmp;
	int		i;

	if (!*stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	tmp = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		tmp[i] = stash[i];
		i++;
	}
	tmp[i] = stash[i];
	return (tmp);
}

char	*get_rest(char *stash)
{
	char	*tmp;
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
	tmp = ft_calloc(ft_strlen(stash) - i + 1, sizeof(char));
	while (stash[i])
		tmp[index++] = stash[++i];
	tmp[index] = '\0';
	free(stash);
	return (tmp);
}

void	*ft_free(char **stash, char **buffer)
{
	free(*buffer);
	free(*stash);
	*stash = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	int				read_len;
	char			*buffer;
	char			*line;
	static char		*stash[FOPEN_MAX];

	read_len = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
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

/* 
int main()
{
    int fd1;
	int fd2;

    char *ptr;
	char *ptr2;
	
    fd1 = open("arquivo1.txt", O_RDONLY);
    ptr = get_next_line(fd1);
    printf("%s", ptr);
    free(ptr);

	fd2 = open("arquivo2.txt", O_RDONLY);
    ptr2 = get_next_line(fd2);
    printf("%s", ptr2);
    free(ptr2);

	ptr = get_next_line(fd1);
	printf("%s", ptr);
	free(ptr);
} */