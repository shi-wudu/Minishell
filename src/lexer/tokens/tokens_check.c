#include "../../../include/minishell.h"

bool	has_syntax_error(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->type == PIPE && tmp->next && tmp->next->type == PIPE)
		{
			errmsg("syntax error near unexpected token", "|", true);
			return (true);
		}
		if (tmp->type >= INPUT
			&& tmp->next && tmp->next->type >= INPUT)
		{
			errmsg("syntax error near unexpected token", tmp->next->value, true);
			return (true);
		}
		//pipe inicio ou fim
		//redirec sem ficheiro
		//pipi + redirect
		//redirect + string
		tmp = tmp->next;
	}
	return (false);
}
