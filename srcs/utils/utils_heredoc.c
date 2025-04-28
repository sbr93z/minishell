/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:57:00 by moel-hal          #+#    #+#             */
/*   Updated: 2025/04/25 16:22:56 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	change_quote(char quote, int i)
{
	if (quote == '\'' && i == 0)
		return (1);
	else if (quote == '"' && i == 0)
		return (2);
	else
		return (0);
}

void	ft_strncat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	if (!src)
		return ;
	i = ft_strlen(dst);
	j = 0;
	while (src[j] && j < size)
		dst[i++] = src[j++];
}

int	tab_len(char **tabl)
{
	int	i;

	i = 0;
	while (tabl[i])
		i++;
	return (i);
}

static char	**create_new_tab(char *str, t_gc_list *gc)
{
	char	**res;

	(void)gc;
	res = gc_malloc(sizeof(char *) * 2, gc);
	if (!res)
		return (NULL);
	res[0] = str;
	res[1] = NULL;
	return (res);
}

char	**add_argument(char **tabl, char *str, t_gc_list *gc)
{
	char	**res;
	int		i;

	(void)gc;
	if (!str)
	{
		if (tabl)
			free_tab(tabl);
		return (NULL);
	}
	if (!tabl)
		return (create_new_tab(str, gc));
	i = -1;
	res = gc_malloc(sizeof(char *) * (tab_len(tabl) + 2), gc);
	if (!res)
		return (free(str), NULL);
	while (tabl[++i])
		res[i] = tabl[i];
	res[i] = str;
	res[++i] = NULL;
	return (res);
}
