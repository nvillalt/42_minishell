#···COLOURS·····#
BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
PUR			= \033[0;35m
YLW			= \033[0;33m
RST			= \033[0m
END			= \e[0m

#···NAME········#
NAME = minishell

#···PATH········#
SRC_PATH = src/
OBJ_PATH = obj/
INC_PATH = inc/

#····CC + FLAGS ···#
CC = cc
CFLAGS = -Wall -Wextra -g3 #-Werror
CFLAGS += -I $(INC_PATH) -I $(LIBFT_DIR) -I $(SRC_PATH) 

#···INC········#
INC = minishell.h
INCS = built-ins.h executor.h parser.h signals.h structs.h tokenizer.h

#···SRCS········#
SRC = main.c \
	built-ins/ft_echo.c

OBJ_NAME = $(SRC:%.c=%.o) # CREO QUE EL ERROR ESTÁ AQUÍ
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

RM = rm -rf

#···LIBFT·······#
#LIBFT
LIBFT_DIR = libft
# search for .a in current directory
LDFLAGS = -L $(LIBFT_DIR)
# lib name
LDLIBS = -lft

#···RULES······#
.PHONY: all re clean fclean debug

all: $(NAME)
	@echo "\033[2K\r${GRN}[CREATED]\033[0m $(NAME)\n"

$(NAME): $(OBJ)
	make -sC $(LIBFT_DIR)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS) $(LDLIBS)
	@echo "\033[2K\r${PUR}[COMPILING LIBFT]${RST}'$<'\n"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC_PATH)/$(INCS) 
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[2K\r${BLU}[COMPILING SOURCES]${RST}'$<'\n"

debug: CFLAGS += -fsanitize=address -g3
debug: $(NAME)

clean:
	make fclean -sC $(LIBFT_DIR)
	$(RM) $(OBJ_PATH)
	@echo "\033[2K\r${RED}[CLEANED]\033[0m $(NAME)\n"

fclean: clean
	$(RM) $(NAME)
	@echo "\033[2K\r${RED}[FCLEANED]\033[0m $(NAME)\n"
	
re: fclean all

# Automatic variables :                                                            \
\
$@ : rule name  target.         			                                     \
\
$^ : The names of all the prerequisites, with spaces between them. For           \
prerequisites which are archive members, only the named member is used.          \
\
$< : The name of the first prerequisite. If the target got its recipe from an    \
implicit rule, this will be the first prerequisite added by the implicit rule.   \
 \
$? : The names of all the prerequisites that are newer than the target, with     \
spaces between them. For prerequisites which are archive members, only the       \
named member is used.                                                            \
\
source :                                                                         \
https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html      \