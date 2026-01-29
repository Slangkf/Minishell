/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:10:57 by seruff            #+#    #+#             */
/*   Updated: 2024/11/15 11:49:59 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			i;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (i < n)
	{
		if (p1[i] > p2[i])
			return (n);
		if (p1[i] < p2[i])
			return (-1);
		i++;
	}
	return (0);
}
/*
int	main()
{
	char s[] = {-128, 0, 127, 0};
	char d[] = {-128, 0, 127, 0};
	printf("%d\n", (ft_memcmp(s,d,4)));
	printf("%d", memcmp(s,d,3));
	return (0);
}
*/
