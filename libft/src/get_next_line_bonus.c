/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 16:36:37 by pkorsako          #+#    #+#             */
/*   Updated: 2024/03/01 15:40:33 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"
#include "libft.h"

// int	gft_strchr(char *str, int c)
// {
// 	int	i;

// 	i = 0;
// 	if (str)
// 	{
// 		while (str[i] != 0)
// 		{
// 			if (str[i] == c)
// 				return (i);
// 			i++;
// 		}
// 	}
// 	return (-1);
// }

// int	gft_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		i ++;
// 	return (i);
// }

// size_t	gft_strlcpy(char *dst, char *src, size_t dstsize)
// {
// 	size_t	i;

// 	i = 0;
// 	if (dstsize < 1)
// 		return (gft_strlen(src));
// 	while (i < dstsize - 1 && src[i] != '\0')
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	dst[i] = '\0';
// 	return (gft_strlen(src));
// }

// char	*gft_strdup(char *s)
// {
// 	size_t	i;
// 	char	*cpy;

// 	i = 0;
// 	if (!s)
// 		return (0);
// 	cpy = malloc(ft_strlen(s) + 1);
// 	if (!cpy)
// 		return (0);
// 	while (s[i])
// 	{
// 		cpy[i] = s[i];
// 		i++;
// 	}
// 	cpy[i] = s[i];
// 	return (cpy);
// }

// char	*gft_strjoin(char *s1, char *s2)
// {
// 	size_t	size;
// 	char	*s;

// 	if (!s1 && !s2[0])
// 		return (0);
// 	else if (!s1)
// 		return (gft_strdup(s2));
// 	else if (!s2[0])
// 		return (gft_strdup(s1));
// 	size = gft_strlen(s1) + gft_strlen(s2) + 1;
// 	s = malloc(size);
// 	if (!s)
// 		return (0);
// 	gft_strlcpy(s, s1, size);
// 	gft_strlcpy(s + gft_strlen(s1), s2, size);
// 	return (s);
// }
