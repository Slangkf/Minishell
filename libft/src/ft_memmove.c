/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:57:44 by seruff            #+#    #+#             */
/*   Updated: 2024/11/14 13:59:09 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <string.h>
#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;

	i = n;
	if (dest == src)
		return (dest);
	if (dest < src || (char *)dest >= (char *)src + n)
		ft_memcpy(dest, src, n);
	else
	{
		while (i > 0)
		{
			((char *)dest)[i - 1] = ((const char *)src)[i - 1];
			i--;
		}
	}
	return (dest);
}
/*
int	main()
{
	char src[] = "Oi mate what's going on?";
	char dest[30];

	ft_memmove(dest, src, 9);
	printf("sans : %s\n", dest);
	memcpy(dest + 5, src + 7, 6);
	printf("avec: %s\n", dest);
	return (0);
}
*/
