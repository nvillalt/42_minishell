#ifndef EXECUTOR_H
# define EXECUTOR_H

# define FUNC_FAILURE 0
# define FUNC_SUCCESS 1

void			dirty_parse(char *input, t_utils *utils);
int				executor(t_utils *utils, t_parse *process);
char			*get_cmd_path(t_utils *utils, t_parse *process);
int				create_multiple_heredocs(t_utils *utils, t_parse *process);
void			close_fds(t_parse *process, t_utils *utils);
int				execute_childs(t_utils *utils, t_parse *process);
void			free_to_prompt(t_utils *utils);
void			free_to_prompt_error(t_utils *utils);
void			exit_process(t_utils *utils);
void			unlink_files(t_parse *process);
void			exit_process_noerror(t_utils *utils);
void			close_pipe_fd(int *pipe_fd);
void			close_all_pipes(t_utils *utils);
int				redirec_infile(t_utils *utils, t_parse *process);
int				redirec_outfile(t_utils *utils, t_parse *process);
int				create_first_child(t_utils *utils, t_parse *process, int process_index);
void			exec_cmd(t_utils *utils, t_parse *current_process);
int				create_last_child(t_utils *utils, t_parse *process, int process_index);
int				create_mid_child(t_utils *utils, t_parse *process, int process_index);
int				exec_builtins(t_utils *utils, t_parse *process, int process_index);
unsigned char	handle_builtins(t_utils *utils, t_parse *process);
#endif