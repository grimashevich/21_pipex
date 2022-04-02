/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:07:34 by EClown            #+#    #+#             */
/*   Updated: 2022/04/02 16:24:37 by EClown           ###   ########.fr       */
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
	int		n;
	int		fd_in;
	int		fd_out;

	fd_in = get_fd_in(ppx, count);
	fd_out = get_fd_out(ppx, count);
	if (fd_out == -1)
		exit(1);
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	close_pipes_fd(ppx, -1, -1);
	if (count == 1 && ppx->stop_word)
		here_doc(ppx->stop_word);
	n = 1;
	while (n++ < count)
		ppx->commands = ppx->commands->next;
	if (ft_strncmp(ppx->commands->value[0], "exit", 5) == 0)
		do_exit_func(ppx->commands->value);
	if (! is_file_executable("", ppx->commands->value[0]))
		my_error(127, "pipex: command not found: ",
			ppx->commands->value[0], "\n");
	execve(ppx->commands->value[0], ppx->commands->value, envp);
}

void	here_doc(const char *stop_word)
{
	char	*buffer;
	int		read_len;
	int		stop_word_len;

	stop_word_len = ft_strlen(stop_word);
	buffer = malloc(stop_word_len + 2);
	while (1)
	{
		read_len = read(0, buffer, stop_word_len + 2);
		if (read_len - 1 == stop_word_len
			&& ft_strncmp(buffer, stop_word, read_len - 1) == 0)
			break ;
		write(1, buffer, read_len);
	}
	exit(0);
}

int	wait_children(t_pipex *ppx)
{
	int	n;
	int	i;
	int	result;
	int	status;

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
