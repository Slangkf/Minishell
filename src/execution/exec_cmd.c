/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclouet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:52:10 by tclouet           #+#    #+#             */
/*   Updated: 2025/07/01 14:33:46 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * Handles execution when PATH is not set or command contains '/'
 * Executes soft builtins or direct paths, returns 1 on success, 0 otherwise
 */
static int	manage_no_path(char **arg, t_shell *shell)
{
	if (ft_is_builtin(arg[0]) == 2)
		return (ft_soft_builtin(arg, shell), 1);
	else if (ft_strchr(arg[0], '/'))
	{
		if (execve(arg[0], arg, shell->environ) == -1)
		{
			if (check_file(arg[0], shell) != 0)
				return (1);
			else
			{
				ft_cmd_not_found(arg[0]);
				return (1);
			}
		}
	}
	return (0);
}

/*
 * Searches for the command in all PATH directories
 * Returns the full path if found, NULL otherwise
 */
static char	*check_all_paths(char *arg, char **paths)
{
	int		i;
	char	*temp;
	char	*complete_path;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		complete_path = ft_strjoin(temp, arg);
		if (!complete_path)
			return (free(temp), NULL);
		free(temp);
		if (access(complete_path, F_OK) == 0)
			return (complete_path);
		free(complete_path);
		i++;
	}
	return (NULL);
}

/*
 * Finds the complete path of a command by searching in PATH environment variable
 * Returns the path if found, sets path_flag to 1 if PATH not found
 */
static char	*find_good_path(char *arg, t_shell *shell)
{
	int		i;
	char	**paths;
	char	*complete_path;

	i = 0;
	while (shell->environ[i] && ft_strncmp(shell->environ[i], "PATH=", 5) != 0)
		i++;
	if (!shell->environ[i])
	{
		shell->path_flag = 1;
		return (NULL);
	}
	paths = ft_split(shell->environ[i] + 5, ':');
	complete_path = check_all_paths(arg, paths);
	if (!complete_path)
		return (ft_free_all(paths), NULL);
	return (ft_free_all(paths), complete_path);
}

/*
 * Executes a command by finding the right path and calling execve
 * Handles errors like command not found or no such file
 */
void	ft_exec_cmd(char **arg, t_shell *shell)
{
	char	*good_path;

	good_path = find_good_path(arg[0], shell);
	if (!good_path || ft_strchr(arg[0], '/') || ft_is_builtin(arg[0]) == 2)
	{
		if (manage_no_path(arg, shell))
		{
			free(good_path);
			ft_free_program(shell);
			exit(shell->error);
		}
		else if (shell->path_flag == 1)
			ft_no_file_or_directory(arg[0]);
		else
			ft_cmd_not_found(arg[0]);
		ft_free_program(shell);
		exit(127);
	}
	else if (execve(good_path, arg, shell->environ) == -1)
	{
		free(good_path);
		ft_cmd_not_found(arg[0]);
		ft_free_program(shell);
		exit(127);
	}
}
