/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:36:58 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 10:50:21 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 *  Split the KEY and the VALUE for the export command
 *  Such as KEY=VALUE -> d[0] = KEY
 *  		      -> d[1] = VALUE
 *  		      -> d[2] = NULL
 */
char	**split_key_value_env(char *s)
{
	char	**d;
	char	*equal;

	equal = ft_strchr(s, '=');
	d = malloc(sizeof(char *) * 3);
	if (!d)
		return (NULL);
	d[0] = ft_substr(s, 0, equal - s);
	if (!d[0])
		return (NULL);
	if (ft_strlen(equal) == 0)
		d[1] = ft_strdup("");
	else
		d[1] = ft_substr(equal, 1, ft_strlen(equal));
	if (!d[1])
		return (free(d[0]), NULL);
	d[2] = NULL;
	return (d);
}

/*
 * Return if the builtins cmd is actually one who need to be executed into a pipe
 * or not (the one who modify the environnement or no)
 */
int	ft_is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	else if (!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "env"))
		return (2);
	return (0);
}
