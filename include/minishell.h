/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hal <moel-hal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:05:12 by sferrad           #+#    #+#             */
/*   Updated: 2025/04/25 16:47:32 by moel-hal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*#################### INCLUDES ####################*/

# include "../libft/ft_printf/ft_printf.h"
# include "../libft/get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

/*###################### MACRO #######################*/

# define BUILTIN 1
# define CMD 2
# define F_OR_D 3
# define STRING 4
# define REDIRECT 5
# define PIPE 6

# define MAX_PIPES 1024
# define MAX_PROCESS 1024

# define TOKEN_CMD 1
# define TOKEN_ARG 2
# define TOKEN_PIPE 3
# define TOKEN_REDIR 4

/*#################### STRUCTURES ####################*/

typedef struct s_preprocessed_heredoc
{
	char							*delimiter;
	char							**content;
	struct s_preprocessed_heredoc	*next;
}									t_heredoc;

typedef enum e_token_type
{
	WORD,
	REDIR,
}									t_token_type;

typedef struct s_gc_node
{
	void							*ptr;
	struct s_gc_node				*next;
}									t_gc_node;

typedef struct s_gc_list
{
	t_gc_node						*head;
}									t_gc_list;

typedef struct s_token
{
	char							*arg;
	char							*str;
	int								type;
	struct s_token					*next;
}									t_token;

typedef struct s_env
{
	char							*key;
	char							*content;
	struct s_env					*next;
}									t_env;

typedef struct s_display_env
{
	t_env							*current;
	t_env							*sorted;
	t_env							*temp;
	t_env							*prev;
	t_env							*copy;
}									t_display_env;

typedef struct s_env_init
{
	t_env							*env;
	t_env							*new;
	char							*key;
	char							*content;
	char							*equal;
	int								i;
}									t_env_init;

typedef enum e_redir_type
{
	IN,
	OUT,
	HEREDOC,
	APPEND,
}									t_redir_type;

typedef struct s_redir
{
	char							*file;
	t_redir_type					type;
	char							**heredoc_content;
	struct s_redir					*next;
}									t_redir;

typedef struct s_command
{
	char							**arguments;
	t_redir							*redir;
	struct s_command				*next;
	int								pid;
}									t_command;

typedef struct s_mini
{
	t_gc_list						*gc;
	char							*buffer;
	size_t							buf_size;
	char							**args;
	char							**envp;
	t_token							*token_list;
	t_env							*env_list;
	int								is_arg;
	pid_t							pid;
	int								in_command;
	int								state;
	t_command						*command;
	t_env_init						*env_init;
	t_heredoc						*preprocessed_heredocs;
}									t_mini;

typedef struct s_expand
{
	char							*buffer;
	char							*var;
	char							*value;
	int								i;
	int								j;
	int								is_pid;
	t_mini							*mini;
	t_gc_list						*gc;
}									t_expand;

typedef struct s_parse_state
{
	char							**args;
	int								i;
	int								pipe_found;
}									t_parse_state;

/*#################### PROTOTYPES ####################*/

extern volatile sig_atomic_t		g_signal;

/* t_env */
t_env								*init_env(char **envp, t_gc_list *gc);
t_env								*env_new_node(char *key, char *content);

/* bool */
bool								is_builtin(char **arg);
bool								exec(t_command *cmd, t_mini *shell,
										t_gc_list *gc);
bool								tidying(t_mini *shell);
bool								is_env_valid(char c, bool start);
bool								handle_token(t_token **token,
										t_command *cmd, t_mini *shell);
bool								tidying(t_mini *shell);
bool								handle_argument(t_token **token,
										t_command *cmd, t_mini *shell);
bool								is_argument_token(t_token *token);

/* t_command */
t_command							*create_command_list(t_token *token_list,
										t_gc_list *gc, t_mini *shell);
t_command							*init_command_struct(t_token *token_start,
										t_gc_list *gc);
t_command							*create_single_command(t_token **token_ptr,
										t_gc_list *gc, t_mini *shell);
