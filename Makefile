# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgodin <sgodin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/13 14:39:47 by sgodin            #+#    #+#              #
#    Updated: 2023/10/01 18:24:29 by sgodin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = src/main.c\
		src/get_map.c\
		src/propagation.c\
		src/stack.c\
		src/utils.c\
		src/utils2.c\
		src/utils3.c\
		src/parser.c\
		src/cleaner.c\
		src/init.c\
		src/movement.c\
		src/Astar.c\
		src/monster.c\
		src/minimap.c\
		src/minimap2.c\
			src/raycasting/raycasting.c\
			src/raycasting/rays.c\
			src/raycasting/mob.c\
			src/raycasting/render.c

INCL = include/cub3d.h

NAME =  cub3d

GCC = gcc -pthread -fsanitize=address -g -finline-functions -fvectorize -fslp-vectorize -ffast-math -falign-functions -funroll-loops -fstrict-aliasing -fomit-frame-pointer -flto -Ofast -O1 -O2 -Os -O3

OBJS_DIR = ./objects/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

SHELL = bash
RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
RESET = \033[0m

all: ${NAME}

${NAME}: ${OBJS} ${INCL}
@${GCC} ${OBJS} -lmlx -framework OpenGL -framework AppKit -o ${NAME} && echo -ne "\r${BLUE}Compiling ${NAME} ${GREEN}Done${RESET}\n" || echo -ne "\r${BLUE}Compiling ${NAME} ${RED}Error${RESET}\n"

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