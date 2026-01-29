/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:34:04 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 11:32:21 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * Free tab of string
 */
void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
	{
		write(2, "RIEN A FREE\n", 12);
		return ;
	}
	if (!args[0])
	{
		free(args);
		return ;
	}
	if (args[i])
	{
		while (args[i])
			free(args[i++]);
		free(args);
	}
}

/* 
 * Free chained list of files
 */
static void	ft_free_files(t_command *curr)
{
	int	i;

	i = 0;
	while (i < curr->nb_files)
	{
		if (curr->files[i].file)
			free(curr->files[i].file);
		if (curr->files[i].delimiter)
			free(curr->files[i].delimiter);
		i++;
	}
	free(curr->files);
}

/*
 * Free chained list of cmd
 */
void	free_cmd_list(t_command *cmd)
{
	t_command	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
			free_args(cmd->args);
		if (cmd->nb_files != 0)
			ft_free_files(cmd);
		free(cmd);
		cmd = tmp;
	}
}

/*
 * Free Token structure of types/tokens
 */
void	ft_free_tokens(t_token *token_struct)
{
	if (token_struct)
	{
		if (token_struct->token && token_struct->token[0])
			ft_free_array(token_struct->token);
		if (token_struct->types || token_struct->types[0])
			ft_free_array(token_struct->types);
		free(token_struct);
	}
}

/*
 * Free every memory allocation of the whole program
 */
void	ft_free_program(t_shell *shell)
{
	if (shell->environ)
		free_args(shell->environ);
	if (shell->cmds)
		free_cmd_list(shell->cmds);
	if (shell->tok)
		ft_free_tokens(shell->tok);
	ft_clean_fd();
}
