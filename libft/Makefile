# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsanz-go <fsanz-go@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/23 11:59:52 by nvillalt          #+#    #+#              #
#    Updated: 2024/05/11 19:00:56 by fsanz-go         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

AR = ar -rc

SRCS = ft_atoi.c \
	   ft_isascii.c \
	   ft_memset.c \
	   ft_strncmp.c \
	   ft_toupper.c \
	   ft_bzero.c \
	   ft_isdigit.c \
	   ft_strchr.c \
	   ft_strnstr.c \
	   ft_isalnum.c \
	   ft_isprint.c \
	   ft_strlcpy.c \
	   ft_strrchr.c \
	   ft_isalpha.c \
	   ft_memcpy.c \
	   ft_strlen.c \
	   ft_tolower.c \
	   ft_putchar_fd.c \
	   ft_putstr_fd.c \
	   ft_putendl_fd.c \
	   ft_putnbr_fd.c \
	   ft_calloc.c \
	   ft_strdup.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_strlcat.c \
	   ft_substr.c \
	   ft_strjoin.c \
	   ft_memmove.c \
	   ft_itoa.c \
	   ft_strtrim.c \
	   ft_strmapi.c \
	   ft_striteri.c \
	   ft_split.c \
	   ft_strcmp.c \
	   get_next_line.c \
	   get_next_line_utils.c \
	   ft_putstr.c

BONUS = ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c

OBJS = $(SRCS:%.c=%.o)

OBJS_BONUS = $(BONUS:%.c=%.o)

RM = rm -f

.PHONY: clean fclean re all bonus

all: $(NAME)

$(NAME): $(OBJS) $(OBJS_BONUS)
	$(AR) $(NAME) $(OBJS) $(OBJS_BONUS)

# BONUS goes together with the main functions, 
# modified from the actual lib

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean:
	$(RM) $(NAME) $(OBJS) $(OBJS_BONUS)

re: fclean all
