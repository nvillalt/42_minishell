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

// get_path.c
char	**get_path(char **env);

// handle_quotes.c
char	*clean_quotes(char *str);

// parser_nodes.c
int		init_process(t_parse **process);
int		init_redir(t_redir **node, int type);
int		add_redir(t_redir **redir_list, t_redir *new);
int		add_process(t_parse **process_list, t_parse *new);

// parse_utils.c
int		is_whitespace(char c);
int		check_quotes(char *line, t_utils *utils);
int		assert_quotes(char *input);
int		whitespace_cmp(char *c);
int		initial_pipe(char *input, t_utils *utils);

// handle_redirections.c
int		check_redirections(char *input);
int		handle_redirection(t_token **iterate, t_redir **redir_list, t_redir **redir_head);

// parse_tokens.c
int		parse_tokens(t_utils *utils);

#endif