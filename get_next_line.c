/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 10:26:05 by vkurkela          #+#    #+#             */
/*   Updated: 2020/02/14 00:01:02 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** This function checks if it finds linebreak and stores
** the line ending '\n' to *line variable and sets *s
** variable to position where that line ends. 
** If there is no linebreak it copies the end and
** frees the *s variable.
*/

static int	get_line(char **s, char **line)
{
	int		len;
	char	*temp;

	len = 0;
	while ((*s)[len] != '\n' && (*s)[len] != '\0')
		len++;
	if ((*s)[len] == '\n')
	{
		if ((!(*line = ft_strsub(*s, 0, len))) ||\
		!(temp = ft_strdup(&((*s)[len + 1]))))
			return (-1);
		ft_strdel(s);
		*s = temp;
		if ((*s)[0] == '\0')
			ft_strdel(s);
	}
	else
	{
		if (!(*line = ft_strdup(*s)))
			return (-1);
		ft_strdel(s);
	}
	return (1);
}

/*
** Returns a value 1 if line has been read,
** 0 when the reading has been completed or
** -1 if an error has happened respectively.
*/

static int	ret_value(char **s, char **line, int ret, int fd)
{
	if (ret < 0)
		return (-1);
	else if (ret == 0 && s[fd] == NULL)
		return (0);
	else
		return (get_line(&s[fd], line));
}

/*
** This function checks if static variable is empty and then allocates
** memory for it using buff and see if it contains line break
** character. Next iterations will store the data from fd and
** stores it after the previous data. If line break occurs then
** function breaks and returns 1.
*/

static int	check_linebreak(char *buff, char **s, int *ret, int fd)
{
	char		*temp;

	buff[*ret] = '\0';
	if (s[fd] == NULL)
	{
		if (!(s[fd] = ft_strdup(buff)))
			return (-1);
	}
	else
	{
		if (!(temp = ft_strjoin(s[fd], buff)))
			return (-1);
		free(s[fd]);
		s[fd] = temp;
	}
	if (ft_strchr(s[fd], '\n'))
		return (0);
	return (1);
}

/*
** GNL checks first errors and continue to read the file descriptor
** untill it finds a new line or an error occurs.
*/

int			get_next_line(const int fd, char **line)
{
	int			ret;
	char		buff[BUFF_SIZE + 1];
	static char	*s[FD_MAX];
	int			value;

	if (fd < 0 || line == NULL)
		return (-1);
	*line = NULL;
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		value = check_linebreak(buff, s, &ret, fd);
		if (value == -1)
			return (-1);
		else if (value == 0)
			break ;
	}
	return (ret_value(s, line, ret, fd));
}
