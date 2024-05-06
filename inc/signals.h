#ifndef SIGNALS_H
# define SIGNALS_H
typedef struct sigaction t_sigaction;
void	set_child_signals(void);
void	ignore_signals(void);
void	set_signals(void);
#endif