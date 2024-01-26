/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulk <paulk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 16:36:57 by pkorsako          #+#    #+#             */
/*   Updated: 2024/01/21 13:18:13 by paulk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		*dup = ft_strdup(*f);
		*f = free_str(*f);
	}
}

char	*do_a_flip(char *string, int i, int fd)
{
	char	buff[4096 + 1];
	char	*tmp;
	int		j;

	tmp = NULL;
	j = ft_strchr(string, '\n');
	while (i == 4096 && j == -1)
	{
		i = read(fd, buff, 4096);
		if (i < -1)
			return (0);
		buff[i] = 0;
		tmp = ft_strjoin(string, buff);
		string = free_str(string);
		string = ft_strdup(tmp);
		j = ft_strchr(string, '\n');
		tmp = free_str(tmp);
		if (i < 4096 && j == -1)
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
	stash = ft_strdup(&string[j + 1]);
	string[j + 1] = 0;
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*string;
	char		*tmp;
	char		buff[4096 + 1];
	int			i;

	string = NULL;
	tmp = NULL;
	free_dup(&stash, &string);
	i = read(fd, buff, 4096);
	if (i < 0)
		return (0);
	buff[i] = '\0';
	if (!i && ft_strchr(string, '\n') == -1)
		return (string);
	tmp = ft_strjoin(string, buff);
	free_dup(&tmp, &string);
	if (i < 4096 && ft_strchr(string, '\n') == -1)
		return (string);
	string = do_a_flip(string, i, fd);
	stash = make_stash(ft_strchr(string, '\n'), string);
	return (string);
}
