/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 11:27:18 by sferrad           #+#    #+#             */
/*   Updated: 2024/11/18 13:42:19 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	char			*p;

	p = (char *) s;
	i = 0;
	while (p[i])
	{
		if (p[i] == (unsigned char)c)
			return (&p[i]);
		i++;
	}
	if (p[i] == (unsigned char)c)
		return (&p[i]);
	return (NULL);
}
