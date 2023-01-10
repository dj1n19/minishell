#include "../Includes/minishell.h"

void    search_tokens(void)
{
    int     quotes_count;
    int     dquotes_count;
    char    **save1;
    char    *save2;

    save1 = g_cmd->argv;
    while (*g_cmd->argv)
    {
        save2 = *g_cmd->argv;
        dquotes_count = 0;
        quotes_count = 0;
        while (**g_cmd->argv)
        {
            if (**g_cmd->argv == '|')
                g_cmd->tokens |= PIPE;
            if (**g_cmd->argv == '<' || **g_cmd->argv == '>')
                g_cmd->tokens |= REDIR;
            if (**g_cmd->argv == '"')
                dquotes_count++;
            if (**g_cmd->argv == '\'')
                quotes_count++;
            (*g_cmd->argv)++;
        }
        if (quotes_count && quotes_count % 2 == 0)
            g_cmd->tokens |= QUOTES;
        if (dquotes_count && dquotes_count % 2 == 0)
            g_cmd->tokens |= DQUOTES;
        *g_cmd->argv = save2;
        g_cmd->argv++;
    }
    g_cmd->argv = save1;
}