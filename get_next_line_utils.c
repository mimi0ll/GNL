/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhatamle <mhatamle@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 11:05:49 by mhatamle          #+#    #+#             */
/*   Updated: 2026/10/03 14:13:18 by mhatamle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	 strlen(char const *str)
{
	size_t	i;

	i = 0;
	
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *old)
{
	char	*copy;
	size_t	len;
	size_t	i;

	i = 0;
	len = strlen(old) + 1;
	copy = malloc(len);
	if (!copy)
		return (NULL);
	while (old[i])
	{
		copy[i] = old[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
	
char	*strjoin(char const *old, char const *buffer)
{
	size_t	i;
	size_t	j;
	char	*join;

	i = 0;
	j = 0;
	if (!buffer)
		return (NULL);
	if (!old)
		return (ft_strdup(buffer));
	join = malloc (strlen(old) + strlen(buffer) + 1);
	if (!join)
		return (NULL);
	while (old[j])
		join[i++] = old[j++];
	j = 0;
	while (buffer[j])
		join[i++] = buffer[j++];
	join [i] = '\0';
	return (join);
}

char	*join_buffer(char *static_str, char *buffer)
{
	char	*temp;

	temp = strjoin(static_str, buffer);
	free(static_str);
	return (temp);
}

size_t	find_newline(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] &&str[i] != '\n')
		i++;
	return (i);
}

char	*get_line(char *leftover)
{
	size_t	i;
	size_t	x;
	char	*line;

	i = 0;
	while (leftover[i] && leftover[i] != '\n')
		i++;
	if (leftover[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	x = 0;
	while (x != i)
	{
		line[x] = leftover[x];
		x++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_leftover(char	*str)
{
	size_t	i;
	size_t	len;
	char	*leftover;
	size_t	j;

	i = find_newline(str);
	if(!str[i])
		return (ft_strdup(""));
	i++;
	len = strlen(str) - i;
	leftover = malloc(len + 1);
	if(!leftover)
		return (NULL);
	j = 0;
	while (str[i])
	{
		leftover[j++] = str[i++];
	}
	leftover[j] = '\0';
	return(leftover);
}