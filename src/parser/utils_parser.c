/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:09:16 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 11:09:12 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_syntax_error(t_shell *shell)
{
	shell->error = 2;
	write(2, "bash: syntax error near unexpected ", 36);
	write(2, "token `newline'\n", 16);
}

int	ft_is_cmd(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (ft_isalpha(line[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

/*
 * Check the presence of a T_PIPE types into the input
 * return (1) if yes
 * Otherwise (0)
 */
int	ft_check_pipe(char *types[MAX_TOKEN])
{
	int	i;

	i = 0;
	while (ft_strcmp(types[i], "NULL"))
	{
		if (!ft_strcmp(types[i], "T_PIPE"))
			return (1);
		i++;
	}
	return (0);
}
