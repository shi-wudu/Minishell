#include "minishell.h"

extern volatile sig_atomic_t g_signal;

static int open_heredoc_file(char **tmp_file)
{
    int fd;

    *tmp_file = gen_heredoc_filename();
    fd = open(*tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("open");
        free(*tmp_file);
        return (-1);
    }
    return (fd);
}

char *read_heredoc(char *delimiter, bool expand, char **envp, int last_exit_status)
{
    char *tmp_file;
    char *line;
    int  fd;

    fd = open_heredoc_file(&tmp_file);
    if (fd == -1)
        return (NULL);
    setup_signals_heredoc();
    while (1)
    {
        line = readline("> ");
        if (g_signal == 130 || heredoc_should_stop(line, delimiter))
            break;
        write_heredoc_line(fd, line, envp, expand, last_exit_status);
        free(line);
    }
    close(fd);
    setup_signals_interactive();
    if (g_signal == 130)
        return (unlink(tmp_file), free(tmp_file), NULL);
    return (tmp_file);
}
