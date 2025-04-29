NAME    := minishell
CC      := cc
CFLAGS  := -Wall -Werror -Wextra -g3
MAKE    := make
LIBFT_NAME := libft.a
LIBFT_DIR  := ./libft

# Directories
SRCS_DIR := ./srcs
OBJS_DIR := ./objs

# Sources
SRCS = minishell.c prompt.c signal.c\
 exec/builtins.c builtins/env.c exec/exec_cmd.c exec/cmd_track.c exec/env/env2.c\
 garbage_collector/gc.c garbage_collector/split_gc.c exec/redirections/redirects.c\
 parsing/parsing.c parsing/pars_buffer.c parsing/pars_buffer_utils.c parsing/split_pars/split.c parsing/expand.c parsing/split_pars/split_utils.c parsing/quotes.c parsing/expand_utils.c\
 utils/utils1.c utils/utils4.c utils/utils2.c utils/utils3.c utils/utils.c utils/utils5.c utils/utils6.c utils/utils7.c utils/utils9.c\
 utils/opens.c utils/utils8.c utils/util_pipe.c utils/handles_utils.c utils/utils_pipes2.c\
 utils/utils_heredoc.c exec/expand_help/expand_util.c exec/heredoc/heredoc.c exec/heredoc/functions_heredoc.c exec/heredoc/heredoc_3.c utils/ft_commands.c\
 builtins/cd.c builtins/echo.c builtins/exit.c builtins/export.c builtins/pwd.c builtins/unset.c

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
TOTAL := $(words $(SRCS))

all: $(LIBFT_DIR)/$(LIBFT_NAME) $(NAME)

$(LIBFT_DIR)/$(LIBFT_NAME):
	@cd $(LIBFT_DIR) && $(MAKE) -s all

$(NAME): $(LIBFT_DIR)/$(LIBFT_NAME) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT_DIR)/$(LIBFT_NAME) -lreadline
	@printf "\n\033[0;32m✔ Compilation terminée avec succès\n✔ A toi de jouer !\033[0m\n"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ && \
	COUNT=$$(find $(OBJS_DIR) -name "*.o" | wc -l); \
	PERCENT=$$(echo "$$COUNT * 100 / $(TOTAL)" | bc); \
	BARS=$$(echo "$$PERCENT / 5" | bc); \
	LINE=$$(printf "%0.s█" $$(seq 1 $$BARS)); \
	SPACES=$$(printf "%0.s " $$(seq $$BARS 19)); \
	printf "\r\033[0;36m[%-20s] %3s%%\033[0m" "$$LINE$$SPACES" "$$PERCENT"

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJS_DIR)
	@cd $(LIBFT_DIR) && $(MAKE) -s clean

fclean: clean
	@rm -f $(NAME)
	@cd $(LIBFT_DIR) && $(MAKE) -s fclean

re: fclean all

.PHONY: all clean fclean re