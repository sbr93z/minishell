/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sferrad <sferrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:16:10 by moel-hal          #+#    #+#             */
/*   Updated: 2025/04/19 03:31:31 by sferrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static bool	ft_isnum(char c)
{
	return ((c >= '0' && c <= '9'));
}

bool	exit_state(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isnum(str[i]))
		return (false);
	while (ft_isnum(str[i]))
		i++;
	while (ft_isspace(str[i]))
		i++;
	return (!str[i]);
}

static void	cleanup_and_exit(t_mini *shell, t_gc_list *gc, int status)
{
	rl_clear_history();
	cleanup_states(shell);
	gc_free_all(gc);
	free_env_list(shell->env_list);
	exit(status);
}

int	ft_exit(char **args, t_gc_list *gc, t_mini *shell)
{
	int	status;

	printf("exit\n");
	if (!args[1])
		cleanup_and_exit(shell, gc, EXIT_SUCCESS);
	if (!exit_state(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		cleanup_and_exit(shell, gc, EXIT_FAILURE);
	}
	if (!args[2])
	{
		status = atoi(args[1]);
		cleanup_and_exit(shell, gc, status);
	}
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	return (1);
}
