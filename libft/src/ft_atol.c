/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:48:42 by seruff            #+#    #+#             */
/*   Updated: 2025/07/03 15:52:26 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	clean_entry(char *s, int *i, long *sign)
{
	while (ft_isspace(s[*i]))
		(*i)++;
	if (ft_signe(s[*i]))
	{
		if (s[*i] == '-')
			*sign *= -1;
		i++;
	}
}

long	ft_atol(char *string)
{
	int			i;
	long		sign;
	long		result;

	sign = 1;
	result = 0;
	i = 0;
	while (ft_isspace(string[i]) == 0)
		i++;
	if (ft_signe(string[i]))
	{
		if (string[i] == '-')
			sign *= -1;
		i++;
	}
	while (string[i] >= '0' && string[i] <= '9')
	{
		result = result * 10 + (string[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_atoll(char *s)
{
	int			i;
	long		sign;
	long		result;

	sign = 1;
	result = 0;
	i = 0;
	clean_entry(s, &i, &sign);
	if (sign == -1)
		return (-1);
	if (ft_strlen(s) == 1 && s[0] == '0')
		return (0);
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i] - '0');
		if (result >= 256)
			return (-1);
		i++;
	}
	return (result);
}
