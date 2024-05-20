#include "../../minishell.h"

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
static void	heredoc_sigint(int signal)
{
	g_sigint = 1;
	ioctl(0, TIOCSTI, "\n");
}

void	set_signals(void)
{
	signal(SIGINT, exec_sigint);
	signal(SIGQUIT, SIG_IGN);
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
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}