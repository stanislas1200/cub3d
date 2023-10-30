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

SRCS = src/mandatory/main.c\
		src/mandatory/get_map.c\
		src/mandatory/propagation.c\
		src/mandatory/stack.c\
		src/mandatory/utils.c\
		src/mandatory/utils2.c\
		src/mandatory/utils3.c\
		src/mandatory/parser.c\
		src/mandatory/cleaner.c\
		src/mandatory/end.c\
		src/mandatory/init.c\
		src/mandatory/movement.c\
			src/mandatory/raycasting/raycasting.c\
			src/mandatory/raycasting/rays.c\
			src/mandatory/raycasting/render.c

SRCS_BONUS = src/bonus/main_bonus.c\
		src/bonus/get_map_bonus.c\
		src/bonus/get_file_bonus.c\
		src/bonus/propagation_bonus.c\
		src/bonus/stack_bonus.c\
		src/bonus/utils_bonus.c\
		src/bonus/utils2_bonus.c\
		src/bonus/utils3_bonus.c\
		src/bonus/parser_bonus.c\
		src/bonus/event_bonus.c\
		src/bonus/sound_bonus.c\
		src/bonus/cleaner_bonus.c\
		src/bonus/init_bonus.c\
		src/bonus/movement_bonus.c\
			src/bonus/astar/Astar_bonus.c\
			src/bonus/astar/Astar_init_bonus.c\
			src/bonus/astar/Astar_free_bonus.c\
			src/bonus/astar/Astar_utils_bonus.c\
		src/bonus/monster_bonus.c\
		src/bonus/abutor_bonus.c\
		src/bonus/chubbs_egg_bonus.c\
		src/bonus/minimap_bonus.c\
		src/bonus/minimap2_bonus.c\
		src/bonus/game_logic_bonus.c\
		src/bonus/sprites_bonus.c\
		src/bonus/sprites2_bonus.c\
		src/bonus/sprites3_bonus.c\
			src/bonus/raycasting/raycasting_bonus.c\
			src/bonus/raycasting/rays_bonus.c\
			src/bonus/raycasting/mob_bonus.c\
			src/bonus/raycasting/render_bonus.c\
			src/bonus/raycasting/render2_bonus.c

INCL = include/cub3d.h
INCL_BONUS = include/cub3d_bonus.h

NAME =  cub3d

GCC = gcc -pthread -fsanitize=address -g -finline-functions -fvectorize -fslp-vectorize -ffast-math -falign-functions -funroll-loops -fstrict-aliasing -fomit-frame-pointer -flto -Ofast -O1 -O2 -Os -O3

OBJS_DIR = ./objects/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
OBJS_BONUS = $(addprefix $(OBJS_DIR), $(SRCS_BONUS:.c=.o))

SHELL = bash
RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
RESET = \033[0m

all: ${NAME}

${NAME}: ${OBJS} ${INCL}
	@${GCC} ${OBJS} -lmlx -framework OpenGL -framework AppKit -o ${NAME} && echo -ne "\r${BLUE}Compiling ${NAME} ${GREEN}Done${RESET}\n" || echo -ne "\r${BLUE}Compiling ${NAME} ${RED}Error${RESET}\n"

bonus: ${OBJS_BONUS} ${INCL_BONUS}
	@${GCC} ${OBJS_BONUS} -lmlx -framework OpenGL -framework AppKit -o ${NAME} && echo -ne "\r${BLUE}Compiling ${NAME} ${GREEN}Done${RESET}\n" || echo -ne "\r${BLUE}Compiling ${NAME} ${RED}Error${RESET}\n"

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@ ${GCC} -c $< -o $@

clean:
	@echo -ne "${RED}Cleaning...${RESET}"
	@rm -f ${OBJS} ${OBJS_BONUS} && echo -ne "\r${RED}Cleaning ${GREEN}Done${RESET}\n" || echo -ne "\r${RED}Cleaning ${RED}Error${RESET}\n"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.c.o:
	@echo -ne "${BLUE}Compiling $<${RESET}"
	@${GCC} -c $< -o ${<:.cpp=.o} && echo -ne "\r\033[K"

.PHONY: all clean fclean re .cpp.o bonus