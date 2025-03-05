NAME = minishell

LIBS = 010_FT_PRINTF/libftprintf.a 020_LIBFT/libft.a

MAINDIR = 000_MAIN/
MAIN1DIR = $(MAINDIR)001_SPLIT_PARSING/
MAIN2DIR = $(MAINDIR)002_PIPELINE/
UTILSDIR = 100_UTILS/
BUILTINSDIR = 110_BUILTINS/
MAINSRC = $(MAINDIR)main.c \
	$(MAINDIR)ft_utils.c \
	$(MAINDIR)ft_history.c
MAIN1SRC = $(MAIN1DIR)ft_pipe_split.c \
	$(MAIN1DIR)ft_fix_redirections.c \
	$(MAIN1DIR)ft_split_redirec.c \
	$(MAIN1DIR)ft_fix_order.c \
	$(MAIN1DIR)ft_valid_input.c
MAIN2SRC = $(MAIN2DIR)ft_exec.c \
	$(MAIN2DIR)ft_loop.c \
	$(MAIN2DIR)ft_hd_loop.c \
	$(MAIN2DIR)ft_unlink_hd.c \
	$(MAIN2DIR)ft_make_pipeline.c \
	$(MAIN2DIR)ft_open.c \
	$(MAIN2DIR)ft_heredoc.c \
	$(MAIN2DIR)ft_pipeline_function_set.c
UTILSSRC = $(UTILSDIR)ft_free_all.c \
	$(UTILSDIR)ft_path.c \
	$(UTILSDIR)ft_expand_split.c \
	$(UTILSDIR)ft_expand_remap.c \
	$(UTILSDIR)ft_expand_slines.c \
	$(UTILSDIR)ft_tdata.c \
	$(UTILSDIR)ft_is_env.c
BUILTINSSRC = $(BUILTINSDIR)ft_exit.c \
	$(BUILTINSDIR)ft_pwd.c \
	$(BUILTINSDIR)111_EXPORT/ft_export.c \
	$(BUILTINSDIR)111_EXPORT/ft_export2.c \
	$(BUILTINSDIR)111_EXPORT/ft_export3.c \
	$(BUILTINSDIR)111_EXPORT/ft_export4.c \
	$(BUILTINSDIR)ft_unset.c \
	$(BUILTINSDIR)ft_echo.c \
	$(BUILTINSDIR)ft_cd.c \

OBJDIR = 666_OBJ/
OBJ = $(patsubst %.c,$(OBJDIR)%.o,$(notdir $(MAINSRC) $(MAIN1SRC) $(MAIN2SRC) $(UTILSSRC) $(BUILTINSSRC)))
DEP = $(patsubst %.c,$(OBJDIR)%.d,$(notdir $(MAINSRC) $(MAIN1SRC) $(MAIN2SRC) $(UTILSSRC) $(BUILTINSSRC)))

CCA = cc -Wall -Werror -Wextra -L/usr/local/lib -I/usr/local/include -lreadline -MP -MMD -g3

MAKEFLAGS += --no-print-directory

all: $(NAME)

$(NAME): $(LIBS) $(OBJ)
	@$(CCA) -o $(NAME) $(OBJ) $(LIBS)
	@printf "\n\033[38m\033[1mMinishell: \033[1;97mBuild Complete !\033[0m\n"

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@printf "\033[38m\033[1mMinishell: \033[1;37m666_OBJ/ Generated !\033[0m\n"

$(OBJDIR)%.o: $(MAIN1DIR)%.c | $(OBJDIR)
	@cc -Wall -Werror -Wextra -MP -MMD -g3 -o $@ -c $< -I.

$(OBJDIR)%.o: $(MAIN2DIR)%.c | $(OBJDIR)
	@cc -Wall -Werror -Wextra -MP -MMD -g3 -o $@ -c $< -I.

$(OBJDIR)%.o: $(MAINDIR)%.c | $(OBJDIR)
	@cc -Wall -Werror -Wextra -MP -MMD -g3 -o $@ -c $< -I.

$(OBJDIR)%.o: $(UTILSDIR)%.c | $(OBJDIR)
	@cc -Wall -Werror -Wextra -MP -MMD -g3 -o $@ -c $< -I.

$(OBJDIR)%.o: $(BUILTINSDIR)%.c | $(OBJDIR)
	@cc -Wall -Werror -Wextra -MP -MMD -g3 -o $@ -c $< -I.

$(OBJDIR)%.o: $(BUILTINSDIR)111_EXPORT/%.c | $(OBJDIR)
	@cc -Wall -Werror -Wextra -MP -MMD -g3 -o $@ -c $< -I.

libs:
	@rm -rf 010_FT_PRINTF/
	@git clone https://github.com/Izzokz/42-ft_printf.git 010_FT_PRINTF/
	@printf "\033[38m\033[1mMinishell: \033[1;37mft_printf Cloned !\033[0m\n"

	@rm -rf 020_LIBFT/
	@git clone https://github.com/PGBmax/Libft.git 020_LIBFT/
	@printf "\033[38m\033[1mMinishell: \033[1;37mlibft Cloned !\033[0m\n"

dep:
	@sudo apt install libreadline-dev

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

chazzup:

.PHONY: all clean fclean re libs

-include $(DEP)
