/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:52:28 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/06 18:54:23 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

# define CMD 0
# define PIPE 1
# define GREAT 2
# define APPEND 3
# define HEREDOC 4
# define MINUS 5
# define BUILTIN 6

# define ECHO 1
# define PWD 2 
# define ENV 3 
# define UNSET 4 
# define CD 5 
# define EXIT 6 
# define EXPORT 7 

# define NOT_EXPAND 0
# define EXPAND 1

char	*clean_quotes(char *str);

int		init_process(t_parse **process);
int		init_redir(t_redir **node, int type);
int		add_redir(t_redir **redir_list, t_redir *new);
int		add_process(t_parse **process_list, t_parse *new);

int		check_quotes(char *line, t_utils *utils);
int		assert_quotes(char *input);
int		whitespace_cmp(char *c);
int		initial_pipe(char *input, t_utils *utils);

int		check_redirections(char *input);
int		handle_redirection(t_token **iterate,
			t_redir **redir_list, t_redir **redir_head);
int		syntax_error(char *input, t_utils *utils);

int		parse_tokens(t_utils *utils);

int		is_token(char c);
int		is_whitespace(char c);
int		count(char **arr);
int		validate_redir(char *s);

void	dup_matrix(char **ret, char **aux, int j, int k);
int		init_process_cmd(t_parse **node);
char	*init_quoteless_line(int num);

#endif
