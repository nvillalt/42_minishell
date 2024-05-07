#include "../../minishell.h"

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

void	set_signals(void)
{
	signal(SIGINT, exec_sigint);
	signal(SIGQUIT, SIG_DFL);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	heredoc_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}