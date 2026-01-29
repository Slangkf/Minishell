/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:51:52 by seruff            #+#    #+#             */
/*   Updated: 2025/05/23 14:22:34 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <string.h>

static int	ft_count_n(long int num)
{
	int	count;

	count = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		count++;
	while (num != 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long int	num;
	int			len;
	char		*result;

	num = n;
	len = ft_count_n(num);
	result = malloc (sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (num == 0)
		result[0] = '0';
	if (num < 0)
	{
		result[0] = '-';
		num *= -1;
	}
	while (len-- && num != 0)
	{
		result[len] = num % 10 + '0';
		num /= 10;
	}
	return (result);
}
/*
int	main(void)
{
	char	*d;

	d = ft_itoa(-10004);
	printf("%s \t strcmp: %d\n", d, strcmp(d, "-10004"));
	free(d);
	return (0);
}
*/
