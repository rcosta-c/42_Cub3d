#  |  |  ___ \    \  |         |
#  |  |     ) |  |\/ |   _  |  |  /   _ 
# ___ __|  __/   |   |  (   |    <    __/ 
#    _|  _____| _|  _| \__,_| _|\_\ \___|
#                              by jcluzet
################################################################################
#                                     CONFIG                                   #
################################################################################

NAME        := cub3d
CC        := gcc
FLAGS    := -Wall -Wextra -Werror 
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=      lib/libft/ft_lstlast.c \
                          lib/libft/ft_isalpha.c \
                          lib/libft/ft_strdup.c \
                          lib/libft/ft_strnstr.c \
                          lib/libft/ft_memchr.c \
                          lib/libft/ft_substr.c \
                          lib/libft/ft_strchr.c \
                          lib/libft/ft_strlcpy.c \
                          lib/libft/ft_strncmp.c \
                          lib/libft/ft_tolower.c \
                          lib/libft/ft_memmove.c \
                          lib/libft/ft_strmapi.c \
                          lib/libft/ft_lstiter.c \
                          lib/libft/ft_strlcat.c \
                          lib/libft/ft_strlen.c \
                          lib/libft/ft_lstmap.c \
                          lib/libft/ft_isprint.c \
                          lib/libft/ft_atoi.c \
                          lib/libft/ft_isdigit.c \
                          lib/libft/ft_isspace.c \
                          lib/libft/ft_memset.c \
                          lib/libft/ft_lstnew.c \
                          lib/libft/ft_strrchr.c \
                          lib/libft/ft_itoa.c \
                          lib/libft/ft_strtrim.c \
                          lib/libft/ft_putnbr_fd.c \
                          lib/libft/ft_isalnum.c \
                          lib/libft/ft_putstr_fd.c \
                          lib/libft/ft_lstsize.c \
                          lib/libft/ft_isascii.c \
                          lib/libft/ft_lstdelone.c \
                          lib/libft/ft_strjoin.c \
                          lib/libft/ft_memcpy.c \
                          lib/libft/ft_lstclear.c \
                          lib/libft/ft_memcmp.c \
                          lib/libft/ft_bzero.c \
                          lib/libft/ft_putendl_fd.c \
                          lib/libft/ft_striteri.c \
                          lib/libft/ft_calloc.c \
                          lib/libft/ft_putchar_fd.c \
                          lib/libft/ft_split.c \
                          lib/libft/ft_lstadd_front.c \
                          lib/libft/ft_lstadd_back.c \
                          lib/libft/ft_atol.c \
                          lib/libft/ft_toupper.c \
                          lib/gnl/get_next_line_utils.c \
                          lib/gnl/get_next_line.c \
                          src/main.c \
                          src/init.c \
                          src/game.c \
                          src/parse_map_utils1.c \
                          src/free.c \
                          src/map_analyzer2.c \
                          src/parse_map.c \
                          src/map_analyzer1.c \
                          src/load_textures.c \
                          src/player.c \
                          src/render_map.c \
                          src/render_utils.c \
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

UNAME		:=	$(shell uname)

$(NAME): ${OBJS}
			@echo "$(GREEN)Linux compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			@chmod 777 ./lib/mlx/configure
			@ $(MAKE) -C ./lib/mlx all
			$(CC) $(CFLAGS) -g3 -o $(NAME) $(OBJS) -L ./lib/mlx -lmlx -Ilmlx -lXext -lX11 -lm
			@echo "$(GREEN)$(NAME) created[0m ✔️"


all:		${NAME}

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ rm -rf $(NAME).dSYM >/dev/null 2>&1
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ $(MAKE) -C ./lib/mlx clean 
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re


