# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/13 14:39:47 by sgodin            #+#    #+#              #
#    Updated: 2023/08/23 15:47:47 by sgodin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = src/main.c src/get_map.c

INCL = include/cub3d.h

NAME =  cub3d

GCC = gcc #-Wall -Wextra -Werror

OBJS_DIR = ./objects/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

SHELL = bash
RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
RESET = \033[0m

all: ${NAME}

${NAME}: ${OBJS} ${INCL}
	@${GCC} ${OBJS} -o ${NAME} && echo -ne "\r${BLUE}Compiling ${NAME} ${GREEN}Done${RESET}\n" || echo -ne "\r${BLUE}Compiling ${NAME} ${RED}Error${RESET}\n"

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@ ${GCC} -c $< -o $@

clean:
	@echo -ne "${RED}Cleaning...${RESET}"
	@rm -f ${OBJS} && echo -ne "\r${RED}Cleaning ${GREEN}Done${RESET}\n" || echo -ne "\r${RED}Cleaning ${RED}Error${RESET}\n"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.c.o:
	@echo -ne "${BLUE}Compiling $<${RESET}"
	@${GCC} -c $< -o ${<:.cpp=.o} && echo -ne "\r\033[K"

.PHONY: all clean fclean re .cpp.o bonus