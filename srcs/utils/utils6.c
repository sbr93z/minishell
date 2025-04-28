/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 13:46:36 by sferrad           #+#    #+#             */
/*   Updated: 2025/04/25 01:51:50 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

char	**handle_input(char *buffer, t_mini *shell, t_gc_list *gc)
{
	t_parse_state	state;

	state.args = split_pars(buffer, gc);
	if (!state.args || !state.args[0])
		return (NULL);
	state.i = 0;
	state.pipe_found = 0;
	shell->in_command = 0;
	return (state.args);
}

int	print_error(char *cmd, char *msg, int ret)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msg, 2);
	return (ret);
}
