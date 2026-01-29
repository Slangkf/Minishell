/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:15:04 by seruff            #+#    #+#             */
/*   Updated: 2024/11/26 16:16:04 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <stdint.h>

int		ft_type(const char format, va_list args);
int		ft_printf(const char *format, ...);
int		ft_printperc(void);
int		ft_printnbr(int n);
int		ft_printstr(char *s);
int		ft_print_hex(unsigned int n, const char format);
int		ft_print_uint(unsigned int n);
int		ft_putchar(int c);
int		ft_print_adr(uintptr_t p);
int		ft_print_adx(uintptr_t p);

void	ft_putstr(char *s);

#endif// FT_PRINTF_H
