/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:32:26 by seruff            #+#    #+#             */
/*   Updated: 2025/06/23 12:07:37 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *str, int new_size)
{
	int		i;
	char	*new_str;

	i = 0;
	if (new_size == 0)
		return (free(str), NULL);
	new_str = malloc((new_size + 1) * sizeof(char ));
	if (!new_str)
		return (NULL);
	if (str)
	{
		i = ft_strlen(str);
		if (i > new_size - 1)
			i = new_size - 1;
		ft_memcpy(new_str, str, i);
		new_str[i] = '\0';
		free(str);
	}
	else
		new_str[0] = '\0';
	return (new_str);
}

void	*ft_realoc(void *ptr, size_t old_s, size_t new_s)
{
	void	*new;
	size_t	copy;

	if (new_s == 0)
		return (free(ptr), NULL);
	new = malloc(new_s);
	if (!new)
		return (NULL);
	if (ptr)
	{
		if (old_s < new_s)
			copy = old_s;
		else
			copy = new_s;
		ft_memcpy(new, ptr, copy);
		free(ptr);
	}
	return (new);
}

char	**ft_realloc_array(char **str, int new_size)
{
	int		i;
	char	**new_str;

	i = 0;
	if (new_size <= 0)
		return (NULL);
	new_str = malloc((new_size) * sizeof(char *));
	if (!new_str)
		return (NULL);
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	while (i < new_size)
	{
		new_str[i] = NULL;
		i++;
	}
	return (free(str), new_str);
}
