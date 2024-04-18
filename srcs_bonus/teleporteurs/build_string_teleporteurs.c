/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_string_teleporteurs.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:17:17 by ajeannin          #+#    #+#             */
/*   Updated: 2024/04/18 21:01:25 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	add_used(char *used, char c)
{
	int	i;

	i = 0;
	while (used[i] && used[i] != c)
		i++;
	if (used[i] != c)
	{
		used[i] = c;
		return ('\0');
	}
	else
		return (c);
}

int	help_build_telep_str(char *str, char *result, char *used, int *flag)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != '\n')
	{
		if (str[i] == '[' && *flag == 0)
		{
			result[i] = str[i];
			*flag = 1;
		}
		else if (flag != 0 && *flag < 3
			&& !add_used(used, str[i]) && ft_isalnum(str[i]))
		{
			result[i] = str[i];
			*flag += 1;
		}
		else if (str[i] == ']' && *flag == 3)
		{
			result[i] = str[i];
			*flag = 0;
		}
		else
			return (0);
	}
	return (1);
}

char	*build_telep_str(char *str)
{
	char	*result;
	char	*used;
	int		flag;

	if (!str)
		return (NULL);
	result = calloc(sizeof(char), ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	used = calloc(sizeof(char), ft_strlen(str) + 1);
	if (!used)
	{
		free(result);
		return (NULL);
	}
	flag = 0;
	if (!help_build_telep_str(str, result, used, &flag))
	{
		printf("bad syntax for teleporteurs, cf ReadMe\n");
		free(used);
		free(result);
		return (NULL);
	}
	free(used);
	return (result);
}
