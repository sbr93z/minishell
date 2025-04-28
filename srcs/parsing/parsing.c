/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:56:29 by sferrad           #+#    #+#             */
/*   Updated: 2025/04/25 01:52:22 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*find_executable_path(char *cmd, char **paths, t_gc_list *gc)
{
	int		i;
	int		j;
	char	*part_path;

	i = 0;
	while (paths[i])
	{
		part_path = gc_malloc(ft_strlen(paths[i]) + ft_strlen(cmd) + 2, gc);
		if (!part_path)
			return (NULL);
		ft_strlcpy(part_path, paths[i], ft_strlen(paths[i]) + 1);
		ft_strlcat(part_path, "/", ft_strlen(part_path) + 2);
		ft_strlcat(part_path, cmd, ft_strlen(part_path) + ft_strlen(cmd) + 1);
		if (access(part_path, F_OK | X_OK) == 0)
		{
			j = i + 1;
			while (paths[j])
			{
				j++;
			}
			return (part_path);
		}
		i++;
	}
	return (NULL);
}

void	restore_string(char *str, t_mini *shell)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] < 0)
			str[i] *= -1;
		i++;
	}
	shell->state = 127;
}

char	*path_tracking(char *cmd, t_mini *shell, t_gc_list *gc)
{
	char	**paths;
	char	*executable_path;

	if (!cmd || !shell->envp)
		return (NULL);
	if (cmd[0] == '/' || ft_strchr(cmd, '/'))
	{
		if (!handle_absolute_path(cmd, shell))
			return (NULL);
		if (access(cmd, X_OK) == 0)
			return (gc_strdup(cmd, gc));
		return (NULL);
	}
	paths = (char **)get_env_path(shell, gc);
	if (!paths)
		return (NULL);
	executable_path = find_executable_path(cmd, paths, gc);
	if (!executable_path && !shell->is_arg && !is_builtin(&cmd))
	{
		print_error(cmd, ": 1command not found\n", 0);
		shell->state = 127;
	}
	return (executable_path);
}

int	verify_path(char *av, t_mini *shell, t_gc_list *gc)
{
	char	*path;

	path = path_tracking(av, shell, gc);
	if (!path)
		return (0);
	return (1);
}

t_token	*parsing(char *buffer, t_mini *mini, t_gc_list *gc)
{
	t_token	*token_list;
	char	**args;

	if (!buffer || !mini->envp)
		return (NULL);
	if (!pars_buff(buffer))
		return (NULL);
	buffer = expand_vars(buffer, mini, gc);
	if (!buffer)
		return (NULL);
	if (is_only_empty_quotes(buffer))
		return (NULL);
	args = handle_input(buffer, mini, gc);
	if (!args)
		return (NULL);
	token_list = tokenize(args, mini, gc);
	return (token_list);
}
