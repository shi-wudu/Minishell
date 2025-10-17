#include "../../include/minishell.h"

void	errmsg(const char *msg, const char *arg, bool newline)
{
	write(2, msg, strlen(msg));
	if (arg)
	{
		write(2, ": ", 2);
		write(2, arg, strlen(arg));
	}
	if (newline)
		write(2, "\n", 1);
}
