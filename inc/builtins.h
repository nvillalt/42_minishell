#ifndef BUILTINS_H
# define BUILTINS_H

int		ft_echo(char **str);
int		ft_pwd(char **env);
int		ft_env(char **env, char **argv);
int		ft_unset(t_utils *utils, char **cmd);
int		ft_cd(t_utils *utils, char **cmd);
void	ft_exit(char **cmd, t_utils *utils);
int		ft_export(t_utils *utils, char **cmd);
char	**change_old_pwd(char **env);
char	**change_pwd(char **env);
char    **export_to_env(char **env, char **cmd);
int		is_string_alpha(char *cmd);
char	**unset_var_env(char **env, int index_jump);
char	**change_var(char **env, char *cmd);
char	**add_to_env(char **env, char *cmd);
int		cmd_on_env(char **env, char *cmd);
void	exit_process_custom(t_utils *utils, unsigned char status);
int		env_varlen(char *str);
char	*ft_getenv(char **env, char *var);
char	**change_pwd_error(char **env, char *cmd);
#endif