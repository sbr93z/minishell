RED     := \033[0;31m
GREEN   := \033[0;32m
YELLOW  := \033[0;33m
RESET   := \033[0m
BLUE    := \e[0;34m

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
 utils/utils_heredoc.c exec/expand_help/expand_util.c exec/heredoc/heredoc.c exec/heredoc/functions_heredoc.c exec/heredoc/heredoc_2.c exec/heredoc/heredoc_3.c utils/ft_commands.c\
 builtins/cd.c builtins/echo.c builtins/exit.c builtins/export.c builtins/pwd.c builtins/unset.c
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all: $(LIBFT_DIR)/$(LIBFT_NAME) $(NAME)

$(LIBFT_DIR)/$(LIBFT_NAME):
	@echo "\n${YELLOW}Making libft...${RESET}"
	@cd $(LIBFT_DIR) && $(MAKE) all
	@echo "${GREEN}Done.${RESET}"

$(NAME): $(LIBFT_DIR)/$(LIBFT_NAME) $(OBJS)
	@echo "\n${YELLOW}Compiling Minishell...${RESET}"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT_DIR)/$(LIBFT_NAME) -lreadline
	@echo "${GREEN}Minishell ready to use!${RESET}"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo -n "${BLUE}$@ ${RESET}"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "${YELLOW}Cleaning Minishell objects...${RESET}"
	@rm -f $(OBJS)
	@rm -rf $(OBJS_DIR)
	@echo "${RED}Files cleaned: $(OBJS)${RESET}"
	@cd $(LIBFT_DIR) && $(MAKE) clean
	@echo "${GREEN}Done.${RESET}"

fclean: clean
	@echo "${YELLOW}Cleaning Minishell program...${RESET}"
	@rm -f $(NAME)
	@echo "${RED}Files cleaned: $(NAME)${RESET}"
	@cd $(LIBFT_DIR) && $(MAKE) fclean
	@echo "${GREEN}Done.${RESET}"

re: fclean all

.PHONY: all clean fclean re