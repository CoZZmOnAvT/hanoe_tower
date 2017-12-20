# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/10 17:05:19 by pgritsen          #+#    #+#              #
#    Updated: 2017/12/16 20:48:56 by pgritsen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	hanoe

CC			=	gcc

CFLAGS		=	-Wextra -Wall -O3 -g3

HDRS		=	

SRCS		=	source.c

OBJDIR		=	obj

OBJ			=	$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBS		=	libft/libft.a

INCLUDES	=	-Ilibft/ -Llibft -lft

all: lib $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(HDRS) $(LIBS)
	@printf "\n\033[32m[Creating $(NAME)].......\033[0m"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INCLUDES)
	@printf "\033[32m[DONE]\033[0m\n"

$(OBJDIR):
	@printf "\n\033[32m[Creating folder $(OBJDIR)].......\033[0m"
	@mkdir $(OBJDIR)
	@printf "\033[32m[DONE]\033[0m\n"

$(OBJ): $(OBJDIR)/%.o : %.c
	@printf "\033[32m[Compiling $<].......\033[0m"
	@$(CC) $(CFLAGS) -Ilibft -c $< -o $@
	@printf "\033[32m[DONE]\033[0m\n"

$(LIBS): lib

lib:
	@printf "\033[33m[Creating libft.a].......[START]\033[0m\n"
	@make -j3 -C libft
	@printf "\033[33m[Creating libft.a].......[END]\033[0m\n"

clean:
	@make -j3 -C libft clean
	@printf "\033[31m[Cleaning object files].......\033[0m"
	@rm -rf $(OBJDIR)
	@printf "\033[31m[DONE]\033[0m\n"

fclean: clean	
	@make -j3 -C libft fclean
	@rm -rf $(NAME)
	@printf "\033[31m[Cleaning All].......\033[0m"
	@printf "\033[31m[DONE]\033[0m\n"

re:	fclean all
	@printf "\033[33m[Rebuild].......[END]\033[0m\n"

.NOTPARALLEL: all $(NAME) re
