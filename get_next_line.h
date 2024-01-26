/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 16:37:07 by pkorsako          #+#    #+#             */
/*   Updated: 2022/06/18 17:18:54 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);
int		ft_strchr(char *str, int c);
char	*get_next_line(int fd);
char	*ft_strdup(char *s);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	*free_str(char *str);
void	free_dup(char **f, char **dup);
char	*do_a_flip(char *string, int i, int fd);
char	*make_stash(int j, char *string);

#endif