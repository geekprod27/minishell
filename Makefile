# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfelsemb <nfelsemb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/31 22:41:32 by nfelsemb          #+#    #+#              #
#    Updated: 2022/08/29 18:46:45 by nfelsemb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
INCLUDE = ./include/
LIBFT	= ./libft/libft.a
CFLAGS	+= -Wall -Werror -Wextra -g3

FILES	= main.c pwd.c util.c echo.c exitfree.c norm.c autres.c pipe.c pipe2.c fi.c la.c
FILES_PARS = quote_checker.c tokens_split.c sk_strtok.c build_tokens.c

SRCS	= $(addprefix ./srcs/, $(FILES))
OBJS	= $(addprefix ./objs/, $(FILES:.c=.o))
SRCS_PARS	= $(addprefix ./srcs/parsing/, $(FILES_PARS))
OBJS_PARS	= $(addprefix ./objs/parsing/, $(FILES_PARS:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(OBJS_PARS)
	$(CC) $(OBJS) $(OBJS_PARS) $(LIBFT) $(CFLAGS) -o $@ -lreadline

objs/%.o: srcs/%.c
	mkdir -p ./objs/
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(LIBFT):
	$(MAKE) --no-print-directory -C ./libft

clean:
	$(MAKE) -C ./libft clean
	$(RM) $(OBJS) 

fclean:	clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)

re:	fclean all

.PHONY:	all clean fclean re
