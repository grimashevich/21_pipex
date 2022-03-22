/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:07:34 by EClown            #+#    #+#             */
/*   Updated: 2022/03/22 20:08:46 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //TODO удалить
#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc < 3)
	{
		printf("Error (argc < 3)\n");
		return (1);
	}
	t_pipex	*ppx;
	t_str	*path_tmp;
	/* t_str	*cmd_tmp; */

	ppx = get_t_pipex(argc, argv, envp);
	path_tmp = ppx->path;
	(void) argc; (void) argv; (void) envp; //TODO DELETE


	pid_t child;
	pid_t child2;
	int status;
	int pipe_fd[2];

	pipe(pipe_fd);
	ppx->infile_fd = open(ppx->infile, O_RDONLY);
	ppx->outfile_fd = open(ppx->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);

	child = fork();
	if (child != 0) //Parent
	{
		child2 = fork();
		close(pipe_fd[1]);
		if (child2 != 0) //Parent
		{
			close(pipe_fd[0]);
			printf("Start main process...\n");
			//waitpid(child, &status, 0);
			waitpid(child, &status, 0);
			printf("Child 1 is closed...\n");
			waitpid(child2, &status, 0);
			printf("Child 2 is closed...\n");
			printf("done!!!\n");
			return (0);
		}
		else //Child 2
		{
			printf("Child 2 starting...\n");
			dup2(pipe_fd[0], 0);
			dup2(ppx->outfile_fd, 1);
			//printf("Trying to start: %s %s\n", ppx->commands->next->value[0], ppx->commands->next->value[1]);
			execve(ppx->commands->next->value[0], ppx->commands->next->value, envp);
		}
	}
	else // Child 1 (process 1)
	{
		printf("Child 1 starting...\n");
		//dup2(ppx->infile_fd, 0);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[0]);
		//close(pipe_fd[0]);
		//close(pipe_fd[1]);
		//close(ppx->infile_fd);
		execve(ppx->commands->value[0], ppx->commands->value, envp);
		printf("Child 1 print some text\n");
		exit(0);
	}
	
/* 	while (path_tmp)
	{
		printf("%s\n", path_tmp->value);
		path_tmp = path_tmp->next;
	}
	cmd_tmp = ppx->commands;
	printf("- - - - - - - - - \n");
	while (cmd_tmp)
	{
		printf("%s\n", cmd_tmp->value);
		cmd_tmp = cmd_tmp->next;
	}
	clear_t_pipex(ppx); */
	return (0);
}
