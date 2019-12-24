/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_up.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelvan-d <jelvan-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 09:08:48 by jelvan-d          #+#    #+#             */
/*   Updated: 2019/12/23 14:17:46 by jelvan-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static void	ft_print_x_up(unsigned long n, int *count)
{
	unsigned long	tmp;

	if (n > 15)
		ft_print_x_up(n / 16, count);
	tmp = n % 16;
	if (tmp > 9 && tmp < 16)
		ft_putchar_count((n % 16) + '7', count);
	else
		ft_putchar_count((n % 16) + '0', count);
}

static void	ft_reverse_pad_x_up(int len, int *count, t_printf *flag)
{
	if (flag->maxwidth == -2)
		flag->width -= len;
	while (flag->width > 0)
	{
		ft_putchar_count(' ', count);
		(flag->width)--;
	}
}

static void	ft_pad_x_up(int *count, t_printf *flag)
{
	while (flag->width > 0)
	{
		ft_putchar_count(' ', count);
		(flag->width)--;
	}
}

static void	ft_resolve_x_up(int numlen, int *count, t_printf *flag)
{
	int	tmp;

	tmp = numlen;
	if (flag->maxwidth > numlen)
		numlen = flag->maxwidth;
	if (flag->maxwidth > 0 &&
		(flag->maxwidth <= numlen || flag->maxwidth < flag->width))
		flag->width -= numlen;
	if (flag->width && flag->reverse != 1 && (flag->padding != 1
		|| flag->maxwidth != -2))
		ft_pad_x_up(count, flag);
	while (flag->maxwidth > tmp || (flag->width > numlen && flag->padding == 1))
	{
		ft_putchar_count('0', count);
		tmp -= -1;
		if (flag->padding == 1 && flag->reverse != 1)
			(flag->width)--;
	}
}

void		ft_putnbr_hex_up(unsigned long n, int *count, t_printf *flag)
{
	int				numlen;

	numlen = ft_strlen_hex(n);
	if (flag->precision == 1 && flag->maxwidth == -2 && n == 0)
		numlen = 0;
	if (flag->maxwidth == -2 && flag->reverse != 1 && flag->padding != 1)
		flag->width -= numlen;
	ft_resolve_x_up(numlen, count, flag);
	if (n == 0 && flag->precision == 1 &&
		(flag->maxwidth == -2 || flag->maxwidth == 0))
		n = 0;
	else
		ft_print_x_up(n, count);
	if (flag->width > 0)
		ft_reverse_pad_x_up(numlen, count, flag);
}
