/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:59:19 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/07 15:18:49 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/structs.h"
#include <sys/wait.h>
#include <stdio.h>



static void del(void *content) {
    (void)content;
	return;
}



// typedef struct s_env
// {
// 	char		*value; //Value
// 	char		*key; //Key
// 	bool		is_export;
// 	bool		is_printed;
// }				t_env;

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	t_shell shell;
	t_node 	cmd;
	t_list *path_next;
	t_list *path_next2;
    shell.exit_code = 0;

    t_list  *envplist_start = malloc(sizeof(t_list));
    t_list  *envplist_next = malloc(sizeof(t_list));
    t_list  *envplist_next2 = malloc(sizeof(t_list));
    
    envplist_start->next = envplist_next;
    envplist_next->next = envplist_next2;
    envplist_next2->next = NULL;

    t_env   *env_1 = malloc(sizeof(t_env));
    t_env   *env_2 = malloc(sizeof(t_env));
    t_env   *env_3 = malloc(sizeof(t_env));

    env_1->key = "VAR";
    env_1->value = "10";

    env_2->key = "NEW_VAR";
    env_2->value = NULL;

    env_3->key = "VAR3";
    env_3->value = "hello";
    
    envplist_start->content = env_1;
    envplist_next->content = env_2;
    envplist_next2->content = env_3;

    shell.envp = envplist_start;    
    
    // t_list *io_list;
    // io_list = malloc(sizeof(t_list));
    // t_list *io_list2;
    // io_list2 = malloc(sizeof(t_list));


    // t_io    *io_1;
    // t_io    *io_2;
    // io_1 = malloc(sizeof(t_io));
    // io_2 = malloc(sizeof(t_io));


    // cmd.io_list = io_list;
    // io_list->content = (t_io*)io_1;
    // io_list->next = NULL;
    
    // io_list2->content = (t_io*)io_2;
    // io_list2->next = NULL;
    // ft_lstadd_back(&io_list, io_list2);

    // char *str_arr[2];
    // str_arr[0] = "outfile1";
    // str_arr[1] = NULL;
    // io_1->expanded_value = str_arr;

    // io_1->fd_here_doc = -1;
    // io_1->type = IO_APPEND;
    // io_1->value = "outfile1";

    // char *str_arr2[2];
    // str_arr2[0] = "outfile2";
    // str_arr2[1] = NULL;
    // io_2->value = "outfile2";
    

    // // for checking *wildcard
    // char *str_arr2[3];
    // str_arr2[0] = "infile2";
    // str_arr2[1] = "infile";
    // str_arr2[2] = NULL;
    // io_2->value = "inf*";

    // io_2->expanded_value = str_arr2;

    // io_2->fd_here_doc = -1;
    // io_2->type = IO_APPEND;



	shell.path = ft_lstnew("/usr/bin/");
	path_next = ft_lstnew("/usr/local/bin");
	path_next2 = ft_lstnew("/home/mosokina/.local/bin");
	ft_lstadd_back(&shell.path, path_next);
	ft_lstadd_back(&shell.path->next, path_next2);

	
    // // for checking no command(just redirections)
    // cmd.expanded_args = NULL;


    // char *expanded_args[3];
	// cmd.expanded_args = expanded_args;

	// // expanded_args[0] = "wrongcommand";
	// expanded_args[0] = "upset";
	// // expanded_args[0] = "wrongcmd";

	// // expanded_args[0] = "./test1";
	// expanded_args[1] = "VAR";
	// // expanded_args[1] = "invalidargs";
	// // expanded_args[1] = "./tests/test.o";
	// // expanded_args[1] = "./tests/test.c";

	// // expanded_args[2] = "arg";

	// expanded_args[2] = NULL;
    // // expanded_args[3] = NULL;
    

	shell.envp_arr = env;
	// printf("env %s\n", shell.envp_arr[0]);

    
	// shell.exit_code = ft_exec_simple_cmd(shell, &cmd);
	// printf("exit status %d\n", shell.exit_code);
    



	char *expanded_args1[4];
	cmd.expanded_args = expanded_args1;

	// expanded_args[0] = "wrongcommand";
	expanded_args1[0] = "export";
	// expanded_args[0] = "wrongcmd";

	// expanded_args[0] = "./test1";
	expanded_args1[1] = "VAR2=5";
	// expanded_args[1] = "invalidargs";
	// expanded_args[1] = "./tests/test.o";
	// expanded_args[1] = "./tests/test.c";

	expanded_args1[2] = "NEW_VAR3";

	expanded_args1[3] = NULL;
    // expanded_args[3] = NULL;


	shell.exit_code = ft_exec_simple_cmd(shell, &cmd);
	printf("exit status %d\n", shell.exit_code);
    printf("%s env\n", shell.envp_arr[3]);
	ft_lstclear(&shell.path, &del);
	return (0);
}
