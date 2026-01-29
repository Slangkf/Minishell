/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:41:53 by seruff            #+#    #+#             */
/*   Updated: 2025/07/03 15:52:57 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "ft_printf.h"
# include "get_next_line.h"
# include <limits.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int			ft_atoi(const char *str);
int			ft_atoi_strict(const char *str, int *out);
int			ft_array_len(char **array);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_strisalpha(char *s);
int			ft_isascii(int c);
int			ft_iscapital(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_signe(char c);
int			ft_atoll(char *s);

long		ft_atol(char *string);

char		*ft_itoa(int n);
char		*ft_realloc(char *str, int new_size);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *S, const char *s, size_t len);
char		*ft_strdup(const char *s);
char		*ft_strndup(const char *s, size_t n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s, char const *set);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strstr(char *s, char *word);
char		**ft_realloc_array(char **str, int new_size);
char		**ft_split(char const *s, char c);

size_t		ft_count_carac(char *s, char c);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlen(const char *string);

void		*ft_realoc(void *str, size_t old_s, size_t new_s);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		ft_free_array(char **dest);
void		*ft_memchr(const void *s, int c, size_t count);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memset(void *dest, int c, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));

#endif // LIBFT_H
