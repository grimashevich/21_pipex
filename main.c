/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:07:34 by EClown            #+#    #+#             */
/*   Updated: 2022/04/01 16:31:44 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_work(t_pipex *ppx, int pipe_fd[2], char **envp)
{
	dup2(ppx->infile_fd, 0);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[0]);
	close(ppx->infile_fd);
	execve(ppx->commands->value[0], ppx->commands->value, envp);
	error_exit("PIPEX CHILD: execve error", ppx);
}

void	child_work_bonus(t_pipex *ppx, int count, char **envp)
{
	int	n;
	char	*error_msg;

	int fd_in = get_fd_in(ppx, count);
	int fd_out = get_fd_out(ppx, count);
	if (fd_out == -1)
		exit(1);
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	close_pipes_fd(ppx, -1, -1);
	if (count == 1 && ppx->stop_word)
	{
		here_doc(ppx->stop_word);
		exit(ppx->exit_code);
	}
	n = 1;
	while (n++ < count)
		ppx->commands = ppx->commands->next;
	if (ft_strncmp(ppx->commands->value[0], "exit", 5) == 0)
		do_exit_func(ppx->commands->value);
	if (! is_file_executable("", ppx->commands->value[0]))
	{
		error_msg = str_join3("pipex: command not found: ", ppx->commands->value[0], "\n");
		if (error_msg)
		{
			ft_putstr_fd(error_msg, 2);
			free(error_msg);
		}
		exit(127);
	}
	execve(ppx->commands->value[0], ppx->commands->value, envp);
}

void here_doc(const char *stop_word)
{
	char	*buffer;
	int		read_len;
	int		stop_word_len;

	stop_word_len = ft_strlen(stop_word);
	buffer = malloc(stop_word_len + 2);
	while (1)
	{
		read_len = read(0,  buffer, stop_word_len + 2);
		if (read_len - 1 == stop_word_len &&
				ft_strncmp(buffer, stop_word, read_len - 1) == 0)
			break;
		write(1, buffer, read_len);
	}
	close(0);
	close(1);
}

int wait_children(t_pipex *ppx)
{
	int	n;
	int	i;
	int result;
	int status;

	i = 1;
	n = 0;
	result = -1;
	if (ppx->stop_word)
		i = 2;
	waitpid(ppx->last_pid, &status, 0);
	while (i++ < ppx->commands_count)
		waitpid(0, &n, 0);
	
	if (WIFEXITED(status)) 
		result = WEXITSTATUS(status);
	return (result);
}

void open_file_error(int fd)
{
	if (fd == -1)
		perror("pipex");
}

void	get_fd(t_pipex *ppx)
{
	if (! ppx->stop_word)
	{
		ppx->infile_fd = open(ppx->infile, O_RDONLY);
		open_file_error(ppx->infile_fd);
		ppx->outfile_fd = open(ppx->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		open_file_error(ppx->outfile_fd);
	}
	else
	{
		ppx->infile_fd = dup(0);
		ppx->outfile_fd = open(ppx->outfile, O_WRONLY | O_CREAT |O_APPEND, 0664);
		open_file_error(ppx->outfile_fd);
		ppx->tmp_file_fd_wr = open(ppx->tmp_file_name,
				O_WRONLY | O_CREAT | O_TRUNC, 0664); 
		ppx->tmp_file_fd_rd = open(ppx->tmp_file_name, O_RDONLY, 0664); 
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*ppx;
	int		count;

	if (argc < 5)
		error_exit("PIPEX: arguments count must be >= 4", NULL);
	ppx = get_t_pipex(argc, argv, envp);
	get_fd(ppx);
	ppx->pipes = get_pipe_fd_list(argc - 4);
	count = 0;

	while (count++ < argc - 3)
	{
		if (count == 2 && ppx->stop_word)
			wait(NULL);
		ppx->last_pid = fork();
		if (ppx->last_pid == 0)
			child_work_bonus(ppx, count, envp);
	}
	close_pipes_fd(ppx, -1, -1);
	ppx->exit_code = wait_children(ppx);
	if (ppx->stop_word)
		unlink(TMP_FILE_NAME);
	exit(ppx->exit_code);
}
