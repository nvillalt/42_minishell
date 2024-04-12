#ifndef BUILTINS_H
# define BUILTINS_H

void	ft_echo(char **str);
void	ft_pwd(void);
void	ft_env(char **env, char **argv);
char	**ft_unset(char **env, char **var);
char	**ft_cd(char **env, char **cmd);
#endif
