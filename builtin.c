/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <bgenie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:03:40 by bgenie            #+#    #+#             */
/*   Updated: 2022/12/04 18:13:36 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void echo_print(char **args, int nl)
{
    int i;

    i = 0;
    while (args[i])
    {
        printf("%s", args[i++]);
        if (args[i])
            printf(" ");
    }
    if (!nl)
        printf("\n");
    
}

void    b_echo(t_cmd *cmd)
{
    int     i;
    int     j;
    int     nl;

    i = 0;
    nl = 0;
    while (cmd->argv[i])
    {
        if (cmd->argv[i][0] == '-')
        {
            j = 1;
            while (cmd->argv[i][j] == 'n')
                j++;
            if (cmd->argv[i][j] != 0)
                break ;
            if (j > 1)
                nl++;
        }
        else
            break ;
        i++;
    }
    echo_print(&cmd->argv[i], nl);
    g_exit_code = 0; 
}

void    b_exit(int n)
{
    exit((unsigned int)n);
}