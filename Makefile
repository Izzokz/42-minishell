NAME = minishell

LIB = 010_FT_PRINTF/libftprintf.a

OBJDIR = 666_OBJ/
OBJ = NULL

CCA = cc -Wall -Werror -Wextra -g3

MAKEFLAGS += --no-print-directory

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	@$(CCA) -o $(NAME) $(OBJ) $(LIB)
	@printf "\n\033[32m\033[1mPipex: \033[1;97mBuild Complete !\033[0m\n"

libs:
	@git clone https://github.com/Izzokz/42-ft_printf.git 010_FT_PRINTF/
	@printf "\033[35m\033[1mPipex: \033[1;37mft_printf Cloned !\033[0m\n"

$(LIB):
	@$(MAKE) -C 010_FT_PRINTF/

clean:
	@$(MAKE) clean -C 010_FT_PRINTF/
	@rm -f $(OBJ)
	@printf "\033[32m\033[1mPipex: \033[1;37m666_OBJ/ Cleaned !\033[0m\n"

fclean:
	@$(MAKE) fclean -C 010_FT_PRINTF/
	@rm -f $(OBJ) $(NAME)
	@printf "\033[32m\033[1mPipex: \033[1;37mCleaned !\033[0m\n"

re: fclean all

.PHONY: all clean fclean re libs
