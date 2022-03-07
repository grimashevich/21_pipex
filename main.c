/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:07:34 by EClown            #+#    #+#             */
/*   Updated: 2022/03/07 21:52:05 by EClown           ###   ########.fr       */
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


	(void) argc;
	(void) argv;
	(void) envp;
	ppx = get_t_pipex(argc, argv, envp);
	path_tmp = ppx->path;
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
