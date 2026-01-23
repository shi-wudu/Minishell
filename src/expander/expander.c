/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:25 by seilkiv           #+#    #+#             */
/*   Updated: 2026/01/20 21:56:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_ifs(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

static char *expand_vars(const char *s, t_data *data)
{
    int i = 0;
    char *res = ft_strdup("");

    while (s[i])
    {
        if (s[i] == '$' && s[i + 1] == '{')
        {
            handle_this(s, &i, &res, data);
            continue;
        }
         if (s[i] == '$' && s[i + 1] == '$')
        {
            char *pid = ft_itoa(getpid());
            res = ft_strjoin_free(res, pid);
            free(pid);
            i += 2;
            continue;
        }
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

static char **split_ifs(const char *s)
{
    char **res = NULL;
    int i = 0, start;

    while (s[i])
    {
        while (s[i] && is_ifs(s[i]))
            i++;
        if (!s[i])
            break;
        start = i;
        while (s[i] && !is_ifs(s[i]))
            i++;
        res = append_str_array(res, ft_substr(s, start, i - start));
    }
    return (res);
}

char **expand_word_token(t_token *tok, t_data *data)
{
    t_segment   *seg;
    t_seg_type  prev_type;
    char        **result;
    char        *current;

    result = NULL;
    current = ft_strdup("");
    prev_type = UNQUOTED;   // assume início como unquoted

    seg = tok->segments;
    while (seg)
    {
        if (seg->type == SINGLE_QUOTED)
        {
            current = ft_strjoin_free(current, seg->value);
        }
        else
        {
            char *expanded = expand_vars(seg->value, data);

            if (seg->type == UNQUOTED)
            {
                char **split = split_ifs(expanded);
                int i = 0;

                if (split && split[0])
                {
                    // 🔴 REGRA CRÍTICA
                    if (prev_type != UNQUOTED)
                    {
                        result = append_str_array(result, current);
                        current = ft_strdup(split[i++]);
                    }
                    else
                        current = ft_strjoin_free(current, split[i++]);

                    while (split[i])
                    {
                        result = append_str_array(result, current);
                        current = ft_strdup(split[i++]);
                    }
                }
                free_args(split);
            }
            else
                current = ft_strjoin_free(current, expanded);
            free(expanded);
        }
        prev_type = seg->type;
        seg = seg->next;
    }
    result = append_str_array(result, current);
    return (result);
}


void expand_tokens(t_token *tokens, t_data *data)
{
    while (tokens)
    {
        if (tokens->type == WORD)
            tokens->expanded = expand_word_token(tokens, data);
        tokens = tokens->next;
    }
}
