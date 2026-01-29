/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:08:38 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 11:24:43 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* 
 * Add a new element inside a char **arg at the position desired
 * and not only at the end as usually
 */
static int	insert_modif(char ***arg, int *len, int pos, char **split)
{
	int	j;
	int	count;

	count = ft_array_len(split);
	*arg = ft_realloc_array(*arg, *len + count);
	if (!*arg)
		return (137);
	j = *len - 1;
	while (j > pos)
	{
		(*arg)[j + count - 1] = (*arg)[j];
		j--;
	}
	j = 0;
	while (j < count)
	{
		(*arg)[pos + j] = ft_strdup(split[j]);
		if (!(*arg)[pos + j])
			return (137);
		j++;
	}
	*len += count - 1;
	(*arg)[*len] = NULL;
	return (0);
}

/*
 * Split a token into as necessary part depending on the number of space into it
 * if it was expanded before and creating multiple tokens if necessary
 * Then adding them into the array
 * Example : tok:["today", "is sunny", "day"] -> ["today", "is", "sunny", "day"]
 */
static int	handle_split(char ***array, char **split, int *i, int *len)
{
	if (ft_array_len(split) > 1)
	{
		free((*array)[*i]);
		*len = ft_array_len(*array);
		if (insert_modif(array, len, *i, split) != 0)
			return (137);
		*i += ft_array_len(split);
	}
	else
		(*i)++;
	return (0);
}

static void	remove_arg(char ***array, int i)
{
	int	len;
	int	j;

	len = ft_array_len(*array);
	free((*array[i]));
	j = 0;
	while (j < len - 1)
	{
		(*array)[j] = (*array)[j + 1];
		j++;
	}
	(*array)[j] = NULL;
}

int	split_args(t_command *cmd)
{
	int		i;
	int		len;
	int		ret;
	char	**split;

	i = 0;
	if (ft_strlen(cmd->args[i]) == 0 || !empty_string(cmd->args[i]))
		remove_arg(&cmd->args, 0);
	while (cmd->args && cmd->args[i])
	{
		if (ft_strlen(cmd->args[i]) == 0 || !empty_string(cmd->args[i]))
		{
			i++;
			continue ;
		}
		split = split_custom(cmd->args[i]);
		if (!split)
			return (137);
		ret = handle_split(&cmd->args, split, &i, &len);
		ft_free_array(split);
		if (ret != 0)
			return (ret);
	}
	return (0);
}
