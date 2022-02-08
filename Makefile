# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abonard <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/08 19:48:37 by abonard           #+#    #+#              #
#    Updated: 2022/02/08 20:28:17 by abonard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NC = \033[0m
RED = \033[0;91m
ORANGE = \033[93m
GREEN = \033[0;92m
PURPLE = \033[0;95m
BLUE = \033[0;34m
BOLD = \033[1m

SRCS_SERVER		=	./server_src/server.c

SRCS_CLIENT		= ./client_src/client.c

SRCS_SERVER_B	=	./server_bonus/server_bonus.c


SRCS_CLIENT_B	=	./client_bonus/client_bonus.c

INCLUDES	=	./libft/libft.h \
				./libft/ft_printf.h \
				./libft/ft_struct.h \
				./libft/minitalk.h

INCLUDES_BONUS	=	./libft/libft.h \
					./libft/ft_printf.h \
					./libft/ft_struct.h \
					./libft/minitalk.h

HEAD		= ./includes/

HEAD_BONUS	= ./includes/

LIBFT		= ./libft/libft.a

LIB_DIR		= ./libft/

NAME		= Server

NAME2		= Client

NAME3		= Server__bonus

NAME4		= Client__bonus

CC			= clang

OBJS		= ${SRCS_SERVER:.c=.o}

OBJS2		= ${SRCS_CLIENT:.c=.o}

OBJS3		= ${SRCS_SERVER_B:.c=.o}

OBJS4		= ${SRCS_CLIENT_B:.c=.o}

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -g


.c.o:
		@${CC} ${CFLAGS} -I${HEAD_BONUS} -c $< -o ${<:.c=.o}
		@echo "${GREEN}[ OK ]	${ORANGE}${<:.s=.o}${NC}"

all:		${NAME} ${NAME2}

${NAME}:	${OBJS}
			@make -C ${LIB_DIR}
			@echo "${GREEN}\nlibft.a		has been created"
			@${CC} ${CFLAGS} -I${HEAD} -o ${NAME} $(OBJS) ${LIBFT}
			@echo "server		has been created\n${NC}"


${NAME2}:	${OBJS2}
			@${CC} ${CFLAGS} -I${HEAD} -o ${NAME2} $(OBJS2) ${LIBFT}
			@echo "${GREEN}client		has been created\n${NC}"

${NAME3}:	${OBJS3}
			@make -C ${LIB_DIR}
			@echo "${GREEN}\nlibft.a		has been created"
			@${CC} ${CFLAGS} -I${HEAD} -o ${NAME3} $(OBJS3) ${LIBFT}
			@echo "server_bonus		has been created\n${NC}"


${NAME4}:	${OBJS4}
			@echo "${GREEN}\nlibft.a		has been created"
			@${CC} ${CFLAGS} -I${HEAD} -o ${NAME4} $(OBJS4) ${LIBFT}
			@echo "client_bonus		has been created\n${NC}"

bonus:		${NAME3} ${NAME4}

clean:
			@make -C $(LIB_DIR) clean
			@${RM} ${OBJS}
			@${RM} ${OBJS2}
			@${RM} ${OBJS3}
			@${RM} ${OBJS4}
			@echo "${GREEN}[ OK ]${RED}	*.o files	deleted${NC}"

fclean:		clean
			@make -C $(LIB_DIR) fclean
			@echo "${GREEN}[ OK ]${RED}	libft.a		deleted${NC}"
			@${RM} ${NAME} ${NAME2} ${NAME3} ${NAME4}
			@echo "${GREEN}[ OK ]${RED}everything	deleted${NC}"

re :		fclean all

.PHONY:		all	clean	fclean re
