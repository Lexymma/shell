/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:27:56 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/07 12:21:27 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structs.h"

/*
1 - Get cwd with getcwd (from unistd.h);
2 - Check error with getcwd
3 - Print cwd with “\n”;
4 - Don’t forget free as getcwd return char * allocated by malloc;
*/

/*
NOTES - TO BE TESTED/FIXED:
1 - variables PWD and shell.cwd can't be in conflict;
*/

int builtin_pwd(t_shell shell, t_node *cmd)
// int builtin_pwd(void)
{
	char *cwd;

	cwd = getcwd(NULL, 0);// malloc!!
	if (!cwd)
	{
		ft_err_msg("pwd", "cwd error", NULL);
		return (ENO_GENERAL); //not exit from proccess
	}
	printf("%s\n", cwd);
	free(cwd);
	return (ENO_SUCCESS);
}
