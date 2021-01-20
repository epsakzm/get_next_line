/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeopark <hyeopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:26:03 by hyeopark          #+#    #+#             */
/*   Updated: 2021/01/20 15:42:25 by hyeopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static	int		ft_copyline(t_buff *find, char **line)
{
	size_t	i;
	size_t	j;
	int		found;

	i = ft_strlen(*line);
	if (!ft_realloc(line, i))
		return (-1);
	found = 0;
	j = 0;
	while (find->buffer[j])
	{
		(*line)[i++] = find->buffer[j];
		if (find->buffer[j++] == '\n')
		{
			--i;
			found = 1;
			break ;
		}
	}
	(*line)[i] = 0;
	i = 0;
	while (find->buffer[j])
		find->buffer[i++] = find->buffer[j++];
	find->buffer[i] = 0;
	return (found);
}

static	int		ft_error(char **line)
{
	if (*line)
		free(*line);
	*line = 0;
	return (-1);
}

int				get_next_line(int fd, char **line)
{
	static t_buff	*head;
	t_buff			*find;
	int				ret;
	int				rd_size;

	if (BUFFER_SIZE <= 0 || fd < 0 || !line
		|| (!head && !(head = ft_lstnew(fd)))
		|| !(find = ft_getbuffer(fd, head)))
		return (-1);
	*line = 0;
	if ((ret = ft_copyline(find, line)))
		return (ret);
	while ((rd_size = read(fd, find->buffer, BUFFER_SIZE)) > 0)
	{
		find->buffer[rd_size] = 0;
		if ((ret = ft_copyline(find, line)))
			return (ret);
	}
	if (rd_size < 0)
		return (ft_error(line));
	ft_cleanbuffer(&head, fd);
	return (ret);
}
