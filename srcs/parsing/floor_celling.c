/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_celling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:34:52 by pkorsako          #+#    #+#             */
/*   Updated: 2024/03/20 15:07:08 by pkorsako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*strcp_to_n(const char *str, char n)
{
	int		i;
	char	*cp;

	i = 0;
	cp = malloc(sizeof(char) * 4);
	if (!str || !cp)
		return (NULL);
	ft_bzero(cp, 4);
	while (str[i] && str[i] != n)
	{
		if (i == 4)
			return (NULL);
		cp[i] = str[i];
		i ++;
	}
	cp[3] = 0;
	return (cp);
}

int	rgb_atoi_help(char *str)
{
	printf("non str or alpha in color\n");
	free(str);
	return (-1);
}

int	rgb_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 0;
	result = 0;
	if (!str)
		return (-1);
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	else
		sign = 1;
	if (sign == -1 || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		result = (result * 10) + (str[i++] - '0');
	if ((str[i] != 0 && str[i] != '\n') || str[0] == '\n')
		return (rgb_atoi_help(str));
	free(str);
	return (result * sign);
}

void	init_atorgb(int *color, int *tmp, int *i)
{
	*color = 0;
	*tmp = 0;
	*i = 0;
}

int	atorgb(char *str)
{
	int		color;
	int		tmp;
	int		i;
	char	*saved;

	init_atorgb(&color, &tmp, &i);
	saved = str;
	while (i < 3)
	{
		tmp = rgb_atoi(strcp_to_n(str, ','));
		str = ft_strchr(str, ',');
		if (str && str[0] == ',')
			str ++;
		if (tmp < 0)
		{
			free(saved);
			return (-1);
		}
		color += tmp;
		i ++;
		if (i < 3)
			color = color << 8;
	}
	free(saved);
	return (color);
}
