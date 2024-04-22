#ifndef EXECUTOR_H
# define EXECUTOR_H
void	dirty_parse(char *input, t_utils *utils);
int		executor(t_utils *utils);
char	*get_cmd_path(t_utils *utils);
#endif