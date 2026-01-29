/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:02:24 by seruff            #+#    #+#             */
/*   Updated: 2025/07/04 11:29:05 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

volatile sig_atomic_t	g_signal = 0;

/*
 * Processing the Lexer, Parser, Expander part 
 * and verifying the output of those func
 * Also taking care of modifying the error_code of the last function if
 * it was terminate by CTRL+C
 */
static	int	check_entry(t_shell *shell, char *line)
{
	int	ret;

	ret = lexer(shell, line);
	if (ret != 0)
		return (ret);
	ret = parse(shell);
	if (ret != 0)
		return (free_cmd_list(shell->cmds), free_cmd_list(shell->cmds), ret);
	if (g_signal == 130)
	{
		shell->error = 130;
		g_signal = 0;
	}
	ret = main_expand(shell);
	if (ret != 0)
		return (free_cmd_list(shell->cmds), free_cmd_list(shell->cmds), ret);
	return (0);
}

/*
 * Main part to launch the program
 * Take an input command line with readline()
 * If !line then readline received and EOF
 * Check if the input is valid
 * Add the input into history
 * Execute the valid command line
 * Clean every thing created 
 * Be ready for the next input
 */
int	read_line(t_shell *shell)
{
	char	*line;

	rl_on_new_line();
	line = readline(GC"Minishell"EC""RC"@"EC"Tclouet-Seruff"GC"$"EC"> ");
	if (!line)
	{
		free_args(shell->environ);
		rl_clear_history();
		exit_ctrld(shell);
	}
	if (verif(line) == 1 || !empty_string(line))
		return (free(line), 0);
	add_history(line);
	shell->error = check_entry(shell, line);
	if (shell->error)
		return (free(line), 0);
	check_redir(shell);
	ft_manage_execution(shell);
	free_cmd_list(shell->cmds);
	ft_free_tokens(shell->tok);
	ft_clean_fd();
	return (free(line), 1);
}

/*
 * Beginning of the program
 * Take the environnement of the precedent shell
 * Set the error_code to 0 as there was nothing before
 * Exit and clear the history
 */
int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	if (ac != 1)
		return (1);
	init_shell_env(&shell, envp);
	shell.error = 0;
	signal_received();
	while (1)
		read_line(&shell);
	rl_clear_history();
	(void)av;
	(void)ac;
	return (0);
}
