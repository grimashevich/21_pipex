/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:48:18 by EClown            #+#    #+#             */
/*   Updated: 2022/03/25 18:57:51 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clear_t_pipex(t_pipex *ppx)
{
	free(ppx->infile);
	free(ppx->outfile);
	free_text_list(&(ppx->commands));
	free_str_list(&(ppx->path));
	free(ppx);
}

int	is_file_executable(char *dir, char *file)
{
	char	*file_path;
	int		result;

	file_path = ft_strjoin(dir, file);
	result = 0;
	if (access(file_path, 1) == 0)
		result = 1;
	free(file_path);
	return (result);
}

int	update_commands2(t_pipex *ppx, t_text *cur_cmd)
{
	char	*tmp;
	t_str	*cur_path;
	int		file_ok;

	if (is_file_executable("", cur_cmd->value[0]))
		return (1);
	cur_path = ppx->path;
	file_ok = 0;
	while (cur_path)
	{
		if (is_file_executable(cur_path->value, cur_cmd->value[0]))
		{
			file_ok = 1;
			tmp = cur_cmd->value[0];
			cur_cmd->value[0] = ft_strjoin(cur_path->value, cur_cmd->value[0]);
			free(tmp);
			break ;
		}
		cur_path = cur_path->next;
	}
	return (file_ok);
}

int	update_commands(t_pipex *ppx)
{
	t_text	*cur_cmd;

	cur_cmd = ppx->commands;
	while (cur_cmd)
	{
		if (! update_commands2(ppx, cur_cmd))
			return (0);
		cur_cmd = cur_cmd->next;
	}
	return (1);
}

t_pipex	*get_t_pipex(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		i;

	pipex = malloc(sizeof(t_pipex));
	if (! pipex)
		return (NULL);
	pipex->infile = ft_strdup(argv[1]);
	pipex->outfile = ft_strdup(argv[argc - 1]);
	pipex->path = NULL;
	pipex->commands = NULL;
	pipex->path = get_path(envp);
	pipex->infile_fd = 0;
	pipex->outfile_fd = 0;
	pipex->commands_count = argc - 3;
	i = 2;
	pipex->commands = NULL;
	while (i < argc - 1)
		pipex->commands = add_text_to_list(
				create_text_item(argv[i++]), pipex->commands);
	if (! update_commands(pipex))
		error_exit("PIPEX: wrong command", pipex);
	return (pipex);
}
