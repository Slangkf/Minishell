/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:23:54 by seruff            #+#    #+#             */
/*   Updated: 2024/12/02 12:12:00 by seruff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_adr(uintptr_t p)
{
	int	count;

	count = 0;
	if (p == 0)
	{
		ft_printstr("(nil)");
		count += 5;
	}
	else
	{
		ft_printstr("0x");
		count += 2;
		count += ft_print_adx(p);
	}
	return (count);
}

int	ft_print_uint(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += ft_print_uint(n / 10);
	ft_putchar(n % 10 + '0');
	count++;
	return (count);
}

int	ft_print_adx(uintptr_t p)
{
	int		count;
	char	*hex;

	count = 0;
	hex = "0123456789abcdef";
	if (p >= 16)
		count += ft_print_adx(p / 16);
	ft_putchar(hex[p % 16]);
	count++;
	return (count);
}

int	ft_print_hex(unsigned int n, const char format)
{
	int		count;
	char	*hexmaj;
	char	*hexmin;

	count = 0;
	hexmaj = "0123456789ABCDEF";
	hexmin = "0123456789abcdef";
	if (n >= 16)
		count += ft_print_hex(n / 16, format);
	if (format == 'X')
		ft_putchar(hexmaj[n % 16]);
	else if (format == 'x')
		ft_putchar(hexmin[n % 16]);
	count++;
	return (count);
}
/*
int	main(void)
{
	unsigned int n = -264846;
	printf("ori: %u\n", n);
	ft_print_uint(n);
	return (0);
}
*/
