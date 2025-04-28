/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:52:13 by sferrad           #+#    #+#             */
/*   Updated: 2024/11/23 16:10:34 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_uputnbr(unsigned int nb)
{
	int	i;

	i = ft_unbr(nb);
	if (nb <= 9)
	{
		ft_putchar(nb + '0');
	}
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	return (i);
}

int	ft_unbr(unsigned int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

int	ft_print_hex(char c, unsigned int n)
{
	char	*hex;
	int		count;

	count = 0;
	if (c == 'x')
		hex = "0123456789abcdef";
	else if (c == 'X')
		hex = "0123456789ABCDEF";
	if (n == 0)
	{
		ft_putchar('0');
		return (1);
	}
	if (n >= 16)
		count += ft_print_hex(c, n / 16);
	ft_putchar(hex[n % 16]);
	return (count + 1);
}

int	ft_print_hex_pointer(unsigned long long n)
{
	char	*hex;
	int		count;

	count = 0;
	hex = "0123456789abcdef";
	if (n == 0)
	{
		ft_putchar('0');
		return (1);
	}
	if (n >= 16)
		count += ft_print_hex_pointer(n / 16);
	ft_putchar(hex[n % 16]);
	return (count + 1);
}

int	ft_print_pointer(void *ptr)
{
	int					count;
	unsigned long long	adress;
	unsigned long long	temp;

	adress = (unsigned long long)ptr;
	temp = adress;
	count = 2;
	if (ptr == NULL)
	{
		ft_putstr("(nil)");
		count = 5;
		return (count);
	}
	while (temp >= 16)
	{
		temp /= 16;
		count++;
	}
	ft_putstr("0x");
	ft_print_hex_pointer(adress);
	return (count + 1);
}
