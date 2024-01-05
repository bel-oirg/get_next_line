/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:21:07 by bel-oirg          #+#    #+#             */
/*   Updated: 2023/12/06 10:04:48 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_out(int fd, char *out_free)
{
	if (fd >= 0 && fd < OPEN_MAX && out_free != NULL)
	{
		free(out_free);
		out_free = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*out[OPEN_MAX];
	char		*buf;
	ssize_t		readen;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0
		|| BUFFER_SIZE > 2147479552 || read(fd, 0, 0) < 0)
		return (free_out(fd, out[fd]), NULL);
	if (have_n(out[fd]))
		return (print_line(&out[fd]));
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	readen = 1;
	while (readen > 0)
	{
		readen = read(fd, buf, BUFFER_SIZE);
		buf[readen] = 0;
		out[fd] = ft_strjoin(out[fd], buf);
		if (have_n(out[fd]))
			break ;
	}
	if (buf)
		free(buf);
	buf = NULL;
	return (print_line(&out[fd]));
}
