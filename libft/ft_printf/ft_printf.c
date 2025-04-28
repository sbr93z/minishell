/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:31:31 by sferrad           #+#    #+#             */
/*   Updated: 2024/11/22 19:16:45 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *f, ...)
{
	va_list	args;
	int		i;
	int		length;

	length = 0;
	i = 0;
	va_start(args, f);
	if (!f)
		return (-1);
	while (f[i])
	{
		if (f[i] != '%')
			length += ft_putchar(f[i]);
		if (f[i] == '%' && f[i + 1])
		{
			length += ft_conv(f[i + 1], args);
			i++;
		}
		i++;
	}
	return (length);
}
