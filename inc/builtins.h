#ifndef BUILTINS_H
# define BUILTINS_H

void	ft_echo(char **str);
void	ft_pwd(void);
void	ft_env(char **env, char **argv);
char	**ft_unset(char **env, char **var);
char	**ft_cd(char **env, char **cmd);
void	ft_exit(char **cmd);
char	**ft_export(char **env, char **cmd);
char    **export_to_env(char **env, char **cmd);
char	**change_to_directory(char **env, char *cmd);
char	**change_pwd(char **env);
int		is_string_alpha(char *cmd);
char	**unset_var_env(char **env, int index_jump);
char	**change_var(char **env, char *cmd);
char	**add_to_env(char **env, char *cmd);
int		cmd_on_env(char **env, char *cmd);

#endif