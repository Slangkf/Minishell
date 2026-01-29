/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:55:08 by seruff            #+#    #+#             */
/*   Updated: 2025/06/19 09:55:56 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * Checks if currently inside single or double quotes
 * Returns 1 if in quotes, 0 otherwise
 */
int	is_in_quote(t_shell *shell)
{
	if (shell->sq != 0 || shell->dq != 0)
		return (1);
	return (0);
}
