/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:48:18 by seruff            #+#    #+#             */
/*   Updated: 2024/11/15 15:08:20 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;
	size_t	i;	

	i = 0;
	d = (char *)dest;
	s = (char *)src;
	if (dest == NULL && s == NULL)
		return (0);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
/*
int main() 
{
	printf("test: %p\n", ft_memcpy(((void *)0),((void *)0) , 3));
//	printf("Origine : %p", memcpy(((void *)0),((void *)0), 3));
	return 0; 
}
*/
