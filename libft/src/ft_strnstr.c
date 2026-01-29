/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:37:11 by seruff            #+#    #+#             */
/*   Updated: 2024/11/15 08:57:52 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <string.h>

char	*ft_strnstr(const char *S, const char *s, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (len >= ft_strlen(S))
		len = ft_strlen(S);
	if (s[0] == '\0')
		return ((char *)S);
	while (i < len && S[i] != '\0')
	{
		if (S[i] == s[0])
		{
			while (i + j < len && S[i + j] == s[j])
			{
				if (s[j + 1] == '\0')
					return ((char *)S + i);
				j++;
			}
		}
		j = 0;
		i++;
	}
	return (NULL);
}
/*
int main()
{
	char *h = "aaabcabcd";
	char *n = "aabc";
//	char * vide = (char *)"";
	printf("FT: %s \n", ft_strnstr(h, n, 1));
	return 0;
}
*/
