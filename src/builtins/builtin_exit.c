/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:40:30 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/28 10:15:08 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structs.h"

/* no options according to the subject
*/

void	builtin_exit(t_shell shell, t_node *cmd)
{
    int	exit_code;

	exit_code = shell.exit_code;

	//It should be STDERR as in pipe or redirections doesn't printed in terminal. 
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (cmd->expanded_args[1])
	{
		exit_code = STDERR_FILENO;
		ft_err_msg("exit", cmd->expanded_args[1], "too many arguments");
	}
	//clean all
	exit(exit_code);
}