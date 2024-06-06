/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:23:04 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/06 16:15:24 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSOR_H
# define EXPANSOR_H

# include "structs.h"

typedef struct s_expand
{
	int		status;
	char	**env;
	char	*str;
}	t_exp;

// expansor.c
int		expansor(t_utils *utils);

// expansor_builder.c
int		not_exp(char *s, char **ret, int i);
int		expand_dollar(char *s, t_exp *exp_utils, char **ret, int i);
int		handle_sgl_quote(char *s, char **ret, int i);
int		expand_dbl_quote(char *s, t_exp *exp_utils, char **ret, int i);
int		handle_printing_dollar(t_exp *exp_utils, int i, char **s, int flag);

// builder_utils.c
void	join_aux_to_tmp(char **tmp, char *aux);
int		process_non_dollar(char *str, int i, int j, char **aux);
int		process_dollar(char *str, int j, char **aux, t_exp *exp_utils);

// expanding_env.c
int		get_end(char *str, int i, char **s1, t_exp *exp_utils);
int		get_beginning(char *str, int i, char **s1);
int		get_mid(char *str, int i, char **s2, t_exp *exp_utils);
char	*expand_env(char *var, char **env);
char	*var_expanded(char *str, t_exp *exp_utils);

// expansor_utils.c
t_exp	*init_exp(t_utils *utils);
char	*ft_strjoin_expand(char *s1, char *s2);
int		check_dollar(char *str);
int		check_valid_redir(char *s1, t_token *tmp, t_utils *utils);
int		free_expansor(t_token **token_list, t_exp *exp_utils, t_utils *utils);

#endif