/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:11:09 by sferrad           #+#    #+#             */
/*   Updated: 2024/11/18 13:49:48 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*p;

	p = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (p[i] == (unsigned char)c)
			return ((char *)&p[i]);
		i++;
	}
	return (NULL);
}
