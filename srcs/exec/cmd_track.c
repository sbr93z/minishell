/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_track.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:50:04 by sferrad           #+#    #+#             */
/*   Updated: 2025/04/25 17:14:15 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*cmd_finder(char **cmd, char **env)
{
	int		i;
	char	*tmp;
	char	*slash;

	if (cmd[0][0] == '\0')
		return (free_tab(env), NULL);
	slash = ft_strjoin("/", cmd[0]);
	if (!slash)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		tmp = ft_strjoin(env[i], slash);
		if (!tmp)
			return (free(slash), NULL);
		if (access(tmp, F_OK) == 0)
			return (free_tab(env), free(slash), tmp);
		free(tmp);
	}
	return (free_tab(env), free(slash), NULL);
}

static void	error_exit(char *msg, char *cmd, char *path, t_mini *minishell)
{
	ft_putstr_fd(msg, 2);
	ft_putendl_fd(cmd, 2);
	if (path)
		free(path);
	ft_end(minishell);
	gc_free_all(minishell->gc);
	if (!ft_strncmp(msg, "Permission denied", 17)
		|| !ft_strncmp(msg, "Is a directory", 14))
		exit(126);
	exit(127);
}

void	error_msg(char *path, char **cmd, t_mini *minishell)
{
	struct stat	st;

	(void)minishell;
	if (path && stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		error_exit("Is a directory: ", cmd[0], path, minishell);
	if (ft_strchr(cmd[0], '/'))
		ft_putstr_fd("No such file or directory : ", 2);
	else if (!path)
		ft_putstr_fd("command not found: ", 2);
	else if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
		error_exit("Permission denied: ", cmd[0], path, minishell);
	if (path)
		free(path);
	ft_putendl_fd(cmd[0], 2);
	ft_end(minishell);
	gc_free_all(minishell->gc);
	exit(127);
}

void	end_exec(char *path, char **cmd, char **env, t_mini *minishell)
{
	if (!path)
		error_msg(path, cmd, minishell);
	free_all_heredoc(minishell->command);
	execve(path, cmd, env);
	error_msg(path, cmd, minishell);
}

void	excute(char **cmd, char **env, t_mini *minishell)
{
	int		i;
	char	*path;
	char	**tmp_path;

	tmp_path = NULL;
	path = NULL;
	i = 0;
	if (!cmd)
		return ;
	if (ft_strchr(cmd[0], '/') && !access(cmd[0], F_OK | X_OK))
		path = ft_strdup(cmd[0]);
	else if (env[i] && !ft_strchr(cmd[0], '/'))
	{
		while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
			i++;
		if (env[i])
			tmp_path = ft_split(&env[i][5], ':');
		if (!tmp_path)
			error_msg(path, cmd, minishell);
		path = cmd_finder(cmd, tmp_path);
	}
	end_exec(path, cmd, env, minishell);
	exit(0);
}
