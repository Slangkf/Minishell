/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:56:42 by seruff            #+#    #+#             */
/*   Updated: 2025/04/08 14:57:58 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr_array(char **array, char *s)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (!ft_strncmp(array[i], s, ft_strlen(s)))
			return (1);
		i++;
	}
	return (0);
}
