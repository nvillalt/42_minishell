/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:04:54 by nvillalt          #+#    #+#             */
/*   Updated: 2024/05/28 15:25:24 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "structs.h"

typedef struct s_expand
{
	int		status;
	char	**env;
}	t_expand;

// expansor.c
int		expansor(t_utils *utils);

// expansor_builder.c
int		get_end(char *str, int i, char **s1, t_expand *exp_utils);
int		get_beginning(char *str, int i, char **s1);
int		get_mid(char *str, int i, char **s2, t_expand *exp_utils);
char	*expand_env(char *var, char **env);
char	*var_expanded(char *str, t_expand *exp_utils);

// expansor_utils.c
t_expand	*init_exp(t_utils *utils);
char		*ft_strjoin_expand(char *s1, char *s2);


# endif