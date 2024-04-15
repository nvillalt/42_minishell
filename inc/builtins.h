#ifndef BUILTINS_H
# define BUILTINS_H

void	ft_echo(char **str);
void	ft_pwd(void);
void	ft_env(char **env, char **argv);
char	**ft_unset(char **env, char **var); //Habrá que pasar el env por referencia y hacer que devuelva un status
char	**ft_cd(char **env, char **cmd); //Habrá que pasar el env por referencia y hacer que devuelva un status
void	ft_exit(char **cmd);
int     ft_export(char **env, char **cmd);
#endif