/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:07:34 by EClown            #+#    #+#             */
/*   Updated: 2022/03/28 21:08:47 by EClown           ###   ########.fr       */
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

	int fd_in = get_fd_in(ppx, count);
	int fd_out = get_fd_out(ppx, count);
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	close_pipes_fd(ppx, -1, -1);
	n = 1;
	while (n++ < count)
		ppx->commands = ppx->commands->next;
	execve(ppx->commands->value[0], ppx->commands->value, envp);
}

void here_doc(int out_fd, const char *stop_word)
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
		write(out_fd, buffer, read_len);
	}
	close(out_fd);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*ppx;
	pid_t	child;
	int		count;

	if (argc < 5)
		error_exit("PIPEX: arguments count must be >= 4", NULL);
	ppx = get_t_pipex(argc, argv, envp);

	if (! ppx->stop_word)
		ppx->infile_fd = open(ppx->infile, O_RDONLY);
	else
		ppx->infile_fd = dup(0);

	if (ppx->stop_word == NULL)
		ppx->outfile_fd = open(ppx->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else
		ppx->outfile_fd = open(ppx->outfile, O_WRONLY | O_APPEND, 0664);

	if (ppx->infile_fd == -1 || ppx->outfile_fd == -1)
		error_exit("PIPEX: file access error", ppx);
	
	ppx->pipes = get_pipe_fd_list(argc - 4);
	count = 0;
	while (count++ < argc - 3)
	{
		if (count == 1 && ppx->stop_word)
			continue;
		child = fork();
		if (child == 0)
			child_work_bonus(ppx, count, envp);
	}
	if (ppx->stop_word)
	{
		dup2(get_fd_in(ppx, 1), 0);
		dup2(get_fd_out(ppx, 1), 1);
		here_doc(get_fd_out(ppx, 1), ppx->stop_word);
	}
	close_pipes_fd(ppx, -1, -1);
	// printf("DONE!\n");
	exit(0);
/* 
	pipe(pipe_fd);
	ppx->infile_fd = open(ppx->infile, O_RDONLY);
	ppx->outfile_fd = open(ppx->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (ppx->infile_fd == -1 || ppx->outfile_fd == -1)
		error_exit("PIPEX: file access error", ppx);
	child = fork();
	if (child == 0)
		child_work(ppx, pipe_fd, envp);
	dup2(pipe_fd[0], 0);
	dup2(ppx->outfile_fd, 1);
	close(pipe_fd[1]);
	close(ppx->outfile_fd);
	execve(ppx->commands->next->value[0], ppx->commands->next->value, envp);
	 
	 ./pipex infile "grep pe" wc outfile
	 %       4      35     251
	 
	 ./pipex here_doc 0 cat wc outfile
	 */
}
