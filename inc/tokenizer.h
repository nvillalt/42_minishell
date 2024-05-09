/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:31:21 by nvillalt          #+#    #+#             */
/*   Updated: 2024/05/09 20:11:24 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

// token_list.c
int		new_token(t_token **new);
int		add_token(t_token **list, t_token *new);
int		clear_token_list(t_token **token_list);
int		free_tokens(t_token **token_list, char *temp, int n);

// token_generator.c
char	*trim_spaces(char *input);
int		get_tokens(char	*aux, t_utils *utils);

#endif