/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:34:18 by seruff            #+#    #+#             */
/*   Updated: 2025/04/09 11:47:44 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != (unsigned char) c)
	{
		if (*s == 0)
			return (0);
		s++;
	}
	return ((char *)s);
}

/*
int	main()
{
	char s[] = "jeanclaudeduce";
	printf("%s", ft_strchr(s, 'c'));
	return (0);
}
*/
