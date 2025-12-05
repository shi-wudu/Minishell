#include "minishell.h"

extern volatile sig_atomic_t g_signal;

void    sigint_handler(int sig)
{
    (void)sig;
    g_signal = 130;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void    sigquit_handler(int sig)
{
    (void)sig;
    rl_on_new_line();      // bash: não faz nada no prompt
    rl_redisplay();
}

void    sigint_heredoc(int sig)
{
    (void)sig;
    g_signal = 130;
    write(1, "\n", 1);
    close(STDIN_FILENO);   // interrompe o readline do heredoc
}

void    setup_signals_interactive(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);
}

void    setup_signals_child(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

void    setup_signals_heredoc(void)
{
    signal(SIGINT, sigint_heredoc);
    signal(SIGQUIT, SIG_IGN);
}
