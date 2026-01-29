/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 07:54:26 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 10:42:23 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * Remove the Key=value of the environnement
 */
static	int	remove_var(t_shell *shell, char *arg)
{
	int	element;

	element = give_env_pos(shell->environ, arg);
	if (element != -1 && remove_element_env(shell, element) == 1)
		return (137);
	return (0);
}

/*
 * Don't remove secure var such as $_ 
 */
int	unset_cmd(t_shell *shell, char **args)
{
	int	i;

	i = 1;
	if (!args[i])
		return (0);
	while (args && args[i])
	{
		if (ft_count_carac(args[i], '=') != 0
			|| !ft_strcmp(args[i], "_") || !ft_strcmp(args[i], "_="))
		{
			i++;
			continue ;
		}
		else if (remove_var(shell, args[i]) == 1)
		{
			shell->error = 137;
			return (137);
		}
		i++;
	}
	return (0);
}
