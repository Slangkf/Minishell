/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:08:22 by seruff            #+#    #+#             */
/*   Updated: 2025/06/17 13:58:26 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * Updates PWD and OLDPWD environment variables after directory change
 * Retrieves current directory and updates shell environment
 * Returns 0 on success, 1 on error
 */
int	update_env_pwd(t_shell *shell, char *old)
{
	char	pwd[10000];

	if (!getcwd(pwd, sizeof(pwd)))
	{
		write(2, "chdir: error retrieving current directory:", 42);
		write(2, "getcwd: cannot access parent directories: ", 42);
		write(2, "No such file or directory\n", 26);
		return (1);
	}
	if (old)
	{
		if (add_element_env(shell, "OLDPWD", old) == 1)
			return (1);
	}
	if (add_element_env(shell, "PWD", pwd) == 1)
		return (1);
	return (0);
}
