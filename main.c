/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:07:34 by EClown            #+#    #+#             */
/*   Updated: 2022/03/26 12:52:43 by EClown           ###   ########.fr       */
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

/* 	dup2(get_fd_in(ppx, count), 0);
	dup2(get_fd_out(ppx, count), 1); */
	
	
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	close_pipes_fd(ppx, -1, -1);
	n = 1;
	while (n++ < count)
		ppx->commands = ppx->commands->next;
	execve(ppx->commands->value[0], ppx->commands->value, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*ppx;
	pid_t	child;
	int		count;

	if (argc < 5)
		error_exit("PIPEX: arguments count must be >= 4", NULL);
	ppx = get_t_pipex(argc, argv, envp);

	ppx->infile_fd = open(ppx->infile, O_RDONLY);
	ppx->outfile_fd = open(ppx->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (ppx->infile_fd == -1 || ppx->outfile_fd == -1)
		error_exit("PIPEX: file access error", ppx);
	ppx->pipes = get_pipe_fd_list(argc - 4);
	count = 0;
	while (count++ < argc - 3)
	{
		child = fork();
		if (child == 0)
			child_work_bonus(ppx, count, envp);
	}
	close_pipes_fd(ppx, -1, -1);
	printf("DONE!\n");

	return (0);
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
	 */
}
