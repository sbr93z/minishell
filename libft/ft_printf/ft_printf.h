/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:14:29 by sferrad           #+#    #+#             */
/*   Updated: 2024/11/23 15:52:54 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_conv(char c, va_list args);
int	ft_putchar(int c);
int	ft_putstr(const char *s);
int	ft_printf(const char *f, ...);
int	ft_putnbr(int nb);
int	ft_nbr(int nb);
int	ft_uputnbr(unsigned int nb);
int	ft_unbr(unsigned int nb);
int	ft_print_hex(char c, unsigned int n);
int	ft_print_pointer(void *ptr);
int	ft_print_hex_pointer(unsigned long long n);
#endif