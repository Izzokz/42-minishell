NAME = minishell

LIB = 010_FT_PRINTF/libftprintf.a

MAINDIR = 000_MAIN/
UTILSDIR = 100_UTILS/
BUILTINSDIR = 110_BUILTINS/
MAINSRC = $(MAINDIR)main.c \
	$(MAINDIR)ft_pipe_split.c \
	$(MAINDIR)ft_make_pipeline.c
UTILSSRC = $(UTILSDIR)ft_free_all.c
BUILTINSSRC = $(BUILTINSDIR)ft_exit.c

OBJDIR = 666_OBJ/
OBJ = $(patsubst %.c,$(OBJDIR)%.o,$(notdir $(MAINSRC) $(UTILSSRC) $(BUILTINSSRC)))
DEP = $(patsubst %.c,$(OBJDIR)%.d,$(notdir $(MAINSRC) $(UTILSSRC) $(BUILTINSSRC)))

CCA = cc -Wall -Werror -Wextra -L/usr/local/lib -I/usr/local/include -lreadline -MP -MMD -g3

MAKEFLAGS += --no-print-directory

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	@$(CCA) -o $(NAME) $(OBJ) $(LIB)
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

$(LIB):
	@$(MAKE) -C 010_FT_PRINTF/

clean:
	@$(MAKE) clean -C 010_FT_PRINTF/
	@rm -f $(OBJ) $(DEP)
	@printf "\033[38m\033[1mMinishell: \033[1;37m666_OBJ/ Cleaned !\033[0m\n"

fclean:
	@$(MAKE) fclean -C 010_FT_PRINTF/
	@rm -f $(OBJ) $(NAME) $(DEP)
	@printf "\033[38m\033[1mMinishell: \033[1;37mCleaned !\033[0m\n"

re: fclean all

.PHONY: all clean fclean re libs

-include $(DEP)
