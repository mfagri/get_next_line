/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:29:33 by mfagri            #+#    #+#             */
/*   Updated: 2021/11/22 18:51:48 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*ft_change(char *res)
{
	size_t	i;
	size_t	j;
	char	*dest;

	i = 0;
	while (res[i] != '\n' && res[i] != '\0')
		i++;
	if (ft_strlen(res) == i)
	{
		free(res);
		return (NULL);
	}
	dest = (char *)malloc((ft_strlen(res) - i + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	j = 0;
	while (res[i++] != '\0')
		dest[j++] = res[i];
	dest[j] = '\0';
	free(res);
	return (dest);
}

char	*ft_line(char *res)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	if (res[0] == '\0')
		return (NULL);
	while (res[i] != '\n' && res[i] != '\0')
		i++;
	if (res[i] == '\n')
		i++;
	line = (char *)malloc((i + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = res[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*dest;

	if (s1 == NULL)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	i = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)malloc(i + 1 * sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	free(s1);
	return (dest);
}

char	*read_file(char *res, int fd)
{
	char	*buf;
	int		n;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	n = 1;
	while (ft_strchr(res, '\n') == NULL && n != 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[n] = '\0';
		res = ft_strjoin(res, buf);
	}
	free(buf);
	return (res);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*res[10240];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	res[fd] = read_file(res[fd], fd);
	if (res[fd] == NULL)
		return (NULL);
	line = ft_line(res[fd]);
	res[fd] = ft_change(res[fd]);
	return (line);
}
