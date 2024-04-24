#ifndef EXECUTOR_H
# define EXECUTOR_H
void	dirty_parse(char *input, t_utils *utils);
void	executor(t_utils *utils);
char	*get_cmd_path(t_utils *utils);
void	open_multiple_heredocs(t_utils *utils, t_parse *process);
void	close_fds(t_parse *process, t_utils *utils);
void	execute_first_process(t_utils *utils, t_parse *process);
void	close_unlink_fds(t_parse *process, t_utils *utils);
#endif