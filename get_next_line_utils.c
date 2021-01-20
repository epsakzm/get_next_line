/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeopark <hyeopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:06:18 by hyeopark          #+#    #+#             */
/*   Updated: 2021/01/20 15:55:07 by hyeopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buff	*ft_lstnew(int fd)
{
	t_buff	*out;

	if (!(out = (t_buff*)malloc(sizeof(t_buff))))
		return (out);
	out->fd = fd;
	out->next = 0;
	out->buffer[0] = 0;
	return (out);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

t_buff	*ft_getbuffer(int fd, t_buff *buffer)
{
	if (buffer->fd == fd)
		return (buffer);
	if (!buffer->next)
		return (buffer->next = ft_lstnew(fd));
	return (ft_getbuffer(fd, buffer->next));
}

int		ft_realloc(char **line, size_t len)
{
	char	*newbuff;
	size_t	i;

	if ((newbuff = (char*)malloc(len + BUFFER_SIZE + 1)) == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		newbuff[i] = (*line)[i];
		++i;
	}
	newbuff[i] = 0;
	free(*line);
	*line = newbuff;
	return (1);
}

void	ft_cleanbuffer(t_buff **toclean, int fd)
{
	t_buff	*temp;
	t_buff	*old;

	temp = *toclean;
	if (temp->fd == fd)
	{
		old = temp->next;
		free(temp);
		*toclean = old;
		return ;
	}
	while (temp->next->fd != fd)
		temp = temp->next;
	old = ft_getbuffer(fd, *toclean);
	temp->next = old->next;
	free(old);
}
