#include "minishell.h"

static void write_heredoc_line_expanded(int fd, char *line, char **envp, int last)
{
    char *out;

    out = expand_vars_no_quotes(line, envp, last);
    write(fd, out, ft_strlen(out));
    write(fd, "\n", 1);
    free(out);
}

static void write_heredoc_line_noexp(int fd, char *line)
{
    write(fd, line, ft_strlen(line));
    write(fd, "\n", 1);
}

void write_heredoc_line(int fd, char *line, char **envp, bool expand, int last)
{
    if (expand)
        write_heredoc_line_expanded(fd, line, envp, last);
    else
        write_heredoc_line_noexp(fd, line);
}