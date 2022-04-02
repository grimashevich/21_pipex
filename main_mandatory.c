/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mandatory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:07:34 by EClown            #+#    #+#             */
/*   Updated: 2022/04/02 18:17:33 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_work(t_pipex *ppx, int pipe_fd[2], char **envp)
{
	dup2(ppx->infile_fd, 0);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[0]);
	close(ppx->infile_fd);
	if (ft_strncmp(ppx->commands->value[0], "exit", 5) == 0)
		do_exit_func(ppx->commands->value);
	if (! is_file_executable("", ppx->commands->value[0]))
		my_error(127, "pipex: command not found: ",
			ppx->commands->value[0], "\n");
	execve(ppx->commands->value[0], ppx->commands->value, envp);
	my_error(1, "pipex CHILD: execve error: ", ppx->commands->value[0], NULL);
}

void	child_work2(t_pipex *ppx, int pipe_fd[2], char **envp)
{
	if (ppx->outfile_fd == -1)
		exit(1);
	dup2(pipe_fd[0], 0);
	dup2(ppx->outfile_fd, 1);
	close(pipe_fd[1]);
	if (ft_strncmp(ppx->commands->next->value[0], "exit", 5) == 0)
		do_exit_func(ppx->commands->next->value);
	if (! is_file_executable("", ppx->commands->next->value[0]))
		my_error(127, "pipex: command not found: ",
			ppx->commands->next->value[0], "\n");
	execve(ppx->commands->next->value[0], ppx->commands->next->value, envp);
	my_error(1, "pipex CHILD: execve error: ", ppx->commands->next->value[0],
		NULL);
}

void	main_exit(int child2)
{
	int	result;
	int	status;
	int	n;

	n = 0;
	result = -1;
	waitpid(child2, &status, 0);
	waitpid(0, &n, 0);
	if (WIFEXITED(status))
		result = WEXITSTATUS(status);
	exit(result);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*ppx;
	int		pipe_fd[2];
	pid_t	child;
	pid_t	child2;

	if (argc != 5)
		my_error(1, "PIPEX: 4 arguments expected", NULL, NULL);
	ppx = get_t_pipex(argc, argv, envp);
	pipe(pipe_fd);
	ppx->infile_fd = open(ppx->infile, O_RDONLY);
	open_file_error(ppx->infile_fd);
	ppx->outfile_fd = open(ppx->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	open_file_error(ppx->outfile_fd);
	child = fork();
	if (child == 0)
		child_work(ppx, pipe_fd, envp);
	child2 = fork();
	if (child2 == 0)
		child_work2(ppx, pipe_fd, envp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	main_exit(child2);
}
