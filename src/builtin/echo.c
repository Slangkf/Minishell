/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 08:54:11 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 10:35:53 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 *	Gestion of space for the argument of echo
 */
static void	echo_utils(char **args, int *i, int *f)
{
	while (args[*i])
	{
		if (args[*i][0] == '\0')
		{
			(*i)++;
			continue ;
		}
		if (!*f)
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, args[*i], ft_strlen(args[*i]));
		*f = 0;
		(*i)++;
	}
}

/*
 * Echo should print is argument on the STDIN with or without '\n'
 * Depend on the option
 * Echo main bloc. i -> index
 * n -> flag for option n or 'nnnnn'
 * f -> flag for space
 * Loop on the option -n
 */
void	echo_cmd(char **args)
{
	int	i;
	int	f;
	int	n;

	i = 1;
	f = 1;
	n = 0;
	if (!args[1])
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	while (args[i] && (!ft_strcmp(args[i], "-n")
			|| (args[i][0] == '-' && args[i][1] == 'n'
		&& ft_count_carac(args[i], 'n') == ft_strlen(args[i]) - 1)))
	{
		i++;
		n = 1;
	}
	echo_utils(args, &i, &f);
	if (n == 0)
		write(STDOUT_FILENO, "\n", 1);
}