t_command							*init_command_struct(t_token *token_start,
										t_gc_list *gc);

t_command							*ft_commandnew(char **tabl, t_redir *redir,
										t_gc_list *gc);
t_command							*ft_commandlast(t_command *head);

/* t_token */
t_token								*ft_tokenadd_back(t_token **lst,
										t_token *new);
t_token								*tokenize(char **args, t_mini *shell,
										t_gc_list *gc);
t_token								*parsing(char *buffer, t_mini *mini,
										t_gc_list *gc);
t_token								*ft_lstnew_mini(char *arg, int type,
										t_gc_list *gc);
t_token								*create_token_by_type(char *arg,
										t_mini *shell, t_gc_list *gc);

/*t_redir*/

t_redir								*ft_redirnew(char *str, t_redir_type type,
										t_mini *shell);
t_redir_type						find_redir_type(char *str);
t_redir								*ft_redirlast(t_redir *head);

/* void */
void								print_token_type(int type);
void								gc_free_all(t_gc_list *gc);
void								*gc_malloc(size_t size, t_gc_list *gc);
void								free_args(t_mini *shell);
void								free_env_list(t_env *env);
void								cleanup_states(t_mini *shell);
void								env_add_back(t_env **env, t_env *new);
void								display_env(t_env *env, t_gc_list *gc);
void								init_states(t_mini *shell, char **envp);
void								condition_help_display(t_display_env *vars,
										t_gc_list *gc);
void								help_display_env(t_env *env,
										t_display_env *vars, t_gc_list *gc);
void								clear_buffers(t_mini *shell);
void								ft_signal(void);
void								set_signal_child(void);
void								excute(char **cmd, char **env,
										t_mini *minishell);
void								end_exec(char *path, char **cmd, char **env,
										t_mini *minishell);
void								error_msg(char *path, char **cmd,
										t_mini *minishell);
void								execut_me(t_command *cmd, t_mini *shell,
										int save[2], int fd[2]);
void								check_signal_exec(t_mini *minishell);
void								waiter(t_command *cmd, t_mini *minishell);
void								free_tab(char **tabl);
void								ft_envclear(t_env **env);
void								ft_redirclear(t_redir *redir);
void								ft_commandclear(t_command **cmd);
void								ft_tokenclear(t_token *token);
void								ft_end(t_mini *shell);
void								free_all_heredoc(t_command *cmd);
void								open_heredoc(t_redir *redir, t_mini *shell);
void								open_output(t_redir *redir, t_mini *shell);
void								open_input(t_redir *redir, t_mini *shell);
void								ft_tabupdate(t_mini *shell);
void								signal_handler(int sig);
void								restore_tokens(t_token *token_list);
void								append_heredoc_node(t_mini *shell,
										t_heredoc *new_node);
void								handle_redirections(t_token *token_start,
										t_command *cmd, t_gc_list *gc,
										t_mini *shell);
void								fill_command_arguments(t_command *cmd,
										t_token *token_start, t_gc_list *gc);

void								handle_redirection(t_token **token_ptr,
										t_command *cmd, t_gc_list *gc,
										t_mini *shell);
void								if_expand(t_mini *shell, char *expanded,
										int *i);
void								get_env_value(char *str, char *expanded,
										int *i, t_mini *shell);
void								free_tab(char **tabl);
void								ft_strncat(char *dst, const char *src,
										size_t size);
void								ft_rediraddback(t_redir **head,
										t_redir *new);
void								ft_commandaddback(t_command **head,
										t_command *new);
void								var_update(t_env **env_list, char *key,
										char *content);
void								restore_string(char *str, t_mini *shell);
void								free_split(char **result, int j);

/* char */
char								**split_pars(const char *s, t_gc_list *gc);
char								**gc_split(const char *str, char c,
										t_gc_list *gc);
char								*path_tracking(char *cmd, t_mini *shell,
										t_gc_list *gc);
char								*find_executable_path(char *cmd,
										char **paths, t_gc_list *gc);
char								**prepare_command_and_get_path(char *av,
										t_mini *shell, t_gc_list *gc);
