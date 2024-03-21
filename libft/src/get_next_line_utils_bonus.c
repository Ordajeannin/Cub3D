/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 16:36:57 by pkorsako          #+#    #+#             */
/*   Updated: 2024/03/21 19:34:33 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"
#include "libft.h"

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
