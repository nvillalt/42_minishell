#include "../../minishell.h"
#ifndef MALLOC_FAIL
# define MALLOC_FAIL 0
#endif

void	*malloc(size_t n)
{
	static int cnt = 0;

	if (cnt == MALLOC_FAIL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	cnt++;
	return (calloc(n, 1));
}