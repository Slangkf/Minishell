/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:03:03 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 10:41:30 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * Display error message
 */
static	void	print_error(t_shell *shell, char *args)
{
	write(2, "bash: export: `", 15);
	write(2, args, ft_strlen(args));
	write(2, "': not a valid identifier\n", 26);
	shell->error = 1;
}

void	ft_export_env(char **env)
{
	int	i;

	if (!env || !env[0])
		return ;
	i = 0;
	while (env[i])
	{
		if (!ft_strcmp(env[i], "_="))
			i++;
		write(STDIN_FILENO, "export ", 7);
		write(STDIN_FILENO, env[i], ft_strlen(env[i]));
		write(STDIN_FILENO, "\n", 1);
		i++;
	}
}

/*
 * Check the valid format of the args such as : KEY=value
 * And not KEY = value or 32@KEY=value
 * Key only take alphabetic caracteres no special one
 */
static	int	export_check_cmd(char *key)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(key[0]) || key[0] == '_'))
		return (1);
	while (key[i])
	{
		if (!(ft_isalpha(key[i])
				|| ft_isalnum(key[i]) || key[i] == '_'))
			return (1);
		i++;
	}
	return (0);
}

/*
 * Add element into the environnement of Minishell(Turtle)
 */
static	int	export_block(t_shell *shell, char *key, char *value, char *arg)
{
	if (export_check_cmd(key) == 1)
		print_error(shell, arg);
	else if ((export_check_cmd(key) == 0)
		&& ft_strcmp(value, "valid"))
	{
		if (add_element_env(shell, key, value) != 0)
			return (137);
	}
	else
	{
		if (add_element_env(shell, key, "") != 0)
			return (137);
	}
	return (0);
}

int	export_cmd(t_shell *shell, char **args)
{
	int		i;
	int		ret;
	char	**splitted;

	i = 1;
	if (!args[1] || !empty_string(args[1]))
		return (0);
	while (args[i])
	{
		splitted = split_key_value_env(args[i]);
		if (!splitted)
			return (137);
		ret = export_block(shell, splitted[0], splitted[1], args[i]);
		if (ret == 137)
			return (ft_free_array(splitted), 137);
		ft_free_array(splitted);
		i++;
	}
	return (0);
}
