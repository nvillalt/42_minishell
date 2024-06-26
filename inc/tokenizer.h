/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:31:21 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/06 18:54:31 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# define TOKEN_ERR 1
# define TOKEN_OK 2

# define YES 1
# define NO 0

int		new_token(t_token **new);
int		add_token(t_token **list, t_token *new);
int		clear_token_list(t_token **token_list, int n, t_utils *utils);
int		free_tokens(t_token **token_list, char *temp, int n, t_utils *utils);
char	*trim_spaces(char *input);
int		get_tokens(char	*aux, t_utils *utils);

#endif