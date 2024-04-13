# RUN PROJECT: valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=ignore_readline.sup -s ./minishell

NAME = minishell

LIBFT = ./libft/libft.a

LIBFTDIR = ./libft

CC = cc

LM = make -C

CFLAGS = -lreadline #-Wall -Wextra -Werror

INCLUDES = minishell.h inc/builtins.h inc/executor.h inc/parser.h inc/signals.h inc/structs.h inc/tokenizer.h

RM = rm -f

BUILT_INS = src/builtins/ft_echo.c \
			src/builtins/ft_pwd.c

EXECUTOR = 

TOKENIZER =	src/tokenizer/token_generator.c \
			src/tokenizer/token_list.c

PARSER =	src/parser/get_path.c \
			src/parser/parse_utils.c

GENERAL = src/general/main.c \
			src/general/error_management.c \
			src/general/free_utils.c \
			src/general/general_utils.c

OBJS = ${BUILT_INS:.c=.o} ${EXECUTOR:.c=.o} ${TOKENIZER:.c=.o} ${GENERAL:.c=.o} ${PARSER:.c=.o}

$(NAME): $(OBJS) $(INCLUDES)
		$(LM) $(LIBFTDIR)
		$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline

all: $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell
debug: $(NAME)

clean:
		$(RM) $(OBJS)
		cd $(LIBFTDIR) && make clean

fclean: clean
		$(RM) $(NAME)
		cd $(LIBFTDIR) && make fclean

re: fclean all

.PHONY = all clean fclean re bonus debug