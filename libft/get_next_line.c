/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:16:38 by lle-duc           #+#    #+#             */
/*   Updated: 2024/12/24 14:53:52 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*check_remainder(char **remainder)
{
	int		pos;
	char	*line;
	char	*temp;

	pos = -1;
	if (*remainder)
	{
		while ((*remainder)[++pos] != '\0')
		{
			if ((*remainder)[pos] == '\n')
				break ;
		}
		if ((*remainder)[pos] == '\n')
		{
			line = ft_substr(*remainder, 0, pos + 1);
			temp = ft_substr(*remainder, pos + 1, ft_strlen(*remainder));
			free(*remainder);
			*remainder = temp;
			return (line);
		}
	}
	return (NULL);
}

static int	read_from_fd(int fd, char **buffer)
{
	int	bytes_read;

	*buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!*buffer)
		return (-1);
	bytes_read = read(fd, *buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(*buffer);
		*buffer = NULL;
		return (-1);
	}
	(*buffer)[bytes_read] = '\0';
	return (bytes_read);
}

static int	read_and_update(int fd, char **remainder)
{
	char	*buffer;
	int		bytes_read;
	char	*temp;

	bytes_read = read_from_fd(fd, &buffer);
	if (bytes_read == -1)
	{
		free(*remainder);
		*remainder = NULL;
		return (-1);
	}
	if (!*remainder)
		*remainder = ft_strdup(buffer);
	else
	{
		temp = ft_strjoin(*remainder, buffer);
		free(*remainder);
		*remainder = temp;
	}
	free(buffer);
	if (bytes_read == 0)
		return (0);
	return (1);
}

static char	*file_end(char **remainder)
{
	char	*line;

	if (*remainder && **remainder)
	{
		line = ft_strdup(*remainder);
		free(*remainder);
		*remainder = NULL;
		return (line);
	}
	free(*remainder);
	*remainder = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*remainder[1024];
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		line = check_remainder(&remainder[fd]);
		if (line)
			return (line);
		bytes_read = read_and_update(fd, &remainder[fd]);
		if (bytes_read == -1)
			return (NULL);
		if (bytes_read == 0)
			break ;
	}
	return (file_end(&remainder[fd]));
}

/*
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void) {
	char *line;
	int fd1, fd2;

	fd1 = open("1char.txt", O_RDONLY);
	fd2 = open("read_error.txt", O_RDONLY);

	if (fd1 == -1 || fd2 == -1) {
		perror("Erreur d'ouverture des fichiers");
		if (fd1 != -1) close(fd1);
		if (fd2 != -1) close(fd2);
		return (1);
	}

	line = get_next_line(fd1);
	printf("FD1 - Ligne lue : %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("FD2 - Ligne lue : %s", line);
	free(line);

	line = get_next_line(fd1);
	printf("FD1 - Ligne lue : %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("FD2 - Ligne lue : %s", line);
	free(line);

	line = get_next_line(fd1);
	printf("FD1 - Ligne lue : %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("FD2 - Ligne lue : %s", line);
	free(line);

	line = get_next_line(fd1);
	printf("FD1 - Ligne lue : %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("FD2 - Ligne lue : %s", line);
	free(line);

	line = get_next_line(fd1);
	printf("FD1 - Ligne lue : %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("FD2 - Ligne lue : %s", line);
	free(line);

	line = get_next_line(fd1);
	printf("FD1 - Ligne lue : %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("FD2 - Ligne lue : %s", line);
	free(line);

	close(fd1);
	close(fd2);

	return (0);
}
*/