/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:02:17 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 10:47:33 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* 
 * EXEC HARD BUILTIN WITHOUT PIPE
 * Execute only the builtin if there is no pipe in the command line
 */
void	ft_hard_builtin(t_shell *shell, char **args)
{
	if (!ft_strcmp(args[0], "cd"))
		cd_cmd(shell, args);
	else if (!ft_strcmp(args[0], "export"))
		export_cmd(shell, args);
	else if (!ft_strcmp(args[0], "unset"))
		unset_cmd(shell, args);
	else if (!ft_strcmp(args[0], "exit"))
		exit_cmd(shell, args);
}

/* 
 * EXEC HARD BUILTIN IN PIPE
 * Special exit in the command line with a pipe
 * Shouldn't write 'exit' or quit the program
 * Shouldn't do anything
 * Only write error if there is one in the input of the command
 */
static void	exit_in_pipe(t_shell *shell, char **args)
{
	if (!args[1])
		shell->error = shell->error;
	else if (is_numeric(shell, args[1]) == 1)
		print_exit(1, args[1]);
	else if (args[2])
	{
		print_exit(2, NULL);
		shell->error = 1;
		return ;
	}
	else if (is_numeric(shell, args[1]) == 2)
		shell->error = -2;
	else
		shell->error = ft_atoll(args[1]);
}

/*
 * Export in pipe isn't doing anything
 */
static void	export_in_pipe(t_shell *shell, char **args)
{
	if (!args[1] || !empty_string(args[1]))
		ft_export_env(shell->environ);
}

/*
 * Builtins who need to be executed in a pipe without doing anything
 * Cause they are modifying the environnement
 * Only print error in the args of those commands
 */
void	ft_hard_builtin_in_pipe(t_command *current, t_shell *shell)
{
	if (!ft_strcmp(current->args[0], "cd"))
		ft_cd_in_pipe(current->args, shell);
	else if (!ft_strcmp(current->args[0], "export"))
	{
		if (!current->next)
			export_in_pipe(shell, current->args);
	}
	else if (!ft_strcmp(current->args[0], "exit"))
		exit_in_pipe(shell, current->args);
	else
		return ;
}

/* 
 * EXEC SOFT BUILTIN
 * Builtins who actually does something into a pipe and without a pipe
 */
void	ft_soft_builtin(char **args, t_shell *shell)
{
	if (!ft_strcmp(args[0], "echo"))
		echo_cmd(args);
	else if (!ft_strcmp(args[0], "pwd"))
		pwd_cmd(shell);
	else if (!ft_strcmp(args[0], "env"))
		env_cmd(shell->environ);
	ft_clean_fd();
}
