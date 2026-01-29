/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:43:12 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 11:21:36 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	int	filter_bloc(t_command *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		tmp = clean_quotes(cmd->args[i]);
		if (!tmp)
			return (137);
		free(cmd->args[i]);
		cmd->args[i] = tmp;
		i++;
	}
	return (0);
}

static int	filter_files(t_command *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < cmd->nb_files)
	{
		if (cmd->files[i].file)
		{
			tmp = clean_quotes(cmd->files[i].file);
			if (!tmp)
				return (137);
			free(cmd->files[i].file);
			cmd->files[i].file = tmp;
		}
		i++;
	}
	return (0);
}

char	*filter_string(char *s)
{
	char	*tmp;

	tmp = clean_quotes(s);
	if (!tmp)
		return (NULL);
	free(s);
	s = tmp;
	return (s);
}

/*
 * Removes quotes outside or around a string 
 */
int	filter_main(t_command *cmd)
{
	if (cmd->args && filter_bloc(cmd) != 0)
		return (137);
	if (cmd->files && filter_files(cmd) != 0)
		return (137);
	return (0);
}
