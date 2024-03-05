/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 16:36:57 by pkorsako          #+#    #+#             */
/*   Updated: 2024/03/01 15:41:49 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"
#include "libft.h"

int	gft_strchr(char *str, int c)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] != 0)
		{
			if (str[i] == c)
				return (i);
			i++;
		}
	}
	return (-1);
}

int	gft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i ++;
	return (i);
}

size_t	gft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize < 1)
		return (gft_strlen(src));
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (gft_strlen(src));
}

char	*gft_strdup(char *s)
{
	size_t	i;
	char	*cpy;

	i = 0;
	if (!s)
		return (0);
	cpy = malloc(ft_strlen(s) + 1);
	if (!cpy)
		return (0);
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = s[i];
	return (cpy);
}

char	*gft_strjoin(char *s1, char *s2)
{
	size_t	size;
	char	*s;

	if (!s1 && !s2[0])
		return (0);
	else if (!s1)
		return (gft_strdup(s2));
	else if (!s2[0])
		return (gft_strdup(s1));
	size = gft_strlen(s1) + gft_strlen(s2) + 1;
	s = malloc(size);
	if (!s)
		return (0);
	gft_strlcpy(s, s1, size);
	gft_strlcpy(s + gft_strlen(s1), s2, size);
	return (s);
}

char	*free_str(char *str)
{
	if (str)
		free(str);
	return (0);
}

void	free_dup(char **f, char **dup)
{
	*dup = free_str(*dup);
	if (*f)
	{
		*dup = gft_strdup(*f);
		*f = free_str(*f);
	}
}

char	*do_a_flip(char *string, int i, int fd)
{
	char	buff[BUFFER_SIZE + 1];
	char	*tmp;
	int		j;

	tmp = NULL;
	j = gft_strchr(string, '\n');
	while (i == BUFFER_SIZE && j == -1)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i < -1)
			return (0);
		buff[i] = 0;
		tmp = gft_strjoin(string, buff);
		string = free_str(string);
		string = gft_strdup(tmp);
		j = gft_strchr(string, '\n');
		tmp = free_str(tmp);
		if (i < BUFFER_SIZE && j == -1)
			return (string);
	}
	return (string);
}

char	*make_stash(int j, char *string)
{
	char	*stash;

	stash = NULL;
	if (j == -1 || string[j + 1] == 0)
		return (0);
	stash = gft_strdup(&string[j + 1]);
	string[j + 1] = 0;
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*string;
	char		*tmp;
	char		buff[BUFFER_SIZE + 1];
	int			i;

	string = NULL;
	tmp = NULL;
	free_dup(&stash, &string);
	i = read(fd, buff, BUFFER_SIZE);
	if (i < 0)
		return (0);
	buff[i] = '\0';
	if (!i && gft_strchr(string, '\n') == -1)
		return (string);
	tmp = gft_strjoin(string, buff);
	free_dup(&tmp, &string);
	if (i < BUFFER_SIZE && gft_strchr(string, '\n') == -1)
		return (string);
	string = do_a_flip(string, i, fd);
	stash = make_stash(gft_strchr(string, '\n'), string);
	return (string);
}
