/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhatamle <mhatamle@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 10:33:17 by mhatamle          #+#    #+#             */
/*   Updated: 2026/10/03 11:05:36 by mhatamle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*buffer;
	static char	*leftover;
	char	*line;
	char	*new_leftover;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if(read_until_newline(fd, buffer, &leftover) < 0)
		return (free(buffer), NULL);
	line = get_line(leftover);
	new_leftover = get_leftover(leftover);
	free(leftover);
	leftover = new_leftover;
	free (buffer);
	return (line);
}

static int	read_until_newline(int fd, char *buffer, char **leftover)
{
	int	bytes;
	size_t	i;

	if(!*leftover)
	{
		*leftover = ft_strdup("");
		if(!*leftover)
			return (-1);
	}
	i = find_newline(*leftover);
	while((*leftover)[i] != '\n')
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if(bytes < 0)
			return (-1);
		if(bytes == 0)
			break;
		buffer[bytes] = '\0';
		*leftover = join_buffer(*leftover, buffer);
		if(!*leftover)
			return (-1);
		i = find_newline(*leftover);
	}
	return (0);
}