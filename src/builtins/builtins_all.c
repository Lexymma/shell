/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:07:12 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/11 23:33:06 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structs.h"

bool ft_is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (false);
	if (!ft_strcmp(cmd_name, "echo") 
		|| !ft_strcmp(cmd_name, "cd") 
		|| !ft_strcmp(cmd_name, "exit") 
		|| !ft_strcmp(cmd_name, "export")
		|| !ft_strcmp(cmd_name, "unset")
		|| !ft_strcmp(cmd_name, "pwd")
		|| !ft_strcmp(cmd_name, "env"))
		return (true);
	return (false);
}

/*EXIT_STATUS FOR BUILTINS: zero if they succeed and a non-zero status on failure, 
so they may be used by the conditional and list constructs.

All builtins return an exit status of 2 to indicate incorrect usage, 
generally invalid options or missing arguments.*/

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len > s2_len)
		return (ft_strncmp(s1, s2, s1_len));
	else
		return (ft_strncmp(s1, s2, s2_len));
}

int		ft_exec_builtin(t_shell shell, t_node *cmd)
{
	char *cmd_name;

	cmd_name = cmd->expanded_args[0];
	if (!ft_strcmp(cmd_name, "echo"))
		return (builtin_echo(shell, cmd));
	else if (!ft_strcmp(cmd_name, "cd"))
		return (builtin_cd(shell, cmd));
	else if (!ft_strcmp(cmd_name, "export"))
		return (builtin_export(shell, cmd));
	else if (!ft_strcmp(cmd_name, "unset"))
		return (builtin_unset(shell, cmd));
	else if (!ft_strcmp(cmd_name, "env"))
		return (builtin_env(shell, cmd));
	else if (!ft_strcmp(cmd_name, "pwd"))
		return (builtin_pwd(shell, cmd));
	else if (!ft_strcmp(cmd_name, "exit"))
		builtin_exit(shell, cmd);
	return (ENO_NOT_FOUND);
}
