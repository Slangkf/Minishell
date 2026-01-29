/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:38:00 by seruff            #+#    #+#             */
/*   Updated: 2024/11/07 15:17:12 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*d;

	i = 0;
	d = malloc(sizeof * d * (ft_strlen((char *)s) + 1));
	if (d == NULL)
		return (NULL);
	while (s[i])
	{
		d[i] = ((char *)s)[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}
