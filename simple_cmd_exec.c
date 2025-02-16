/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:03:32 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/16 18:30:19 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
// #include "libft/libft.h"
#include <sys/wait.h>
#include <stdio.h>

static char	*find_cmd_path(char *cmd_name, t_shell shell);

static void del(void *content) {
    (void *)content;
	return;
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	t_shell shell;
	t_node 	cmd;
	t_list *path_next;
	t_list *path_next2;

	shell.path = ft_lstnew("/usr/bin/");
	path_next = ft_lstnew("/usr/local/bin");
	path_next2 = ft_lstnew("/home/mosokina/.local/bin");
	ft_lstadd_front(&shell.path, path_next);
	ft_lstadd_front(&shell.path->next, path_next2);

	
	char *expanded_args[3];
	cmd.expanded_args = expanded_args;

	// expanded_args[0] = "nocommand";
	expanded_args[0] = ".sss";
	// expanded_args[0] = "nocmd";

	// expanded_args[0] = "./test1";
	// expanded_args[1] = "-la";
	// expanded_args[1] = "invalidargs";
	// expanded_args[1] = "./tests/test.o";
	expanded_args[1] = "./tests/test.c";


	expanded_args[2] = NULL;
	shell.envp_arr = env;
	// printf("env %s\n", shell.envp_arr[0]);
	shell.exit_code = ft_exec_simple_cmd(shell, &cmd);
	printf("exit status %d\n", shell.exit_code);
	ft_lstclear(&shell.path, &del);
	return (0);
}

/* execute the simple command */
/*The return status is exit status as provided by waitpid(), 
or 128+n if the command was terminated by signal n.*/


/*error messsage: cdhhh: command not found
*/

int	ft_exec_simple_cmd(t_shell shell, t_node *cmd)
{
	int		tmp_status;
	//1. if no cmd
	// if (!node -> expanded_args) 
	// {
	// 	tmp_status = ft_check_redirection(node); // handle redirection
	// 	return (ft_reset_stds(piped), (tmp_status && ENO_GENERAL));
	// }
	//2. if builtin command
	if (ft_is_builtin((cmd->expanded_args)[0])) 
	{
		//to add redirections ...
		tmp_status = ft_exec_builtin(shell, cmd);
		return (tmp_status); //128+n if signals
	}
	//3. system command (child process)
	else
	{
		tmp_status = ft_exec_child(shell, cmd);
		return (tmp_status);
	}
}

/*3. if it's system command, it should be in child process*/

int	ft_exec_child(t_shell shell, t_node *cmd)
{
	char    *cmd_path;
    int		tmp_status;
	int		fork_pid;
	t_err_no	err_no;

	tmp_status = 0;
	
	// to handle signals??? ...
	fork_pid = fork();
	// to add error fork ...
    if (fork_pid == 0)
    {
		//to add redirections ...
		if (ft_strnstr(cmd->expanded_args[0], "/", ft_strlen(cmd->expanded_args[0])))
		{
			cmd_path = cmd->expanded_args[0];
			err_no = ft_check_access(cmd_path);
			if (err_no != ENO_SUCCESS)
			{
				//all clear;
				exit(err_no); // from child proccess
			}
			else if (execve(cmd_path, cmd->expanded_args, shell.envp_arr) == - 1)
			{
				// all clear;
				// ft_err_msg("execve error", strerror(errno), NULL);
				exit(ENO_GENERAL); // from child process;
			}
		}
		else
		{
			cmd_path = ft_get_env_path(shell, cmd->expanded_args[0], &err_no); // err_no as ptr for saving its value
			printf("path: %s\n", cmd_path);
			if (err_no != ENO_SUCCESS)
			{
				//all clear;
				exit(err_no); // from child proccess
			}
			else if (execve(cmd_path, cmd->expanded_args, shell.envp_arr) == - 1)
			{
				free(cmd_path);
				// all clear;
				// ft_err_msg("execve error", strerror(errno), NULL);
				exit(ENO_GENERAL); // from child process;
				}
			}
    }
    waitpid(fork_pid, &tmp_status, 0); //  tmp_status - parent process can retrieve the exit status of the child
	return (ft_get_exit_status(tmp_status));
}

int	ft_get_exit_status(int status)
{
	// if (WIFSIGNALED(status)) 	//to add tmp_status + 127(signals)

	// 	return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status)); // This MACROS WEXITSTATUS shifts to bits to right place,  as child exit status is stored in the higher bits.
}

t_err_no	ft_check_access(char *file) // check the permission to the file, print the error msg and return the error number
{	
	if (access(file, F_OK) != 0) //file doesn't exist
		// if (path_seach)
		// 	ft_err_msg(ERRMSG_CMD_NOT_FOUND, file);
		return (ft_err_msg(file, "No such file or directory", NULL), ENO_NOT_FOUND);
	else if (cmd_is_dir(file))
		return (ft_err_msg(file, "Is a directory", NULL), ENO_CANT_EXEC);
	else if (access(file, X_OK) != 0)// no execution rights
		return (ft_err_msg(file, "Permission denied\n", NULL), ENO_CANT_EXEC); //??check: strerror(errno) instead "Permition denied"
	return (ENO_SUCCESS);
}

/*This function, cmd_is_dir, checks if a given command (or file path) is a directory. 
It uses the stat function to retrieve information about the file 
and stores it in a struct stat called cmd_stat. 
The S_ISDIR macro is then used to check if the file is a directory 
by examining the st_mode field of cmd_stat. If the file is a directory, 
the function returns true; otherwise, it returns false*/

bool	cmd_is_dir(char *cmd)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}


///IN PROCCESS....
/*function for getting the proper path for the command
based on list of directrories from $PATH parsed as a list (t_list) in the start of the program
and saved as shell.path*/
char	*ft_get_env_path(t_shell shell, char *cmd_name, t_err_no *err_no)
{
	char *cmd_path;

	if (!ft_strcmp(cmd_name, ".."))
	{
		ft_err_msg(cmd_name, "command not found", NULL);
		*(err_no) = ENO_NOT_FOUND;
		return (NULL);
	}
	if (!ft_strcmp(cmd_name, "."))
	{
		ft_err_msg(cmd_name, "filename argument required", NULL);
		*(err_no) = 2;
		return (NULL);
	}
	//check (1)empty "PATH=" in env - if unset PATH??? (2) empty cmd name/cmd?
	cmd_path = find_cmd_path(cmd_name, shell); //malloc!!! to do free later
	if (!cmd_path)
	{
		ft_err_msg(cmd_name, "command not found", NULL);
		*(err_no) = ENO_NOT_FOUND;
		return (NULL);
	}
	*(err_no) = ENO_SUCCESS;
	return (cmd_path);
}

static char	*find_cmd_path(char *cmd_name, t_shell shell)
{
	t_list	*path_list;
	char 	*part_path;
	char 	*full_path;

	path_list = shell.path;
	while (path_list)
	{
		full_path = NULL;
		part_path = ft_strjoin(path_list->content, "/");
		full_path = ft_strjoin(part_path, cmd_name);
		free(part_path);
		if ((access(full_path, F_OK)) == 0)
			return (full_path);
		free(full_path);
		path_list = path_list->next;
	}
	return (NULL);
}

// t_err_no redirection(t_node)
// {
	
// }

// ft_out
// ft_is
// ft_append


// heredoc
