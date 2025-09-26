NAME := push_swap
CC := cc
CFLAGS := -Wall -Wextra -Werror -g3
LIBFT := srcs/libft/libft.a
SRCS_LIBFT := srcs/libft
INCLUDES := includes
CPPFLAGS :=  $(addprefix -I,$(INCLUDES))
SRCS_MANDATORY := push_swap.c     handle_error.c     parsing_args.c    moves.c \
                  moves_core.c    moves_utils.c
SRCS_BONUS :=
OBJTS   := $(SRCS_MANDATORY:.c=.o)
SRCS_BONUS := $(addprefix srcs/bonus/,$(SRCS_BONUS))
OBJTS_BONUS	:= $(SRCS_BONUS:.c=.o)
OBJTS_LIBFT = $(shell $(MAKE) -s -C $(SRCS_LIBFT) get_var)
OBJTS_LIBFT := $(addprefix $(SRCS_LIBFT)/,$(OBJTS_LIBFT))


# Cores ANSI
GREEN  = \033[0;32m
RED    = \033[0;31m
YELLOW = \033[0;33m
BLUE   = \033[0;34m
MAGENTA= \033[0;35m
CYAN   = \033[0;36m
NC     = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJTS)
		@echo "$(YELLOW)+==========================================+"
		@echo "          Build $(NAME)          	"
		@echo "+==========================================+$(NC)"
		$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJTS) $(LIBFT) -o $(NAME)


$(LIBFT): $(OBJTS_LIBFT)
		@echo "$(MAGENTA)+==========================================+"
		@echo "                Github: Norethx       "
		@echo "+==========================================+\n\n$(NC)"
		@echo "$(GREEN)	⢀⡴⠑⡄⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠸⡇⠀⠿⡀⠀⠀⠀⣀⡴⢿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠑⢄⣠⠾⠁⣀⣄⡈⠙⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⢀⡀⠁⠀⠀⠈⠙⠛⠂⠈⣿⣿⣿⣿⣿⠿⡿⢿⣆⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⢀⡾⣁⣀⠀⠴⠂⠙⣗⡀⠀⢻⣿⣿⠭⢤⣴⣦⣤⣹⠀⠀⠀⢀⢴⣶⣆"
		@echo "	⠀⠀⢀⣾⣿⣿⣿⣷⣮⣽⣾⣿⣥⣴⣿⣿⡿⢂⠔⢚⡿⢿⣿⣦⣴⣾⠁⠸⣼⡿"
		@echo "	⠀⢀⡞⠁⠙⠻⠿⠟⠉⠀⠛⢹⣿⣿⣿⣿⣿⣌⢤⣼⣿⣾⣿⡟⠉⠀⠀⠀⠀⠀"
		@echo "	⠀⣾⣷⣶⠇⠀⠀⣤⣄⣀⡀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠉⠈⠉⠀⠀⢦⡈⢻⣿⣿⣿⣶⣶⣶⣶⣤⣽⡹⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⠀⠉⠲⣽⡻⢿⣿⣿⣿⣿⣿⣿⣷⣜⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣷⣶⣮⣭⣽⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⣀⣀⣈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠻⠿⠿⠿⠿⠛⠉\n\n$(NC)"
		@echo "$(RED)+==========================================+"
		@echo "      Welcome to push_swap - Build libft       "
		@echo "+==========================================+$(NC)"
		@echo "Compilando código...\n"
		@make -C $(SRCS_LIBFT) all
		@echo "$(BLUE)+==========================================+"
		@echo "          Build Objts push_swap         	"
		@echo "+==========================================+$(NC)"

%.o: %.c
		$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: clean fclean re all bonus $(OBJTS_LIBFT)

bonus:
		$(MAKE) SRCS_MANDATORY="$(SRCS_BONUS)" all

clean:
		@make -C $(SRCS_LIBFT) clean
		rm -f $(OBJTS) $(OBJTS_BONUS)

fclean:
		@make -C $(SRCS_LIBFT) fclean
		rm -f $(OBJTS) $(OBJTS_BONUS)
		rm -f $(NAME) $(MLX42)

re: fclean all
