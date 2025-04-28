/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:56:58 by sferrad           #+#    #+#             */
/*   Updated: 2025/04/24 16:29:17 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>

void	*gc_malloc(size_t size, t_gc_list *gc)
{
	t_gc_node	*node;
	void		*ptr;

	if (!gc)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = malloc(sizeof(t_gc_node));
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	node->ptr = ptr;
	node->next = gc->head;
	gc->head = node;
	return (ptr);
}

void	gc_free_all(t_gc_list *gc)
{
	t_gc_node	*current;
	t_gc_node	*tmp;

	if (!gc || !gc->head)
		return ;
	current = gc->head;
	while (current)
	{
		tmp = current;
		if (current->ptr != NULL)
		{
			free(current->ptr);
			current->ptr = NULL;
		}
		current = current->next;
		free(tmp);
	}
	gc->head = NULL;
}

char	*gc_strdup(const char *s, t_gc_list *gc)
{
	char	*dup;
	size_t	len;

	if (!s || !gc)
		return (NULL);
	len = ft_strlen(s);
	dup = gc_malloc(len + 1, gc);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, len + 1);
	return (dup);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*dup;
	size_t	j;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && i < n)
		i++;
	dup = malloc(i + 1);
	if (!dup)
		return (NULL);
	j = 0;
	while (j < i)
	{
		dup[j] = s[j];
		j++;
	}
	dup[i] = '\0';
	return (dup);
}
