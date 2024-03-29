/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:07:31 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/25 17:34:45 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_command
{
	char				**cmd;
	char				**redir;
	struct s_command	*next;
}	t_command;

typedef struct s_tocken
{
	char			*begin;
	char			*end;
	struct s_tocken	*next;
}	t_tocken;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	char		*input;
	t_command	*cmd;
	t_env		*env_lst;
	pid_t		*pr_id;
	int			pipes_nb;
	int			cmd_nb;
	int			**pipe_fds;
	int			fd_inp;
	int			fd_outp;
	int			exit_status;
	char		*exit_c;
	size_t		len;
	char		**new_envp;
}	t_data;

void		minishell(t_data *data);
t_command	*parse_input(t_data *data);
t_tocken	*get_tockens(char *str);
int			is_whitespace(char c);
int			find_next_del(char *str);
char		**create_arr_for(t_tocken *lst, char type);
void		add_cmd(t_command **lst, t_command *node);
void		free_tockns_lst(t_tocken *lst);
int			is_pipe(t_tocken *tkn);
int			is_redir(t_tocken *tkn);
int			is_redir_str(char *str);
void		*malloc_error(void);
void		free_array(int **arr, int size);
void		free_command_lst(t_command *cmd);
int			count_pipes(t_command *lst);
int			execute(char **cmd, char *envp[]);
char		**get_path(char *envp[]);
char		*ft_strcat(char *str1, char *str2);
char		*file_name(char *str);
char		*get_delim(char *str);
void		open_pipes(t_data *data);
void		close_pipes(t_data *data);
void		process_command(t_data *data);
int			check_cmd(t_data *data, char **arr);
int			write_heredoc(t_data *data, char *str);
t_tocken	*new_tocken(void);
int			get_offset(t_tocken *tkn, char *str, int size);
char		*copy_redir(t_tocken *tkn);
char		*copy_content(t_tocken *tkn);
char		**get_command(t_tocken *lst);
char		**get_redir(t_tocken *lst);
void		*clean_up(t_command *res, t_data *data, t_tocken *tockns_ptr);
void		close_pipes_free(t_data *data);
void		ft_fork(t_data *data, char **cmd, pid_t *pr_id);
int			input_fd(char *redir, t_data *data);
int			output_fd(char *redir, t_data *data);
int			ft_dup2(int fd, int st_fd);
void		restore_fds(t_data *data);
int			check_check(t_data *data, pid_t *pr_id, char **cmd, int error);

#endif
