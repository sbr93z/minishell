/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:55:54 by sferrad           #+#    #+#             */
/*   Updated: 2025/04/25 16:24:21 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	is_valid_identifier(char *key)
{
	int	i;

	i = 1;
	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	**prepare_command_and_get_path(char *av, t_mini *shell, t_gc_list *gc)
{
	char	**cmd;
	char	*path;

	cmd = gc_split(av, ' ', gc);
	if (!cmd)
		return (ft_putstr_fd("Memory allocation failed\n", 2), NULL);
	path = path_tracking(cmd[0], shell, gc);
	if (!path)
		return (NULL);
	cmd[0] = path;
	return (cmd);
}

int	skip_whitespace(const char *s, int i)
{
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (i);
}

int	process_input(t_mini *shell, t_gc_list *gc)
{
	while (1)
	{
		ft_signal();
		if (handle_signal(shell))
			continue ;
		if (!read_input(shell))
			break ;
		if (ft_strlen(shell->buffer) == 0)
			continue ;
		process_command(shell, gc);
		clear_buffers(shell);
	}
	return (0);
}

char	*gc_substr(char const *s, unsigned int start, size_t len, t_gc_list *gc)
{
	char	*dup;
	size_t	i;
	size_t	j;

	i = start;
	j = 0;
	if (start >= ft_strlen(s))
		return (gc_strdup("", gc));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	dup = gc_malloc((len + 1) * sizeof(char), gc);
	if (!dup)
		return (NULL);
	while (j < len && s[i])
	{
		dup[j] = s[i];
		i++;
		j++;
	}
	dup[j] = '\0';
	return (dup);
}
