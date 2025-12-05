#include "minishell.h"

char *gen_heredoc_filename(void)
{
    static int  i = 0;
    char        *nbr = ft_itoa(i++);
    char        *name = ft_strjoin("/tmp/minishell_heredoc_", nbr);
    free(nbr);
    return name;
}

bool heredoc_should_stop(char *line, char *delimiter)
{
    if (!line)
        return (true);
    if (ft_strcmp(line, delimiter) == 0)
        return (true);
    return (false);
}
