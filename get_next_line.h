/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeopark <hyeopark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:57:43 by hyeopark          #+#    #+#             */
/*   Updated: 2021/01/19 19:58:07 by hyeopark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

typedef	struct	s_buff
{
	int				fd;
	char			buffer[BUFFER_SIZE + 1];
	struct s_buff	*next;
}				t_buff;

t_buff			*ft_lstnew(int fd);
t_buff			*ft_getbuffer(int fd, t_buff *buffer);
int				get_next_line(int fd, char **line);
size_t			ft_strlen(const char *s);
int				ft_realloc(char **line, size_t len);
void			ft_freebuffer(t_buff *head, int fd);
void			ft_cleanbuffer(t_buff **toclean, int fd);

#endif
