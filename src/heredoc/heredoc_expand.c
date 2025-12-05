#include "minishell.h"

static char *expand_exit_code(char *res, int *i, int last)
{
    char *num;
    char *new;

    num = ft_itoa(last);
    new = ft_strjoin(res, num);
    free(num);
    free(res);
    *i += 2;
    return (new);
}

static char *expand_normal_var(const char *line, int *i, char **envp, char *res)
{
    int start = *i + 1;
    int j = start;
    char *name;
    char *val;
    char *new;

    while (line[j] && (ft_isalnum(line[j]) || line[j] == '_'))
        j++;
    if (j == start)
        return (append_char(res, line[(*i)++]));
    name = ft_substr(line, start, j - start);
    val = get_env_value(envp, name);
    new = ft_strjoin(res, val ? val : "");
    free(name);
    free(res);
    *i = j;
    return (new);
}

static char *handle_dollar_sign(const char *line, int *i, char **envp, char *res, int last)
{
    if (line[*i + 1] == '?')
        return (expand_exit_code(res, i, last));
    return (expand_normal_var(line, i, envp, res));
}

char *expand_vars_no_quotes(const char *line, char **envp,  int last_exit_status)
{
    int     i;
    char    *res;

    res = ft_strdup("");
    i = 0;
    while (line && line[i])
    {
        if (line[i] == '$')
            res = handle_dollar_sign(line, &i, envp, res, last_exit_status);
        else
        {
            res = append_char(res, line[i]);
            i++;
        }
    }
    return (res);
}
