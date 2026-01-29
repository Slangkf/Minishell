/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:05:43 by seruff            #+#    #+#             */
/*   Updated: 2024/12/23 11:54:21 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "ft_printf.h"
#include <stdio.h>

int	ft_putchar(int c)
{
	char	ca;

	ca = (char)c;
	write(1, &ca, 1);
	return (1);
}

int	ft_type(const char format, va_list args)
{
	int	count;

	count = 0;
	if (format == '%')
		count += ft_printperc();
	else if (format == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (format == 's')
		count += ft_printstr(va_arg(args, char *));
	else if (format == 'd' || format == 'i')
		count += ft_printnbr(va_arg(args, int));
	else if (format == 'x' || format == 'X')
		count += ft_print_hex(va_arg(args, unsigned int), format);
	else if (format == 'p')
		count += ft_print_adr(va_arg(args, uintptr_t));
	else if (format == 'u')
		count += ft_print_uint(va_arg(args, unsigned int));
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int			count;
	int			i;
	va_list		args;

	count = 0;
	i = 0;
	if (!format || format[0] == '\0')
		return (0);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			count += ft_type(format[i + 1], args);
			i++;
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
/*
int	main()
{
	ft_printf("%s %u", "Hello buddies" , 684687867);
	printf("%s %u", "Hello buddies", 684684684);
	return (0);
}
*/
