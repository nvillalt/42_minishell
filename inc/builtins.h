#ifndef BUILTINS_H
# define BUILTINS_H

# define QUOTES_ERR "minishell: export: `': not a valid identifier"
# define CD_ERR "cd: error retrieving current directory: "
# define CWD_ERR "getcwd: cannot access parent directories: "
# define FILE_ERR "No such file or directory"

int		ft_echo(char **str);
int		ft_pwd(char **env);
int		ft_env(char **env, char **argv);
int		ft_unset(t_utils *utils, char **cmd);
int		ft_cd(t_utils *utils, char **cmd);
void	ft_exit(char **cmd, t_utils *utils);
int		ft_export(t_utils *utils, char **cmd);
char	**change_old_pwd(char **env);
char	**change_pwd(char **env);
char    **export_to_env(char **env, char **cmd, int *error_flag);
int		is_export_format(char *cmd);
char	**unset_var_env(char **env, int index_jump);
char	**change_var(char **env, char *cmd);
char	**add_to_env(char **env, char *cmd);
int		cmd_on_env(char **env, char *cmd);
void	exit_process_custom(t_utils *utils, unsigned char status);
int		env_varlen(char *str);
char	*ft_getenv(char **env, char *var);
char	**change_pwd_error(char **env, char *cmd);
int		get_env_index(char **env, char *var);
char	**free_str_matrix_cderror(char *str, char **matrix, char *perror_msg);
int		multiple_argc_error(char **env);
char	**handle_newvar(char **env, char **cmd, int i, int setvar);
char	**create_new_env(char **env, char *cmd);
int		get_cmd_flag(char **env, char *cmd, int cmd_len, int plus_flag);
void	print_no_value(char **env, int *i, int *j);
char	**join_var(char **env, char *cmd);
char	*delete_plus(char *cmd);
#endif