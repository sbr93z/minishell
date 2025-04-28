/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:23:56 by sferrad           #+#    #+#             */
/*   Updated: 2025/04/14 14:40:11 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	skip_whitespace(const char *s, int i)
{
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (i);
}

int	skip_quotes(const char *s, int *i, char quote)
{
	(*i)++;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	if (s[*i] == quote)
		(*i)++;
	return (*i);
}

int	count_words(const char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		i = skip_whitespace(s, i);
		if (s[i] == '\0')
			break ;
		count++;
		while (s[i] && s[i] != ' ' && s[i] != '\t')
		{
			if (s[i] == '"' || s[i] == '\'')
				skip_quotes(s, &i, s[i]);
			else
				i++;
		}
	}
	return (count);
}

char	*extract_word(const char *s, int *i, t_gc_list *gc)
{
	int		k;
	char	quote;
	char	*word;

	k = 0;
	word = gc_malloc(ft_strlen(s) + 1, gc);
	if (!word)
		return (NULL);
	while (s[*i] && s[*i] != ' ' && s[*i] != '\t')
	{
		if (s[*i] == '"' || s[*i] == '\'')
		{
			quote = s[*i];
			(*i)++;
			while (s[*i] && s[*i] != quote)
				word[k++] = s[(*i)++];
			if (s[*i] == quote)
				(*i)++;
		}
		else
			word[k++] = s[(*i)++];
	}
	word[k] = '\0';
	return (word);
}

char	**split_pars(const char *s, t_gc_list *gc)
{
	char	**result;
	int		word_count;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	word_count = count_words(s);
	result = gc_malloc((word_count + 1) * sizeof(char *), gc);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		i = skip_whitespace(s, i);
		if (s[i] == '\0')
			break ;
		result[j] = extract_word(s, &i, gc);
		if (!result[j])
			return (free_split(result, j), NULL);
		j++;
	}
	result[j] = NULL;
	return (result);
}
