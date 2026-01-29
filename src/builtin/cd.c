/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:57:24 by seruff            #+#    #+#             */
/*   Updated: 2025/06/27 17:15:51 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * Checks if the given path is an accessible directory
 * Returns 0 if it's a valid directory
 * Returns 1 if the path doesn't exist or access error
 * Returns 2 if the path exists but is not a directory (file)
 */
int	check_directory_access(char *arg)
{
	struct stat	info;

	if (!arg)
		return (0);
	else if (stat(arg, &info) == 0 && S_ISDIR(info.st_mode))
		return (0);
	else if (stat(arg, &info) == 0 && !S_ISDIR(info.st_mode))
		return (2);
	else
		return (1);
}

/*
 * Executes the directory change and updates environment variables
 * Saves the old PWD and updates with the new directory
 * Returns 0 on success, 1 on error
 */
int	chdir_action(t_shell *shell, char *arg)
{
	int		ret;
	char	*temp;
	char	cwd[10000];

	temp = NULL;
	temp = getcwd(cwd, sizeof(cwd));
	if (!temp)
		temp = give_env_value(shell->environ, "PWD");
	else
		temp = ft_strdup(cwd);
	ret = chdir(arg);
	if (cd_fails(temp, arg, ret))
	{
		shell->error = 1;
		return (1);
	}
	if (update_env_pwd(shell, temp))
	{
		shell->error = 1;
		return (free(temp), 1);
	}
	return (free(temp), 0);
}

/*
 * Handles the case where cd is called without argument
 * Changes to the HOME directory
 * Returns 0 on success, 1 on error
 */
static int	cd_no_args(t_shell *shell)
{
	char	*t;
	int		ret;

	t = give_env_value(shell->environ, "HOME");
	if ((!t || !*t || ft_isspace(*t)))
	{
		if (t)
			free(t);
		return (print_error_cd(shell, NULL, 1), 1);
	}
	ret = !chdir_action(shell, t);
	free(t);
	return (ret);
}

/*
 * Main function for the cd command
 * Handles special cases: no argument, too many arguments and cd -
 * Returns 0 on success, 1 on error
 */
int	cd_cmd(t_shell *shell, char **args)
{
	char	*t;
	char	ret;

	if (!args || !args[1] || ft_isspace(args[1][0])
		|| args[1][0] == '\0' || !ft_strcmp(args[1], "--"))
		return (cd_no_args(shell));
	if (args[2])
		return (print_error_cd(shell, NULL, 2), 1);
	if (!ft_strcmp(args[1], "-"))
	{
		t = give_env_value(shell->environ, "OLDPWD");
		if (!t || !*t || ft_isspace(*t))
			return (print_error_cd(shell, NULL, 1), 1);
		ret = !chdir_action(shell, t);
		return (free(t), ret);
	}
	if (check_directory_access(args[1]) == 1)
		return (print_error_cd(shell, args[1], 3), 1);
	return (!chdir_action(shell, args[1]));
}

/*
 * Custom version of cd for pipelines
 */
void	ft_cd_in_pipe(char **args, t_shell *shell)
{
	if (ft_array_len(args) > 2)
	{
		write(2, "bash: cd: too many arguments\n", 29);
		ft_free_program(shell);
		exit(1);
	}
	else if (!args || !args[1] || ft_isspace(args[1][0])
		|| args[1][0] == '\0' || !ft_strcmp(args[1], "--"))
	{
		if (give_env_pos(shell->environ, "HOME") == -1)
		{
			write(2, "bash: cd: HOME not set\n", 23);
			ft_free_program(shell);
			exit(1);
		}
	}
	else if (chdir(args[1]) == -1)
	{
		write(2, "bash: cd: ", 10);
		perror(args[1]);
		ft_free_program(shell);
		exit(1);
	}
	ft_free_program(shell);
	exit(0);
}
