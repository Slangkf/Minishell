/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclouet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:13:20 by tclouet           #+#    #+#             */
/*   Updated: 2025/07/04 10:48:39 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	int	need_to_see(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=' && s[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

/*
 * PWD
 * Get the path of the actual current working directory
 */
void	pwd_cmd(t_shell *shell)
{
	char	*res;
	char	buf[1024];

	res = getcwd(buf, sizeof(buf));
	if (!res)
	{
		shell->error = 1;
		write(2, "pwd: error retrieving current directory: ", 41);
		write(2, "getcwd: cannot access parent directories:", 41);
		write(2, " No such file or directory", 26);
		write(2, "\n", 1);
		return ;
	}
	write(STDOUT_FILENO, buf, ft_strlen(buf));
	write(STDOUT_FILENO, "\n", 1);
}

/* 
 * ENV
 * Display every environnement variable
 * of the program
 */
void	env_cmd(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (need_to_see(env[i]) == 0)
		{
			write(STDOUT_FILENO, env[i], ft_strlen(env[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		i++;
	}
}
