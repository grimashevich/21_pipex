NAME := pipex
CC := clang
OBJ_DIR := obj

CFLAGS := -Wall -Wextra -Werror -g
CPPFLAGS := -MMD
S_FLAGS := -fsanitize=address

SRC_C :=	ft_atoi.c			functions0.c		ft_split.c			ft_strncmp.c	\
			f_path0.c			f_path1.c			f_parse.c			functions1.c	\
			functions2.c		functions3.c		functions4.c
			
SRC_M :=	main_mandatory.c

SRC_B :=	main.c

SRC := 		$(SRC_C) $(SRC_M)
SRC_B :=	$(SRC_B) $(SRC_C)

OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_B := $(SRC_B:%.c=$(OBJ_DIR)/%.o)

DEP := $(OBJ:.o=.d)
DEP_B := $(OBJ_B:.o=.d)

.PHONY: all clean fclean re bonus

all:	$(NAME)
bonus:
	@make OBJ="$(OBJ_B)" DEP="$(DEP_B)" all

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) $(S_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(S_FLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

-include $(DEP) $(DEP_B)

clean:
	@rm -f $(OBJ) $(DEP) $(OBJ_B) $(DEP_B)

fclean: clean
	@rm -f $(NAME) $(NAME_B)

re: fclean all
