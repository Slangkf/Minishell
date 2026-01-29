/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:28:37 by seruff            #+#    #+#             */
/*   Updated: 2024/11/15 15:46:24 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	j = 0;
	i = ft_strlen(dest);
	k = ft_strlen(src);
	if (size <= i)
		return (size + k);
	while (src[j] != '\0' && i + j < size - 1)
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i <= size)
		dest[i + j] = '\0';
	return (i + k);
}
/*
int main (void)
{
	char *s = "douceur";
	char * d = "testeur";
	printf("%zu et d : %s\n",ft_strlcat(d, s, 5), d);
	return (0);
}
*/
