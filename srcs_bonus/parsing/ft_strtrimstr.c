/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeannin <ajeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:46:29 by ajeannin          #+#    #+#             */
/*   Updated: 2024/04/22 21:10:45 by ajeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	looking_for_cut(char *str, char *cut)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		if (str[i] == cut[j])
		{
			while (str[i] && cut[j] && str[i] == cut[j])
			{
				i++;
				j++;
			}
			if (!str[i] && !cut[j])
				return (i - j);
			else
				break ;
		}
		else
			i++;
	}
	return (0);
}

char	*ft_strtrimstr(char *str, char *cut)
{
	int		i;
	int		j;
	char	*result;

	if (!str || !cut)
		return (NULL);
	i = ft_strlen(str);
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = looking_for_cut(str, cut);
	if (j == 0)
		return (str);
	while (i < j)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
