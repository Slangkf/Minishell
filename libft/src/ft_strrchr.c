/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:41:50 by seruff            #+#    #+#             */
/*   Updated: 2024/11/27 14:14:39 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	if ((unsigned char)c == '\0')
		return ((char *)s + i);
	while (i--)
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
	if (s[i] == (unsigned char)c)
		return ((char *)s + i);
	return (0);
}
/*
int	main(void)
{
	printf("mine: %s\n", ft_strrchr("jeanclaudeduce", 99));
	return (0);
}
*/
