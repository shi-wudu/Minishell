#include "minishell.h"

char *expand_heredoc_line(const char *s, t_data *data)
{
    int i = 0;
    char *res = ft_strdup("");

    while (s[i])
    {
        if (s[i] == '$' && s[i + 1] == '?')
        {
            char *num = ft_itoa(data->last_exit_status);
            res = ft_strjoin_free(res, num);
            free(num);
            i += 2;
        }
        else if (s[i] == '$' && (ft_isalnum(s[i + 1]) || s[i + 1] == '_'))
        {
            int start = ++i;
            while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
                i++;
            char *name = ft_substr(s, start, i - start);
            char *val = get_env_value(data->envp, name);
            res = ft_strjoin_free(res, val ? val : "");
            free(name);
        }
        else
            res = append_char(res, s[i++]);
    }
    return (res);
}
