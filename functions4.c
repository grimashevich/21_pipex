/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:24:15 by EClown            #+#    #+#             */
/*   Updated: 2022/04/02 16:33:09 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_file_error(int fd)
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
		ppx->outfile_fd = open(ppx->outfile, O_WRONLY | O_CREAT
				| O_TRUNC, 0664);
		open_file_error(ppx->outfile_fd);
	}
	else
	{
		ppx->infile_fd = dup(0);
		ppx->outfile_fd = open(ppx->outfile, O_WRONLY | O_CREAT
				|O_APPEND, 0664);
		open_file_error(ppx->outfile_fd);
		ppx->tmp_file_fd_wr = open(ppx->tmp_file_name,
				O_WRONLY | O_CREAT | O_TRUNC, 0664);
		ppx->tmp_file_fd_rd = open(ppx->tmp_file_name, O_RDONLY, 0664);
	}
}

t_pipex	*get_t_pipex(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		i;

	pipex = malloc(sizeof(t_pipex));
	if (! pipex)
		return (NULL);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		pipex->stop_word = argv[2];
	else
		pipex->stop_word = NULL;
	get_t_pipex2(argc, argv, envp, pipex);
	i = 2;
	pipex->commands = NULL;
	while (i < argc - 1)
		pipex->commands = add_text_to_list(
				create_text_item(argv[i++]), pipex->commands);
	update_commands(pipex);
	return (pipex);
}

void	get_t_pipex2(int argc, char **argv, char **envp, t_pipex *pipex)
{
	pipex->infile = ft_strdup(argv[1]);
	pipex->outfile = ft_strdup(argv[argc - 1]);
	pipex->path = NULL;
	pipex->commands = NULL;
	pipex->path = get_path(envp);
	pipex->infile_fd = 0;
	pipex->outfile_fd = 0;
	pipex->commands_count = argc - 3;
	pipex->exit_code = 0;
	pipex->tmp_file_name = TMP_FILE_NAME;
	pipex->tmp_file_fd_wr = -1;
	pipex->tmp_file_fd_rd = -1;
	pipex->last_pid = 0;
}
