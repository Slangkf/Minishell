/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:09:28 by seruff            #+#    #+#             */
/*   Updated: 2024/11/13 09:15:51 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t count)
{
	unsigned char	*d;
	size_t			i;

	i = 0;
	d = (unsigned char *)s;
	while (i < count)
	{
		if (d[i] == ((unsigned char)c))
			return ((void *)s + i);
		i++;
	}
	return (0);
}

/*
int	main()
{
	char s[] = {0,1,2,3,4,5};
	unsigned char *p = ft_memchr(s, 2 + 256, 3);
	unsigned char *p1 = memchr(s,2+256,3);
	printf("ft : %p\n", p);
	printf("mem: %p", p1);
	return (0);
}
*/
