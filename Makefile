# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seruff <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 15:55:32 by seruff            #+#    #+#              #
#    Updated: 2025/07/03 16:04:46 by seruff           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilation
CC = cc
CFLAGS = -Wall -Werror -Wextra
GNU_FLAGS = -lreadline

# Include
INC =	-L$(LIBFT_DIR) -lft
HEAD = $(HEAD_DIR)/.h

# Sources
SRC =  \
       src/builtin/builtin.c				\
       src/builtin/builtin2.c				\
       src/builtin/builtin3.c				\
       src/builtin/cd.c					\
       src/builtin/exit.c				\
       src/builtin/echo.c				\
       src/builtin/export.c				\
       src/builtin/unset.c				\
       src/builtin/utils_builtin.c			\
       src/execution/exec_cmd.c				\
       src/execution/manage_entries.c			\
       src/execution/manage_execution.c			\
       src/execution/manage_exits.c			\
       src/execution/new_pipex.c			\
       src/execution/utils/heredocnopipe_utils.c	\
       src/execution/utils/heredocpipe_utils.c		\
       src/execution/utils/infile_utils.c		\
       src/execution/utils/outfile_utils.c		\
       src/execution/utils/utils2.c			\
       src/execution/utils/utils.c			\
       src/execution/utils/utils_heredoc.c		\
       src/expandvar/clean_quotes.c			\
       src/expandvar/expand.c				\
       src/expandvar/expand_dollar.c			\
       src/expandvar/expand_main.c			\
       src/expandvar/filter.c				\
       src/expandvar/utils_expand1.c			\
       src/expandvar/utils_expand.c			\
       src/expandvar/word_splitting.c			\
       src/lexer/lexer.c				\
       src/lexer/lexer_verif.c				\
       src/main/main.c					\
       src/main/struct.c				\
       src/main/utils_struct.c				\
       src/parser/parse.c				\
       src/parser/parse_redir.c				\
       src/parser/split_cmd.c				\
       src/parser/utils_parser.c			\
       src/signal/handler.c				\
       src/redir/redir_check.c				\
       src/token/token.c				\
       src/utils/utils.c				\
       src/utils/utils_env2.c				\
       src/utils/utils_env.c				\
       src/utils/utils_file.c				\
       src/utils/utils_pwd.c				\

# Program
PROG = minishell

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Colors
GC = \033[0;32m
RC = \033[0;31m
ENDC = \033[0m


all:		$(LIBFT) $(PROG)

$(PROG):	$(SRC)
		@echo "$(GC)Compiling program..$(ENDC)"
		$(CC) $(CFLAGS) -o $(PROG) $(SRC) $(LIBFT) $(INC) $(GNU_FLAGS)
		@echo "$(RC)Pogram Minishell is ready to be used$(ENDC)"

$(LIBFT):
		@echo "$(GC)Building Libft$(ENDC)"
		@make all -C$(LIBFT_DIR)
		@echo "$(RC)Libft is ready$(ENDC)"
clean:
		@make fclean -C$(LIBFT_DIR)
		@echo "$(RC)Libft.a is removed$(ENDC)"

fclean:		clean
		@rm -f $(PROG)

re:		fclean all

.PHONY: 	re all fclean clean
