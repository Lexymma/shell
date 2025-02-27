/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosokina <mosokina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 23:38:14 by mosokina          #+#    #+#             */
/*   Updated: 2025/02/26 23:49:07 by mosokina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../structs.h"

int builtin_unset(t_shell shell, t_node *cmd)
{
    printf("builtin: %s\n", cmd->expanded_args[0]);
    return (ENO_SUCCESS);
}

