/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:46:32 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 11:30:52 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_command	*create_cmd(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->files = NULL;
	cmd->nb_files = 0;
	cmd->entry_fd = -1;
	cmd->infile_dup = 0;
	cmd->outfile_dup = 0;
	cmd->next = NULL;
	return (cmd);
}

/*
 * Copy the main environnement into the minishell(turtle)
 */
static	int	fill_shell_env(char **env, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
			return (137);
		i++;
	}
	env[i] = NULL;
	return (0);
}

static	char	*build_env(const char *key, const char *value)
{
	size_t	len;
	char	*entry;

	len = ft_strlen(key) + ft_strlen(value) + 2;
	entry = malloc(len);
	if (!entry)
		return (NULL);
	entry = ft_strjoin(key, "=");
	if (!entry)
		return (free(entry), NULL);
	entry = ft_strjoin(entry, value);
	if (!entry)
		return (free(entry), NULL);
	return (entry);
}

/*
 * Create an environment if there was nothing in with some basic KEY
 */
int	create_env(char **env)
{
	char	cwd[10000];

	getcwd(cwd, sizeof(cwd));
	env[0] = build_env("PWD", cwd);
	if (!env[0])
		return (free(env), 137);
	env[1] = build_env("OLDPWD", cwd);
	if (!env[1])
		return (ft_free_array(env), 137);
	env[2] = ft_strdup("_=/usr/bin/env");
	if (!env[2])
		return (ft_free_array(env), 137);
	env[3] = NULL;
	return (0);
}

/*
 * Check if there is an environnement or not 
 * If not build one
 * If there is copy it
 */
int	init_shell_env(t_shell *shell, char **envp)
{
	if (ft_array_len(envp) == 0)
	{
		shell->environ = malloc(sizeof(char *) * 4);
		if (!shell->environ)
			return (137);
		if (create_env(shell->environ))
			return (137);
	}
	else
	{
		shell->environ = malloc(sizeof(char *) * (ft_array_len(envp) + 1));
		if (!shell->environ)
			return (137);
		if (fill_shell_env(shell->environ, envp))
			return (137);
	}
	shell->path_flag = 0;
	return (0);
}
