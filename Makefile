# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: pduhard- <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/11/13 00:29:26 by pduhard-     #+#   ##    ##    #+#        #
#    Updated: 2018/12/09 20:43:47 by sbedene     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

#__________CONFIG__________#

NAME		=	lem-in

CC			=	gcc
FLAGS		=	-g -Wall -Werror -Wextra
LIB_FLAGS	=	-L$(LIB_PATH) $(LIB_FLAG)
INCLUDES	=	-I lem-in.h

SRC_PATH	=	./
BIN_PATH	=	./
LIB_PATH	=	./libft/

SRC			=	main.c			\
				parse.c			\
				stock.c			\
				parse_utils.c	\
				output.c		\
				ft_find_ways.c	\
				ft_anthill.c	\
				ft_heat.c		\
				ft_trim.c		\
				ft_probe.c		\
				ft_probe_utils.c\
				ft_free.c		\

BIN			=	$(SRC:.c=.o)

LIB_FLAG			=	-lft
LIB					=	libft.a

SRCS		=	$(addprefix $(SRC_PATH), $(SRC))
BINS		=	$(addprefix $(BIN_PATH), $(BIN))
LIBS		=	$(addprefix $(LIB_PATH), $(LIB))

.PHONY: all clean fclean re lib

#__________COLORS__________#

R			=	\033[0;31m
G			=	\033[32;7m
B			=	\033[0;34m
N			=	\33[0m

#__________RULES__________#

all: $(NAME)

	@make -C libft

$(NAME): $(LIBS) $(BINS)

	@$(CC) $(INCLUDES) $(FLAGS) $(LIB_FLAGS) $^ -o $@
	@echo "\n\n$(B)[EXECUTABLE \"$(NAME)\" READY]\n"

$(LIBS):

	@make -C $(LIB_PATH)

$(BIN_PATH)%.o: $(SRC_PATH)%.c lem_in.h

	@mkdir -p $(BIN_PATH) || true
	@$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $< && echo "${G} \c"

clean:

	@make clean -C $(LIB_PATH)
	@echo "${R}[CLEANING $(NAME) BINARIES]"
	@rm -f $(BINS)

fclean: clean

	@echo "\n${R}[REMOVING "libft.a"]"
	@rm -rf $(LIB_PATH)/libft.a
	@echo "\n${R}[REMOVING \"$(NAME)\"]\n"
	@rm -f $(NAME)

re: fclean all
