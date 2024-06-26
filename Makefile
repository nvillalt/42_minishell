# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 18:59:09 by nvillalt          #+#    #+#              #
#    Updated: 2024/06/06 19:00:24 by nvillalt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = ./libft/libft.a

LIBFTDIR = ./libft

CC = cc

LM = make -C

CFLAGS = -Wall -Wextra -Werror

RLIB = -lreadline

INCLUDES = minishell.h inc/builtins.h inc/executor.h inc/parser.h inc/signals.h inc/structs.h inc/tokenizer.h inc/expansor.h

RM = rm -f

BUILT_INS = src/builtins/ft_echo.c \
						src/builtins/ft_pwd.c \
						src/builtins/ft_env.c \
						src/builtins/ft_unset.c \
						src/builtins/ft_cd.c \
						src/builtins/ft_exit.c \
						src/builtins/ft_export.c \
						src/builtins/export_to_env.c \
						src/builtins/change_pwd.c \
						src/builtins/export_utils.c \
						src/builtins/export_utils2.c \
						src/builtins/unset_var_env.c \
						src/builtins/cd_utils.c \
						src/builtins/cd_utils2.c 

EXECUTOR = src/executor/executor.c \
					src/executor/get_cmd_path.c \
					src/executor/heredocs.c \
					src/executor/close_fds.c \
					src/executor/executor_frees.c \
					src/executor/execute_first_process.c \
					src/executor/childs.c \
					src/executor/exec_cmd.c \
					src/executor/execute_last_process.c \
					src/executor/execute_mid_process.c \
					src/executor/exec_builtins.c \
					src/executor/heredoc_utils.c \
					src/executor/heredoc_utils_2.c \
					src/executor/open_heredoc.c \
					src/executor/expand_heredoc.c \
					src/executor/create_buffer_heredoc.c \
					src/executor/open_files.c \
					src/executor/redir_files.c \
					src/executor/open_infiles.c \
					src/executor/open_outfiles.c \
					src/executor/init_parent_builtin.c 

TOKENIZER =	src/tokenizer/token_generator.c \
			src/tokenizer/token_list.c 

PARSER = src/parser/parse_utils.c \
			src/parser/parse_tokens.c \
			src/parser/handle_quotes.c \
			src/parser/handle_redirections.c \
			src/parser/parser_nodes.c \
			src/parser/checker_functions.c \
			src/parser/assignment_functions.c

SIGNAL = src/signals/signal_reception.c \
			src/signals/heredoc_signal.c \
			src/signals/sigint_signal.c

EXPAND = src/expansor/expansor.c \
			src/expansor/expansor_builder.c \
			src/expansor/expansor_utils.c \
			src/expansor/expanding_env.c \
			src/expansor/builder_utils.c

GENERAL = src/general/main.c \
			src/general/free_utils.c \
			src/general/general_utils.c \
			src/general/ft_puterror.c \
			src/general/exit_utils.c \
			src/general/set_oldpwd.c \
			src/general/update_shlvl.c \
			src/general/free_strings.c \
			src/general/init_shell.c 

MALLOC_DEBUG = src/debug/malloc_debug.c

OBJS = ${BUILT_INS:.c=.o} ${EXECUTOR:.c=.o} ${TOKENIZER:.c=.o} ${GENERAL:.c=.o} ${PARSER:.c=.o} ${SIGNAL:.c=.o} ${EXPAND:.c=.o}
OBJ.DEBUG = $(MALLOC_DEBUG:.c=.o)

$(NAME): $(OBJS) $(INCLUDES)
		$(LM) $(LIBFTDIR)
		$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LIBFT) $(RLIB)

all: $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += -fsanitize=address -g3
debug: $(NAME)

madebug: $(OBJS) $(INCLUDES) $(OBJ.DEBUG)
		$(LM) $(LIBFTDIR)
		$(CC) -o $(NAME) -D MALLOC_FAIL=1 $(CFLAGS) $(OBJS) $(OBJ.DEBUG) $(LIBFT) $(RLIB)

clean:
		$(RM) $(OBJS)
		cd $(LIBFTDIR) && make clean

fclean: clean
		$(RM) $(NAME)
		cd $(LIBFTDIR) && make fclean

re: fclean all

.PHONY = all clean fclean re bonus debug madebug
