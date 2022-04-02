/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:38:10 by EClown            #+#    #+#             */
/*   Updated: 2022/04/02 16:34:25 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define TMP_FILE_NAME ".tmp_file"
# define LLI_MIN "9223372036854775808"
# define LLI_MAX "9223372036854775807"

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# define USLEEP_TIME 0

typedef struct s_str
{
	char			*value;
	struct s_str	*next;
}	t_str;

typedef struct s_text
{
	char			**value;
	struct s_text	*next;
}	t_text;

typedef struct s_p_fd
{
	int				fd[2];
	struct s_p_fd	*next;
}	t_p_fd;

typedef struct s_pipex
{
	char		*infile;
	char		*outfile;
	t_str		*path;
	t_text		*commands;
	int			infile_fd;
	int			outfile_fd;
	int			commands_count;
	t_p_fd		*pipes;
	const char	*stop_word;
	int			exit_code;
	const char	*tmp_file_name;
	int			tmp_file_fd_wr;
	int			tmp_file_fd_rd;
	pid_t		last_pid;
}	t_pipex;

char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
t_str	*get_path(char **envp);
void	free_str_list(t_str **str_list);
t_str	*create_str_item(char *value, int need_dup);
t_str	*add_str_to_list(t_str *new_item, t_str *list_start);
void	cleat_t_pipex(t_pipex *ppx);
t_pipex	*get_t_pipex(int argc, char **argv, char **envp);
void	get_t_pipex2(int argc, char **argv, char **envp, t_pipex *pipex);
void	clear_t_pipex(t_pipex *ppx);
char	*ft_strjoin(char const *s1, char const *s2);
t_text	*add_text_to_list(t_text *new_item, t_text *list_start);
void	free_text_list(t_text **str_list);
t_text	*create_text_item(char *value);
void	error_exit(const char *msg, t_pipex *ppx);
void	free_str_array(char **arr);
void	*clear_pipe_fd_list(t_p_fd *list);
t_p_fd	*get_pipe_fd_list(int count);
int		get_fd_in(t_pipex *ppx, int count);
int		get_fd_out(t_pipex *ppx, int count);
void	close_pipes_fd(t_pipex *ppx, int exclude1, int exclude2);
void	here_doc(const char *stop_word);
void	ft_putstr_fd(char *s, int fd);
char	*str_join3(char *str1, char *str2, char *str3);
void	get_fd(t_pipex *ppx);
int		is_file_executable(char *dir, char *file);
int		wait_children(t_pipex *ppx);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		ft_isnumeric(char *str);
void	do_exit_func(char **command);
void	my_error(int exit_code, char *s1, char *s2, char *s3);
void	open_file_error(int fd);
void	get_fd(t_pipex *ppx);
int		update_commands2(t_pipex *ppx, t_text *cur_cmd);
int		update_commands(t_pipex *ppx);

#endif