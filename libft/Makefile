# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seruff <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/26 15:00:03 by seruff            #+#    #+#              #
#    Updated: 2025/06/18 12:25:28 by seruff           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CF = -Wall -Werror -Wextra

SRC =					\
	$(SRC_DIR)/ft_atol.c		\
	$(SRC_DIR)/ft_atoi.c 		\
	$(SRC_DIR)/ft_arraylen.c 	\
	$(SRC_DIR)/ft_bzero.c 		\
	$(SRC_DIR)/ft_calloc.c		\
	$(SRC_DIR)/ft_count_carac.c	\
	$(SRC_DIR)/ft_isalpha.c		\
	$(SRC_DIR)/ft_iscapital.c	\
	$(SRC_DIR)/ft_isdigit.c		\
	$(SRC_DIR)/ft_isalnum.c		\
	$(SRC_DIR)/ft_isascii.c		\
	$(SRC_DIR)/ft_isprint.c		\
	$(SRC_DIR)/ft_isspace.c		\
	$(SRC_DIR)/ft_itoa.c 		\
	$(SRC_DIR)/ft_free_array.c	\
	$(SRC_DIR)/ft_memset.c 		\
	$(SRC_DIR)/ft_memmove.c 	\
	$(SRC_DIR)/ft_memcpy.c 		\
	$(SRC_DIR)/ft_memchr.c 		\
	$(SRC_DIR)/ft_memcmp.c 		\
	$(SRC_DIR)/ft_printf.c		\
	$(SRC_DIR)/ft_print_hex.c	\
	$(SRC_DIR)/ft_print_util.c	\
	$(SRC_DIR)/ft_putchar_fd.c 	\
	$(SRC_DIR)/ft_putstr_fd.c	\
	$(SRC_DIR)/ft_putendl_fd.c 	\
	$(SRC_DIR)/ft_putnbr_fd.c	\
	$(SRC_DIR)/ft_realloc.c		\
	$(SRC_DIR)/ft_strlen.c		\
	$(SRC_DIR)/ft_strjoin.c 	\
	$(SRC_DIR)/ft_strtrim.c 	\
	$(SRC_DIR)/ft_split.c 		\
	$(SRC_DIR)/ft_strmapi.c		\
	$(SRC_DIR)/ft_striteri.c	\
	$(SRC_DIR)/ft_strlcpy.c 	\
	$(SRC_DIR)/ft_strcpy.c	 	\
	$(SRC_DIR)/ft_strlcat.c 	\
	$(SRC_DIR)/ft_strchr.c		\
	$(SRC_DIR)/ft_strrchr.c		\
	$(SRC_DIR)/ft_strncmp.c 	\
	$(SRC_DIR)/ft_strcmp.c 		\
	$(SRC_DIR)/ft_strnstr.c 	\
	$(SRC_DIR)/ft_strstr.c 		\
	$(SRC_DIR)/ft_strdup.c 		\
	$(SRC_DIR)/ft_strndup.c		\
	$(SRC_DIR)/ft_substr.c 		\
	$(SRC_DIR)/ft_toupper.c 	\
	$(SRC_DIR)/ft_tolower.c 	\
	$(SRC_DIR)/get_next_line.c	\
	$(SRC_DIR)/get_next_line_utils.c

NAME = libft.a
LIB_DIR = include 
SRC_DIR = src
LIBFT_LIB = libft.h
PRINTF_LIB = ft_printf.h
GNL_LIB = get_next_line.h
OBJ = $(SRC:$(SRC_DIR)/%.c=$(SRC_DIR)/%.o)

all: 		$(NAME)

$(NAME):	$(OBJ)
		ar -rcs $(NAME) $(OBJ)

$(SRC_DIR)/%.o:	$(SRC_DIR)/%.c
		$(CC) $(CF) -c -I$(LIB_DIR) $< -o $@
clean:
		@rm -f $(SRC_DIR)/$(OBJ)
fclean: 	clean
		@rm -f $(NAME)
re:		fclean all

.PHONY: re clean fclean all
