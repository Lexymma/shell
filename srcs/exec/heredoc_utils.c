/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 21:30:26 by mosokina          #+#    #+#             */
/*   Updated: 2025/03/26 22:13:38 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	Function creates a name for the heredoc file. It will be a hidden file in the /temp
	folder. The static variable guarantees to have successive numbers.
 */

char	*ft_generate_heredoc_name(void)
{
	static int	i;
	char		*name;
	char		*number;

	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin(HEREDOC_NAME, number);
	free(number);
	i++;
	return (name);
}

/*
NOTE: 
- If the delimiter is quoted, the text in the here-document is taken literally,
w/o any expansions.
- If the delimiter is unquoted, the text in the here-document is subject to expansions.
*/

bool 	ft_is_delimiter_quoted(char *delimiter)
{
	while(*delimiter)
	{
		if (*delimiter == '"' || *delimiter == '\'')
			return (true);
		delimiter ++;
	}
	return (false);
}

/*
function for filling heredoc tmp file (line by line):
1 -  check delimiter for quotes;
Infinity Loop: 
1 - readline (>);
2 - check signal CTRL + D if true then break loop;
3 - check "is delimiter" if true then break loop;
4 - put heredoc line to heredoc tmp file;
5 - free line as readline uses malloc;
*/

void		ft_fill_heredoc(t_in_out *io_here, int fd_hd) 
{
	bool 	has_quoted;
	char 	*hd_line;
	int		line_nbr;

	line_nbr = 0;
	has_quoted = ft_is_delimiter_quoted(io_here->eof);
	//handle signals //QUIT SHOULD BE IGNORED in PARENT PROCESS!
	while(1)
	{
		hd_line = readline("> "); // MALLOC!!!!
		if (!hd_line) // note: it happends in case of signal CTRL + D
		{
			ft_putstr_fd("bash: warning: here-document at line ", STDERR_FILENO);
			ft_putnbr_fd(line_nbr, STDERR_FILENO);
			ft_putstr_fd(" delimited by end-of-file (wanted \'", STDERR_FILENO);
			ft_putstr_fd(io_here->eof, STDERR_FILENO);
			ft_putstr_fd("\')\n", STDERR_FILENO);
			free(hd_line);
			//PANIC()
			// break ;
			return ;
		}
		if (ft_is_delimiter(io_here->eof, hd_line) == true)
		{
			free(hd_line);
			//PANIC()
			return ;
			// break ;
		}
		ft_put_heredoc_line(hd_line, fd_hd, has_quoted);
		free(hd_line);
		line_nbr ++;
	}
}

char *ft_hd_line_expansion(char *hd_line)
{
	//to be done
	return (hd_line);
}


/* if delimiter is not quoted(has_quoted = false):
- lines are subject to expansion;
- \n is ignored;
- \ for quoting characters \, $ and ` // to be check!!!
if delimiter is quoted(has_quoted = true):
- the text in the here-document is taken literally,*/


void	ft_put_heredoc_line(char *hd_line, int fd_hd, bool quoted)
{
	if (quoted == false)
	{
		printf("Need to be no quotes rules\n");
		ft_heredoc_expander(hd_line, fd_hd);
	}
	else
		ft_putendl_fd(hd_line, fd_hd);
}

void	ft_heredoc_expander(char *hd_line, int fd_hd)
{
	int	i;

	i = 0;
	while (hd_line[i])
	{
		// if (hd_line[i] == '\')
		// 	i ++;
		// if next \ n $ or ' write 2d if not skip 1st??
		if (hd_line[i] == '$')
			// i += ft_heredoc_expand_writer(hd_line, i, fd_hd);
			i++;
		else
			i += (ft_putchar_fd(hd_line[i], fd_hd), 1);
	}
	ft_putchar_fd('\n', fd_hd);
}

// static int	ft_heredoc_expand_writer(char *str, size_t i, int fd)
// {
// 	size_t	start;
// 	char	*tmp;

// 	start = ++i;
// 	if (str[i] == '?')
// 		return (ft_putnbr_fd(g_minishell.exit_s, fd), 2);
// 	while (str[i] && str[i] != '$' && str[i] != ' ')
// 		i++;
// 	if (i != start)
// 	{
// 		tmp = ft_garbage_collector(ft_substr(str, start, i), false);
// 		tmp = ft_get_envlst_val(tmp);
// 		if (tmp)
// 			ft_putstr_fd(tmp, fd);
// 	}
// 	return (i);
// }

bool	ft_is_delimiter(char *delimiter, char *hd_line)
{
	while (*hd_line)
	{
		if (*delimiter == '"' || *delimiter == '\'')
		{
			delimiter++;
			continue ;
		}
		else if (*hd_line == *delimiter)
		{
			hd_line++;
			delimiter++;
		}
		else
			return (false);
	}
	while (*delimiter == '"' || *delimiter == '\'')
		delimiter++;
	if (!*delimiter)
		return (true);
	else
		return (false);
}
