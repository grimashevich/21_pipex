/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mandatory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:07:34 by EClown            #+#    #+#             */
/*   Updated: 2022/03/28 19:56:59 by EClown           ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*ppx;
	int		pipe_fd[2];
	pid_t	child;

	if (argc != 5)
		error_exit("PIPEX: 4 arguments expected", NULL);
	ppx = get_t_pipex(argc, argv, envp);
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
	execve(ppx->commands->next->value[0], ppx->commands->next->value, envp);
}
