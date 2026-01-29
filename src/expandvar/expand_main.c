/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:57:59 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 11:20:57 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * Expand Environnement Variable of those infiles and outfile present
 */
static	int	expand_files(t_shell *shell, t_command *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->nb_files)
	{
		if (cmd->files[i].file && ft_count_carac(cmd->files[i].file, '$'))
		{
			cmd->files[i].file = expand(shell, cmd->files[i].file);
			if (!cmd->files[i].file)
				return (137);
		}
		i++;
	}
	return (0);
}

/*
 * Launch the expansion every time there is a '$' 
 * dollar caractere present into a token
 */
static	int	main_expand_bis(t_shell *shell, t_command *cmd)
{
	int	i;

	i = -1;
	while (cmd->args && cmd->args[++i])
	{
		if (ft_count_carac(cmd->args[i], '$') != 0)
		{
			cmd->args[i] = expand(shell, cmd->args[i]);
			if (!cmd->args[i])
				return (137);
		}
	}
	if (cmd->files && expand_files(shell, cmd) != 0)
		return (137);
	return (0);
}

/*
 * Verification of the return value of expand part
 * Verification of the split_args -> word_splitting
 * 	-> Splitting a token after an expansion if this one contains an IFE
 * Verification of filter() -> cleaning extra quotes or quotes around a bloc
 */
int	main_expand(t_shell *shell)
{
	t_command	*curr;

	curr = shell->cmds;
	while (curr)
	{
		if (main_expand_bis(shell, curr) == 137)
			return (137);
		if (split_args(curr) == 1)
			return (137);
		if (filter_main(curr) != 0)
			return (137);
		curr = curr->next;
	}
	return (0);
}
