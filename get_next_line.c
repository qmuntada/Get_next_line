/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 16:04:03 by qmuntada          #+#    #+#             */
/*   Updated: 2015/02/05 16:54:10 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		check_buf(char *buf, int pivot, char **line)
{
	int				start;
	char			*str;

	start = (pivot -= 1) + 1;
	while (++pivot < BUFF_SIZE)
		if (buf[pivot] == '\n')
		{
			str = ft_memalloc(ft_strlen(*line) + ft_strlen(buf));
			str = ft_strcpy(str, *line);
			str = ft_strncat(str, buf, ++pivot);
			*line = str;
			return (pivot);
		}
	str = ft_memalloc(ft_strlen(*line) + ft_strlen(buf + start));
	str = ft_strcpy(str, *line);
	str = ft_strncat(str, buf + start, pivot - start);
	*line = str;
	return (-1);
}

int		get_next_line(int fd, char **line)
{
	static char		buf[BUFF_SIZE + 1];
	static int		pivot = 0;
	int				status;

	if (fd < 0 || !line || BUFF_SIZE > 100000)
		return (-1);
	*line = ft_strnew(1);
	pivot = check_buf(buf, pivot, line);
	if (pivot >= 0)
		return (1);
	while ((status = read(fd, buf, BUFF_SIZE)) > 0)
	{
		pivot = check_buf(buf, 0, line);
		if (pivot >= 0)
			return (1);
	}
	return (status);
}
