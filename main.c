/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:07:34 by EClown            #+#    #+#             */
/*   Updated: 2022/03/08 19:19:05 by EClown           ###   ########.fr       */
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
	t_str	*cmd_tmp;

	ppx = get_t_pipex(argc, argv, envp);
	path_tmp = ppx->path;
	(void) argc; (void) argv; (void) envp; //TODO DELETE


	int child;
	int pipe_fd[2];
	char	*str = ft_strdup("ok");
	char	*buffer;
	int		read_count;

	pipe(pipe_fd);
	ppx->infile_fd = open(ppx->infile, O_RDONLY);
	ppx->outfile_fd = open(ppx->outfile_fd, O_WRONLY);
	buffer = malloc(128);

	child = fork();
	if (child != 0) //Parent
	{
		child = fork();
		if (child != 0) //Parent
		{

		}
		else //Child 2
		{
		}
	}
	else //Child 1
	{
		//TODO Останавился тут узнавать как работают STDIN и STDOUT
		dup2(ppx->infile_fd, stdin);
		dup2(pipe_fd, 0);
		execve(ppx->commands->value, argv, envp);
		
	}	
	return(0);
	
	while (path_tmp)
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
	clear_t_pipex(ppx);
	return (0);
}
