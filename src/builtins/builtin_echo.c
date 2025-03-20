/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:16:04 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/13 09:53:04 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structs.h"



/*tests
echo
echo "hello"
echo  "hello hello"
echo hello1 hello2
echo -n hello
echo -n hello hello
echo -nnnnnnn
echo -n -nnnnnnnn
echo hello -n
echo 
*/


static bool	ft_is_n_option(char *str)
{
	if (*str != '-')
		return (false);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (false);
		str++;
	}
	return (true);
}

/* STEPS:
1 - Check the option “-nnnn…” (could be as second and the following arguments)
2 - Print the arguments with space between each other;
3 - If option print “\n” in the end;
*/

/*TO BE SOLVED:
1 -$? should be at the parsing stage cmd.expanded args[i] = shell.exit_code
*/

int	ft_builtin_echo(t_shell *shell, t_exec *exec_node)
{
	char 	**echo_args;
	bool    n_op;
	int		i;
	(void)shell;

	i = 0;
	echo_args = &(exec_node->av[1]);
	while ((echo_args[i] != NULL) && (ft_is_n_option(echo_args[i])))
	{
		n_op = true;
		i ++;
	}
	while (echo_args[i])
	{
		ft_putstr_fd(echo_args[i], STDOUT_FILENO);
		if (echo_args [i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i ++;
	}
	if (n_op == false)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (ENO_SUCCESS);
}
