/*#include "../../minishell.h"

static void	exec_sigint(int signal)
{
	printf("SIGINT\n");
}

static void	exec_sigquit(int signal)
{
	printf("SIGQUIT\n");
}

static void	get_sigint(void)
{
	t_sigaction	sa;

	sa.sa_handler = exec_sigint; //Puntero a función
	sigaction(SIGINT, &sa, NULL);
}

static void	get_sigquit(void)
{
	t_sigaction	sa;

	sa.sa_handler = exec_sigquit; //Puntero a función
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void	handle_signals(void)
{
	get_sigint();
	get_sigquit();
}
*/