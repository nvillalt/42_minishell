/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:52:27 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/06 17:20:47 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define EOFERR "warning: here-document delimited by end-of-file (wanted `eof')"
# define FUNC_FAILURE 0
# define FUNC_SUCCESS 1

int				executor(t_utils *utils, t_parse *process);
char			*get_cmd_path(t_utils *utils, t_parse *process);
int				create_multiple_heredocs(t_utils *utils, t_parse *process);
void			close_fds(t_parse *process);
int				execute_childs(t_utils *utils, t_parse *process);
void			free_to_prompt(t_utils *utils);
void			exit_process(t_utils *utils);
void			unlink_files(t_parse *process);
void			exit_process_noerror(t_utils *utils);
void			close_redir_fd(int *pipe_fd);
void			close_all_redirs(t_utils *utils);
int				create_first_child(t_utils *utils, t_parse *p, int process_i);
void			exec_cmd(t_utils *utils, t_parse *current_process);
int				create_last_child(t_utils *utils, t_parse *p, int process_i);
int				create_mid_child(t_utils *utils, t_parse *p, int process_i);
int				exec_builtins(t_utils *utils, t_parse *p, int process_i);
unsigned char	handle_builtins(t_utils *utils, t_parse *p);
int				control_eof_hd(t_parse *p, t_utils *utils);
int				control_sigint_hd(char *buffer, t_utils *utils);
void			init_values_hd(char **buff, int *limit, int *buf, t_parse *p);
char			*init_buffer(char *buffer);
char			*append_newline(int *buffer_len, char *buffer, t_utils *utils);
int				ft_strncmp_heredoc(const char *s1, const char *s2, size_t n);
char			*ft_strjoin_hd(char const *s1, char const *s2);
int				open_here_doc(t_redir *redirec, int *temp_num);
char			*check_expansor_hd(t_parse *p, char *buf, t_utils *utils);
char			*get_keyhd(char *buffer, int i, t_utils *utils);
char			*create_new_buffer(char *buffer, char *val, char *key, int *i);
void			open_files(t_utils *ut, t_parse *p, int *lastin, int *lastout);
int				redirec_infile(int last_infile, t_utils *utils);
int				redirec_outfile(int last_outfile, t_utils *utils);
void			open_outfiles(t_parse *p, t_utils *utils, int *last_outfile);
void			open_infiles(t_parse *p, t_utils *utils, int *last_infile);
void			init_parent_builtin(t_utils *ut, int *lastin, int *lastout);

#endif