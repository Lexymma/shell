#include "minishell.h"

t_list	*new_sublist(t_list *t_lst)
{
	int	balance;
	t_list	*new;
	t_token	*token;

	token = (t_token *)t_lst->content;
	new = NULL;
	balance = 1;
	t_lst = t_lst->next;
	if (t_lst)
		token = (t_token *)t_lst->content;
	while (t_lst && balance != 0)
	{
		if (t_lst)
		{
			token = (t_token *)t_lst->content;
			if (token->type == PARENTHESIS && *token->value == ')')
				balance--;
			if (token->type == PARENTHESIS && *token->value == '(')
				balance++;
		}
		if (balance != 0)
			ft_lstadd_back(&new, ft_lstnew(token));
		t_lst = t_lst->next;
	}
	return (new);
}

bool	is_parenthesis(t_list *t_lst)
{
	if (t_lst)
		return (((t_token *)t_lst->content)->type == PARENTHESIS);
	return (NULL);
}

void	clean_sublist(t_list *new)
{
	t_list	*tmp;

	tmp = new;
	while (new)
	{
		tmp = new->next;
		free(new);
		new = tmp;
	}
}

void	*get_andif_subnode(t_shell *shell, void *l_node, t_list *t_lst)
{
	t_list *new;

	new = NULL;
	new = new_sublist(t_lst->next);
	l_node = create_and(shell, l_node, build_ltree(shell, new));
	clean_sublist(new);
	return (l_node);
}

void	*get_or_subnode(t_shell *shell, void *l_node, t_list *t_lst)
{
	t_list	*new;

	new = NULL;
	new = new_sublist(t_lst->next);
	l_node = create_or(shell, l_node, build_ltree(shell, new));
	clean_sublist(new);
	return (l_node);
}