char								**extract_args_from_token(t_token *token,
										int *arg_count, t_gc_list *gc);
char								**extract_args(t_token *token,
										int *arg_count, t_gc_list *gc);
char								*expand_vars(char *buffer, t_mini *mini,
										t_gc_list *gc);
char								*gc_strdup(const char *s, t_gc_list *gc);
char								*get_env_path(t_mini *shell, t_gc_list *gc);
char								*gc_substr(char const *s,
										unsigned int start, size_t len,
										t_gc_list *gc);
char								**handle_input(char *buffer, t_mini *mini,
										t_gc_list *gc);
char								*replace_var(t_expand *exp);
char								*cmd_finder(char **cmd, char **env);
char								*strip_quotes(char *str, t_gc_list *gc);
char								*while_expand(char *str, char *expanded,
										t_mini *shell);
char								*expand(char *str, t_mini *shell);
char								*get_value_env(char *key, t_env *env);
char								**add_argument(char **tabl, char *str,
										t_gc_list *gc);
char								*ft_strndup(const char *s, size_t n);

/* int */
int									ft_prompt(char **envp);
int									is_redirect(char *cmd);
int									pars_buff(char *buffer);
int									process_input(t_mini *shell, t_gc_list *gc);
int									ft_strcmp(char *s1, char *s2);
int									process_command(t_mini *shell,
										t_gc_list *gc);
int									verify_path(char *av, t_mini *shell,
										t_gc_list *gc);
int									handle_empty_input(t_mini *shell);
int									cmd_export(char **args, t_env **env_list,
										t_mini *shell);
int									handle_builtin(t_token *token,
										t_mini *shell, t_gc_list *gc);
int									is_valid_identifier(char *key);
int									handle_absolute_path(char *cmd,
										t_mini *shell);
int									print_error(char *cmd, char *msg, int ret);
int									ft_exit(char **args, t_gc_list *gc,
										t_mini *shell);
int									ft_cd(t_env **env, char *path,
										t_gc_list *gc, t_mini *shell);
int									ft_echo(t_env **env, char **args,
										t_mini *shell);
int									ft_unset(t_env **env, char *var,
										t_mini *shell);
int									ft_pwd(t_mini *shell);
int									printf_env(t_env *env, t_mini *shell);
int									handle_signal(t_mini *shell);
int									is_only_empty_quotes(char *buffer);
int									read_input(t_mini *shell);
int									handle_pid_expansion(t_expand *exp);
int									process_expansion(t_expand *exp);
int									process_var(t_expand *exp);
int									pars_buff_expand(t_expand *exp);
int									all_cmd(t_mini *minishell, int save[2],
										t_command *cmd);
int									open_redirections(t_command *cmd,
										t_mini *shell);
int									builtins(t_mini *shell, t_command *cmd,
										t_gc_list *gc);
int									sig_event(void);
int									handle_pipe_error(void);
int									handle_pipe_error_buff(void);
int									handle_syntax_error(char *buffer, int *i);
int									check_pipe(char *buffer, int *i);
int									check_redir(char *buffer, int *i);
int									check_quotes(char *buffer, int *i);
int									count_command_args(t_token *token);
int									exec_builtins(t_mini *shell, char **arg,
										t_gc_list *gc);
int									expand_variables(t_expand *exp);
int									handle_quotes(char c, int quote_state);
int									check_redirections(char *buffer, int *i);
int									check_pipe_syntax(char *buffer, int *i);
int									check_redir_syntax(char *buffer, int *i);
int									get_heredoc(t_redir *redir, t_mini *shell);
int									get_expanded_len(char *str, t_mini *shell);
int									get_value_len(char *key, t_env *env);
int									get_env_size(char *str, int *i,
										t_mini *shell);
int									change_quote(char quote, int i);
int									tab_len(char **tabl);
int									get_heredoc(t_redir *redir, t_mini *shell);
int									handle_assignment(char *arg,
										t_env **env_list, t_gc_list *gc);

int									handle_variable_lookup(char *arg,
										t_env **env_list);

#endif