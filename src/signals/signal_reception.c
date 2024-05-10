#include "../../minishell.h"

static void	child_sigquit(void)
{
	t_sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &sa, NULL);
}

static void	child_sigint(void)
{
	t_sigaction	sa;

	sa.sa_handler = SIG_DFL; //Puntero a función
	sigaction(SIGINT, &sa, NULL);
}

static void	ignore_sigquit(void)
{
	t_sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

static void	ignore_sigint(void)
{
	t_sigaction	sa;

	sa.sa_handler = SIG_IGN; //Puntero a función
	sigaction(SIGINT, &sa, NULL);
}

static void	exec_sigint(int signal)
{
	write(STDERR_FILENO, "\n", 1);
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	parent_sigint(void)
{
	t_sigaction	sa;

	sa.sa_handler = exec_sigint; //Puntero a función
	sigaction(SIGINT, &sa, NULL);
}

void	set_signals(void)
{
	parent_sigint();
	ignore_sigquit();
}

void	ignore_signals(void)
{
	ignore_sigint();
	ignore_sigquit();
}

void	set_child_signals(void)
{
	child_sigint();
	child_sigquit();
}