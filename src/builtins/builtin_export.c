/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:29:20 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/05 13:08:50 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structs.h"

/*

1 - NOTE: Options are not in the Minishell Subject!
2 - if just cmd without argos, print list shell.envp with msg “declare -x”
If only key without value??

3 - Loop argos:
a- Check is key value valid. It should start with the letter or ‘_’, followed by letters, numbers, or ‘_’.Plus ‘=’ exists
b - If key is not valid, error msg “not a valid identifier” with exit code 1.
c - If key is valid
	- If  ‘=’ doesn’t exists do nothing with exit code 0;
	- If key in env then update env value;and “=” replace or “+=” append;
	- else - add new env (in the end?? Or //alphabetic  order???)
*/




int ft_put_export_envp(t_shell shell, t_node *cmd)
{
	
	t_list	*current;
	t_env	*env_entry;
	(void)cmd;

	//check NULL? error???
	current = shell.envp;
	while (current)
	{
		env_entry = (t_env *)current->content;
		// if (env_entry->value != NULL) //if only key doesn't it print?
		printf("declare -x %s=\"", env_entry->key);
		//add
		current = current->next;
	}
	return (ENO_SUCCESS);
}

bool	ft_is_env_key_valid(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(*str) && *str != '_')
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (1);
}

static char	*ft_extract_key(char *export_arg) //check no malloc!!
{
	int	i;

	i = 0;
	while (export_arg[i])
	{
		if (export_arg[i] == '=')
			return (ft_substr(export_arg, 0, i)); //no malloc
		i++;
	}
	return (export_arg);
}

static char	*ft_extract_value(char *export_arg) //check no malloc!!
{
	int	i;

	i = 0;
	while (export_arg[i])
	{
		if (export_arg[i] == '=')
			if (export_arg[i + 1])
			return (&(export_arg[i + 1])); //no malloc //check quotes(is it parsing part)
		i++;
	}
	return (NULL); //check is it NULL or empty str with "\0"??
}

bool	ft_is_key_in_env(t_list *envp, char *key)
{
	t_list	*current_list;
	t_env	*env_content;

	current_list = envp;
	while (current_list)
	{
		env_content = (t_env *)current_list->content;
		if (!ft_strcmp(env_content->key, key))
			return (true);
        current_list = current_list->next;
	}
	return (false);
}

t_env	*new_env_content(char *key, char *value)
{
	t_env	*env_content;

	env_content = malloc(sizeof(t_env));
	if (!env_content)
		return (NULL);
	env_content->value = ft_strdup(value);
	env_content->key = ft_strdup(key);
	return (env_content);
}

int	builtin_export(t_shell shell, t_node *cmd)
{
	int exit_code;
	char **export_args;
	int i;
	char *key;
	
	exit_code = ENO_SUCCESS;
	export_args = &(cmd->expanded_args[1]);
	i = 0;

	if (!export_args[0])
	{
		ft_put_export_envp(shell, cmd);
		return (ENO_SUCCESS);
	}
	while (export_args[i])
	{
		if (ft_is_env_key_valid(export_args[i]) == false)
		{
			exit_code = ENO_GENERAL;
			ft_err_msg("exit", export_args[i], "not a valid identifier\n");
		}
		else if 	(!ft_strchr(export_args[i], '='))
			break ;		//check, should be ""="
		else
		{

			key = ft_extract_key(export_args[i]); //no malloc! check!
			if (ft_is_key_in_env(shell.envp, key) == true)
				ft_update_env_value(shell.envp, key, ft_extract_value(export_args[i])); //append +=??
			else
				ft_add_envlist(shell.envp, key, ft_extract_value(export_args[i]));
		}
		i ++;
	}
	return (exit_code);
}

