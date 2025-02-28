/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:40:25 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/28 10:38:06 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include "libft/libft.h"
#include <limits.h>
#include <stdbool.h>

#include <stdio.h>  // for readline()
#include <readline/readline.h> // for readline()
#include <readline/history.h> // for readline()
#include <unistd.h> //functions access(), pipe(), fork(), getpcwd(). chdir()
#include <stdlib.h> // exit ()
#include <wait.h> // for MACROS WIFSIGNALED, WTERMSIG, and WEXITSTATUS 
#include <string.h> // for strerror()
#include <sys/stat.h> // for stat() and stat structure
#include <sys/types.h> // for MACRO S_ISDIR for t_pid
#include <fcntl.h> // for open()

/*May require a pointer to cwd and old working dir*/
typedef struct s_shell
{
	t_list *envp;        // Stores environment variables as a linked list.
	char **envp_arr;     // Stores environ variables as an array for execve().
	t_list *path;        // Stores directories from $PATH in a linked list.
	t_list *token_lst;   // Stores parsed command tokens for execution.
	char *input;         // Stores the raw command input from the user.
	char *trimmed_input; // Stores trimmed input (no leading/trailing spaces).
	void *root;          // Root of an AST (Abstract Syntax Tree) for parsing
	char *cmd_path;      // Stores the full executable path for a command.
	//MO: why we need it?

	char *cwd;           // Current working directory
	int exit_code;       // Stores the exit code of the last command 
	//MO: CHANGE NAME TO EXIT_STATUS?
	
	int fd;              // Stores the file descriptor used for redirections.
}				t_shell;

typedef struct s_env
{
	char		*value; //Value
	char		*key; //Key
	bool		is_export;
	bool		is_printed;
}				t_env;

// /*Command structs and typedefs*/
// typedef enum e_node_type
// {
// 	N_PIPE,
// 	N_EXEC,
// 	N_ANDIF,
// 	N_OR,
// }				t_node_type;

// typedef struct s_node
// {
// 	t_node_type	type;
// }				t_node;

// typedef struct s_exec
// {
// 	t_node		type;
// 	char		*command;
// 	char		**av;
// 	t_list		*infiles;
// 	t_list		*outfiles;
// }				t_exec;

//MO: SUGGESTIONS TO HEADER

typedef enum e_node_type
{
	N_PIPE,
	N_AND,
	N_OR,
	N_CMD
}	t_node_type;

typedef enum e_io_type
{
	IO_IN,
	IO_OUT,
	IO_HEREDOC,
	IO_APPEND
}	t_io_type;


typedef struct s_io
{
	t_io_type			type;
	char				*value;
	char				**expanded_value;
	int					fd_here_doc;
}	t_io;


typedef struct s_node
{
	t_node_type			type;
	t_list				*io_list; // t_list list.content should be t_io(io);
	char				*args;
	char				**expanded_args;
	struct s_node		*left;
	struct s_node		*right;
}	t_node;

typedef enum e_err_msg
{
	ERRMSG_CMD_NOT_FOUND,
	ERRMSG_NO_SUCH_FILE,
	ERRMSG_PERM_DENIED,
	ERRMSG_AMBIGUOUS,
	ERRMSG_TOO_MANY_ARGS,
	ERRMSG_NUMERIC_REQUI
}	t_err_msg;


//return is exit status
// 0: Success
// 1: General error
// 2: Misuse of shell builtins !!!
// 126: Command invoked cannot execute
// 127: Command not found
// 128: Invalid argument to exit !!!
// Exit status 130: Script terminated by Control-C !!!

typedef enum e_err_no
{
	ENO_SUCCESS, //0
	ENO_GENERAL, //1
	// ENO_MISUSE_BUILTIN; //2
	ENO_CANT_EXEC = 126,
	ENO_NOT_FOUND, //127
	ENO_EXEC_255 = 255
}	t_err_no;

//redirections

int		redirection(t_node *cmd);
int		ft_in(t_io	*io);
int		ft_out(t_io	*io);
int		ft_append(t_io	*io);

//execution of simple command
int		ft_exec_simple_cmd(t_shell shell, t_node *cmd);


//(3) execution of child command

int			ft_exec_child(t_shell shell, t_node *cmd);
int			ft_get_exit_status(int status);
t_err_no	ft_check_access(char *file);
bool		cmd_is_dir(char *cmd);

char		*ft_get_env_path(t_shell shell, char *cmd_name, t_err_no *err_no);


//(2) execution of builtins
bool 		ft_is_builtin(char *cmd);
int			ft_exec_builtin(t_shell shell, t_node *cmd);
int			builtin_echo(t_shell shell, t_node *cmd);
int			builtin_cd(t_shell shell, t_node *cmd);
int			builtin_export(t_shell shell, t_node *cmd);
int			builtin_unset(t_shell shell, t_node *cmd);
int			builtin_pwd(t_shell shell, t_node *cmd);
int			builtin_env(t_shell shell, t_node *cmd);
void		builtin_exit(t_shell shell, t_node *cmd);

void		ft_update_env_value(t_list *envp, char *key, char *new_value);
char 		*ft_get_env_value(t_list *envp, const char *key);


//utils
void		ft_err_msg(char *s1, char *s2, char *s3);
int			ft_strcmp(const char *s1, const char *s2);


#endif