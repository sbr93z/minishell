/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_gc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:59:09 by sferrad           #+#    #+#             */
/*   Updated: 2025/03/08 15:14:02 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	count_words(const char *str, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*str == c)
			in_word = 0;
		str++;
	}
	return (count);
}

static char	*gc_get_next_word(const char **str, char c, size_t *len)
{
	while (**str == c)
		(*str)++;
	*len = 0;
	while ((*str)[*len] && (*str)[*len] != c)
		(*len)++;
	return ((char *)*str);
}

static int	gc_fill_result(char **result, const char *str, char c,
		t_gc_list *gc)
{
	size_t	i;
	size_t	len;
	char	*word;

	i = 0;
	while (*str)
	{
		word = gc_get_next_word(&str, c, &len);
		if (len > 0)
		{
			result[i] = gc_malloc(len + 1, gc);
			if (!result[i])
				return (0);
			ft_strlcpy(result[i++], word, len + 1);
			str += len;
		}
	}
	result[i] = NULL;
	return (1);
}

char	**gc_split(const char *str, char c, t_gc_list *gc)
{
	char	**result;
	size_t	count;

	if (!str)
		return (NULL);
	count = count_words(str, c);
	result = gc_malloc((count + 1) * sizeof(char *), gc);
	if (!result)
		return (NULL);
	if (!gc_fill_result(result, str, c, gc))
		return (NULL);
	return (result);
}
