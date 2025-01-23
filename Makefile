NAME = minishell

LIBS = 010_FT_PRINTF/libftprintf.a 020_LIBFT/libft.a

MAINDIR = 000_MAIN/
UTILSDIR = 100_UTILS/
BUILTINSDIR = 110_BUILTINS/
MAINSRC = $(MAINDIR)main.c \
	$(MAINDIR)ft_pipe_split.c \
	$(MAINDIR)ft_make_pipeline.c
UTILSSRC = $(UTILSDIR)ft_free_all.c \
	$(UTILSDIR)ft_path.c
BUILTINSSRC = $(BUILTINSDIR)ft_exit.c

OBJDIR = 666_OBJ/
OBJ = $(patsubst %.c,$(OBJDIR)%.o,$(notdir $(MAINSRC) $(UTILSSRC) $(BUILTINSSRC)))
DEP = $(patsubst %.c,$(OBJDIR)%.d,$(notdir $(MAINSRC) $(UTILSSRC) $(BUILTINSSRC)))

CCA = cc -Wall -Werror -Wextra -L/usr/local/lib -I/usr/local/include -lreadline -MP -MMD -g3

MAKEFLAGS += --no-print-directory

all: $(NAME)

$(NAME): $(LIBS) $(OBJ)
	@$(CCA) -o $(NAME) $(OBJ) $(LIBS)
	@printf "\n\033[38m\033[1mMinishell: \033[1;97mBuild Complete !\033[0m\n"

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@printf "\033[38m\033[1mMinishell: \033[1;37m666_OBJ/ Generated !\033[0m\n"

$(OBJDIR)%.o: $(MAINDIR)%.c | $(OBJDIR)
	@cc -Wall -Werror -Wextra -MP -MMD -g3 -o $@ -c $<

$(OBJDIR)%.o: $(UTILSDIR)%.c | $(OBJDIR)
	@cc -Wall -Werror -Wextra -MP -MMD -g3 -o $@ -c $<

$(OBJDIR)%.o: $(BUILTINSDIR)%.c | $(OBJDIR)
	@cc -Wall -Werror -Wextra -MP -MMD -g3 -o $@ -c $<

libs:
	@rm -rf 010_FT_PRINTF/
	@git clone https://github.com/Izzokz/42-ft_printf.git 010_FT_PRINTF/
	@printf "\033[38m\033[1mMinishell: \033[1;37mft_printf Cloned !\033[0m\n"

	@rm -rf 020_LIBFT/
	@git clone https://github.com/PGBmax/Libft.git 020_LIBFT/
	@printf "\033[38m\033[1mMinishell: \033[1;37mlibft Cloned !\033[0m\n"

$(LIBS):
	@$(MAKE) -C 010_FT_PRINTF/
	@$(MAKE) -C 020_LIBFT/

clean:
	@$(MAKE) clean -C 010_FT_PRINTF/
	@$(MAKE) clean -C 020_LIBFT/
	@rm -f $(OBJ) $(DEP)
	@printf "\033[38m\033[1mMinishell: \033[1;37m666_OBJ/ Cleaned !\033[0m\n"

fclean:
	@$(MAKE) fclean -C 010_FT_PRINTF/
	@$(MAKE) fclean -C 020_LIBFT/
	@rm -f $(OBJ) $(NAME) $(DEP)
	@printf "\033[38m\033[1mMinishell: \033[1;37mCleaned !\033[0m\n"

re: fclean all

.PHONY: all clean fclean re libs

-include $(DEP)
