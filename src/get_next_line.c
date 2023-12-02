/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:22:45 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/17 16:32:43 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char	*malloc_size(char **line, char *buf)
{
	char	*ret;
	int		line_len;
	int		buf_len;

	line_len = 0;
	while (*line && (*line)[line_len] && (*line)[line_len] != '\n')
		line_len++;
	buf_len = 0;
	while (buf[buf_len] && buf[buf_len] != '\n')
		buf_len++;
	ret = (char *)malloc(sizeof(char) * (buf_len + line_len + 1));
	if (!ret)
		return (free(buf), NULL);
	return (ret);
}

static int	add_to_line(char **line, char *buf)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = malloc_size(line, buf);
	if (!tmp)
		return (free(line), -1);
	i = 0;
	j = 0;
	while (*line && (*line)[i] && (*line)[i] != '\n')
		tmp[i++] = (*line)[j++];
	j = 0;
	while (buf[j] && buf[j] != '\n')
		tmp[i++] = buf[j++];
	tmp[i] = buf[j];
	free(*line);
	*line = tmp;
	i = 0;
	while (buf[j])
		buf[i++] = buf[++j];
	buf[i] = '\0';
	i = 0;
	while ((*line)[i] && (*line)[i] != '\n')
		i++;
	return (i);
}

int	do_what_i_want_now(char **line, int ret)
{
	if (ret != -1 && *line && **line)
		return (1);
	if (ret < 0)
	{
		free(*line);
		*line = NULL;
	}
	return (ret);
}

static int	gnl(int fd, char **line)
{
	static char		buf[FD_MAX][BUFFER_SIZE + 1];
	int				ret;

	*line = NULL;
	ret = add_to_line(line, buf[fd]);
	while (ret != -1 && (*line)[ret] != '\n')
	{
		ret = read(fd, buf[fd], BUFFER_SIZE);
		if (ret < 1)
			return (do_what_i_want_now(line, ret));
		buf[fd][ret] = '\0';
		ret = add_to_line(line, buf[fd]);
		if (!ret)
			return (free(line), free(buf[fd]), -1);
	}
	if (ret == -1)
		return (-1);
	(*line)[ret] = '\0';
	return (1);
}

int	get_next_line(int fd, char **line)
{
	if (fd < 0 || fd > FD_MAX || !line || BUFFER_SIZE < 1)
		return (free(line), -1);
	return (gnl(fd, line));
}
