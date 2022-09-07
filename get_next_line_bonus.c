/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:52:15 by eujeong           #+#    #+#             */
/*   Updated: 2022/08/23 13:59:13 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < start)
		len = 0;
	else if (s_len - start < len)
		len = s_len - start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_len;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_len = s1_len + s2_len;
	str = (char *)malloc(sizeof(char) * (total_len + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, s1_len + 1);
	ft_strlcpy(str + s1_len, s2, s2_len + 1);
	return (str);
}

static char	*ft_read_line(int fd, char *buff, char *backup)
{
	char	*temp;
	int		read_cnt;

	while (backup == NULL || ft_strchr(backup, '\n') == NULL)
	{
		read_cnt = read(fd, buff, BUFFER_SIZE);
		if (read_cnt == -1)
		{
			free(backup);
			return (NULL);
		}
		if (read_cnt == 0)
			break ;
		buff[read_cnt] = '\0';
		if (backup == NULL)
			backup = ft_strdup("");
		temp = backup;
		backup = ft_strjoin(backup, buff);
		free(temp);
		if (backup == NULL)
			return (NULL);
	}
	return (backup);
}

static char	*ft_get_line(char **backup)
{
	char	*temp;
	char	*line;
	size_t	line_len;

	line_len = 0;
	while ((*backup)[line_len] != '\n' && (*backup)[line_len] != '\0')
		line_len++;
	if ((*backup)[line_len] == '\n')
		line_len++;
	if (line_len == 0)
		return (NULL);
	line = ft_substr(*backup, 0, line_len);
	if (line == NULL)
		return (NULL);
	temp = *backup;
	*backup = ft_substr(*backup, line_len, ft_strlen(*backup) - line_len);
	free(temp);
	if (*backup == NULL)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*line;
	static char	*backup[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buff == NULL)
		return (NULL);
	backup[fd] = ft_read_line(fd, buff, backup[fd]);
	free(buff);
	if (backup[fd] == NULL)
		return (NULL);
	line = ft_get_line(&backup[fd]);
	if (backup[fd] != NULL && ft_strlen(backup[fd]) == 0)
	{
		free(backup[fd]);
		backup[fd] = NULL;
	}
	return (line);
}
