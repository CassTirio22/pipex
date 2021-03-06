# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/25 16:13:42 by ctirions          #+#    #+#              #
#    Updated: 2021/09/11 12:42:41 by ctirions         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLACK		=	$(shell tput -Txterm setaf 0)
RED			=	$(shell tput -Txterm setaf 1)
GREEN		=	$(shell tput -Txterm setaf 2)
YELLOW		=	$(shell tput -Txterm setaf 3)
LIGHTPURPLE	=	$(shell tput -Txterm setaf 4)
PURPLE		=	$(shell tput -Txterm setaf 5)
BLUE		=	$(shell tput -Txterm setaf 6)
WHITE		=	$(shell tput -Txterm setaf 7)
RESET		=	$(shell tput -Txterm sgr0)

SRCS		=	pipex.c \
				pipe.c

OBJS		=	$(addprefix srcs/, ${SRCS:.c=.o})

NAME		=	pipex.a
EXEC		=	pipex

LIBFT		=	./libft

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

.c.o:
				@${CC} ${CFLAGS} -c -I ./includes $< -o ${<:.c=.o}
				@echo "${LIGHTPURPLE}Compilation : $< --> .o${RESET}"

$(NAME):		${OBJS}
				@make -C ${LIBFT} full
				@cp ${LIBFT}/libft.a ${NAME}
				@ar -rcs ${NAME} ${OBJS}
				@ranlib ${NAME}
				@${CC} ${CFLAGS} ${NAME} -o ${EXEC}
all:			${NAME}

clean:			
				@rm -f ${OBJS}
				@make -C ${LIBFT} clean
				@echo "${RED}Clean done !${RESET}"

fclean:			clean
				@rm -f ${NAME} ${EXEC}
				@make -C ${LIBFT} fclean
				@echo "${RED}Fclean done !${RESET}"

re:				fclean all

.PHONY:			all clean fclean re