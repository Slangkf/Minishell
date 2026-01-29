/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:05:19 by seruff            #+#    #+#             */
/*   Updated: 2025/05/23 15:25:30 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char				*dst;
	unsigned int		i;
	unsigned int		len;
	unsigned int		j;

	j = 0;
	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	dst = malloc(sizeof(char ) * (len + 1));
	if (dst == NULL)
		return (0);
	while (s1[i] && s1)
	{
		dst[i] = s1[i];
		i++;
	}
	while (s2[j] && s2)
	{
		dst[i] = s2[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
/*
int	main(void)
{
	char const *s1 = "Hello m";
	char const *s2 = "y boy com'on";
	printf("dst : %s", ft_strjoin(s1, s2));
	return (0);
}
*/
