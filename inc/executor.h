#ifndef EXECUTOR_H
# define EXECUTOR_H
# define FUNC_FAILURE 0
# define FUNC_SUCCESS 1
void	dirty_parse(char *input, t_utils *utils);
int		executor(t_utils *utils);
char	*get_cmd_path(t_utils *utils);
int		create_multiple_heredocs(t_utils *utils, t_parse *process);
void	close_fds(t_parse *process, t_utils *utils);
void	execute_first_process(t_utils *utils, t_parse *process);
int		execute_childs(t_utils *utils, int process_list_len);
void	free_to_prompt(t_utils *utils);
void	exit_process(t_utils *utils);
void	unlink_files(t_parse *process);
#endif