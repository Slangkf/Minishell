/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:04:24 by seruff            #+#    #+#             */
/*   Updated: 2025/07/01 11:30:29 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// INCLUDES
# include "libft/include/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sysexits.h>
# include <unistd.h>

// COLORS
# define GC "\033[0;32m"
# define RC "\033[0;31m"
# define EC "\033[0m"

// MACROS
# define CMD_NOT_FOUND 127
# define MAX_TOKEN 1000000

// STRUCTURES
typedef struct s_shell			t_shell;
typedef struct s_command		t_command;

typedef struct s_token
{
	char						**token;
	char						**types;
}								t_token;

typedef struct s_shell
{
	int							sq;
	int							dq;
	int							error;
	int							path_flag;
	char						*oldpwd;
	char						**environ;
	t_command					*cmds;
	t_token						*tok;
}								t_shell;

typedef struct s_file
{
	int							mode;
	int							expand;
	int							f_last_in;
	int							f_last_out;
	char						*file;
	char						*delimiter;
}								t_file;

typedef struct s_command
{
	int							nb_files;
	int							nb_infiles;
	int							nb_outfiles;
	int							last_in;
	int							last_out;
	int							entry_fd;
	int							infile_dup;
	int							outfile_dup;
	char						**args;
	t_file						*files;
	t_command					*next;
}								t_command;

// FUNCTIONS_FILES

// MAIN
int								read_line(t_shell *shell);

// STRUCT
t_command						*create_cmd(void);
int								init_shell_env(t_shell *shell, char **envp);
int								create_env(char **env);

// PARSER
t_command						*build_cmd(t_shell *shell, t_token *tok,
									int start, int end);
void							append_cmd(t_command **head, t_command **curr,
									t_command *new);
int								ft_check_pipe(char *types[MAX_TOKEN]);
int								ft_is_cmd(char *line);
int								fill_cmd(t_command *cmd, t_shell *shell,
									int start, int end);
int								parse(t_shell *shell);
void							print_syntax_error(t_shell *shell);
int								fill_redir_parse(t_command *cmd, char *word,
									char *file);

// UTILS
int								ft_is_operator(char c);
int								position_carac(char *line, char c, int i);
int								verif(char *line);
int								empty_string(char *line);
char							*remove_quotes(char *s);

//UTILS_FILE
int								check_file(char *s, t_shell *shell);
void							check_redir(t_shell *shell);

// LEXER
int								ft_isredirec(char *s);
int								lexer(t_shell *shell, char *line);
int								give_types(t_shell *shell);

// LEXER_VERIF
int								main_lexer_verif(t_shell *shell);

// UTIL_EXPAND
int								is_in_quote(t_shell *shell);
int								is_quote(char c);
int								is_var_start(char c);
int								is_var_char(char c);
char							*append_str(char *res, char *add, int len);
char							*append_char(char *res, char c);
// EXPAND
int								split_args(t_command *cmd);
int								main_expand(t_shell *shell);
int								filter(t_command *cmd);
int								filter_main(t_command *cmd);
char							*filter_string(char *s);
char							*expand_var(t_shell *shell, const char *line,
									int *i);
char							*expand_dollar(t_shell *shell,
									const char *input, int *i);
char							*expand(t_shell *s, char *line);
char							*clean_quotes(char *s);

// TOKEN
char							**split_custom(const char *s);

// EXECUTION
void							ft_manage_execution(t_shell *shell);
void							ft_manage_redirections(t_shell *shell);
void							ft_new_pipex(t_shell *shell);
int								ft_manage_entries(t_shell *shell,
									t_command *current, int prev_pipe_fd);
int								ft_manage_exits(t_command *current,
									int *pipe_fd);
void							ft_exec_cmd(char **arg, t_shell *shell);
int								ft_manage_heredoc_in_pipe(t_shell *shell);
int								ft_heredoc_mode(t_shell *shell,
									t_command *current, t_file *heredoc);
void							ft_manage_heredoc_no_pipe(t_shell *shell);
void							ft_heredoc_mode_no_pipe(t_file *current,
									t_shell *shell);
void							ft_read_terminal(t_shell *shell,
									t_file *current, int tmp_pipe);
void							ft_warning_heredoc(char *args);
int								ft_infile_mode(t_command *current,
									t_file *infile);
int								ft_check_infile(t_shell *shell, char *infile);
int								ft_outfile_mode(t_command *cmd, t_file *outfile,
									int append_mode);
int								ft_outfile_mode_no_pipe(t_shell *shell,
									char *outfile, int append_mode);
int								ft_new_strchr(char *s, int c);
void							ft_print_error(char *message);
void							ft_pipex_error(t_shell *shell, char *message);
void							ft_cmd_not_found(char *arg);
void							ft_no_file_or_directory(char *arg);
void							ft_clean_fd(void);
void							ft_free_all(char **input);
char							*ft_check_delimiter(t_shell *shell,
									t_file *current, char *s);
char							*ft_check_expand(t_shell *shell,
									t_file *current, char *line);

// BUILT-IN
void							ft_hard_builtin(t_shell *shell, char **arg);
void							ft_hard_builtin_in_pipe(t_command *current,
									t_shell *shell);
void							ft_soft_builtin(char **args, t_shell *shell);
void							echo_cmd(char **arg);
void							pwd_cmd(t_shell *shell);
int								cd_cmd(t_shell *shell, char **arg);
int								cd_fails(char *temp, char *arg, int ret);
int								check_directory_access(char *arg);
void							ft_cd_in_pipe(char **args, t_shell *shell);
void							env_cmd(char **env);
void							print_error_cd(t_shell *shell, char *s,
									int type);
// BUILT-IN2
int								ft_string_digit(char *s);
int								export_cmd(t_shell *shell, char **args);
void							ft_export_env(char **env);
int								unset_cmd(t_shell *shell, char **args);
void							exit_cmd(t_shell *shell, char **args);
int								exit_ctrld(t_shell *shell);
int								ft_str_digit(char *s);
void							print_exit(int type, char *s);
int								ft_is_builtin(char *cmd);
char							**split_key_value_env(char *s);
int								file_exist(char *file);
int								is_numeric(t_shell *shell, char *s);

// UTILS_ENV
int								give_env_pos(char **arr_env, char *s);
int								size_env_value(char *line);
char							*give_env_value(char **arr_env, char *s);
int								check_key_env(char *s);

// UTILS_ENV2
int								remove_element_env(t_shell *shell, int elemnt);
int								add_element_env(t_shell *shell, char *key,
									char *value);
char							**ft_realloc_env(char **environ);

// UTILS_PWD
int								update_env_pwd(t_shell *shell, char *old);

// SIGNAL
void							signal_received(void);
void							handle_sig(int sig);

// FREE PROGRAM
void							ft_free_program(t_shell *shell);
void							ft_free_tokens(t_token *token_struct);
void							free_cmd_list(t_command *cmd);
void							free_args(char **args);

// GLOBAL
extern volatile sig_atomic_t	g_signal;

#endif
