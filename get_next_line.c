/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:30:09 by mfagri            #+#    #+#             */
/*   Updated: 2021/11/21 17:26:13 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	len;
	size_t	j;

	if (s1 == NULL)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	len = ft_strlen(s1)+ ft_strlen(s2);
	str = (char *)malloc(len + 1 * sizeof(char));
	if (str == NULL)
		return (NULL);
	len = -1;
	while (s1[++len])
		str[len] = s1[len];
	j = 0;
	while (s2[j])
	{
		str[len++] = s2[j++];
	}
	str[len] = '\0';
	free(s1);
	return (str);
}

char	*ft_read(char *s, int fd)
{
	char	*buf;
	int		n;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	n = 1;
	while (ft_strchr(s, '\n') == NULL && n != 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[n] = '\0';
		s = ft_strjoin(s, buf);
	}
	free(buf);
	return (s);
}

char	*change_the_static(char *s)
{
	char	*news;
	size_t	i;
	size_t	l;

	l = 0;
	while (s[l] != '\n' && s[l] != '\0')
		l++;
	if (ft_strlen(s) == l)
	{
		free(s);
		return (NULL);
	}
	news = (char *)malloc((ft_strlen(s) - l + 1) * sizeof(char));
	if (news == NULL)
		return (NULL);
	i = 0;
	while (s[l++])
	{
		news[i] = s[l];
		i++;
	}
	news[i] = '\0';
	free(s);
	return (news);
}

char	*line(char *res)
{
	char	*line;
	size_t	l;
	size_t	i;

	l = 0;
	if (res[0] == '\0')
		return (NULL);
	while (res[l] != '\n' && res[l] != '\0')
		l++;
	if (res[l] == '\n')
		l++;
	line = (char *)malloc(sizeof(char) * l + 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i < l)
	{
		line[i] = res[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*s;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	s = ft_read(s, fd);
	if (s == NULL)
		return (NULL);
	buf = line(s);
	s = change_the_static(s);
	return (buf);
}
