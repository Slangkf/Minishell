/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:41:06 by seruff            #+#    #+#             */
/*   Updated: 2025/05/13 15:20:34 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_array(char **dest)
{
	int	i;

	i = 0;
	if (!dest)
		return ;
	if (!dest[0])
		return ;
	while (dest[i])
	{
		if (dest[i])
			free(dest[i]);
		i++;
	}
	if (dest)
		free(dest);
}
