/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:12:38 by sferrad           #+#    #+#             */
/*   Updated: 2024/11/16 22:39:04 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*pointer;

	pointer = (void *)malloc(elementCount * elementSize);
	if (!pointer)
		return (NULL);
	ft_bzero(pointer, elementCount * elementSize);
	return (pointer);
}
