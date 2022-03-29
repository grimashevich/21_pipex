/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:48:18 by EClown            #+#    #+#             */
/*   Updated: 2022/03/29 20:11:35 by EClown           ###   ########.fr       */
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
	if (! file_ok)
		ppx->exit_code = 127;
	return (file_ok);
}

int	update_commands(t_pipex *ppx)
{
	t_text	*cur_cmd;
	int		i;

	i = 0;
	cur_cmd = ppx->commands;
	while (cur_cmd)
	{
		if (i == 0 && ppx->stop_word != NULL)
		{
			cur_cmd = cur_cmd->next;
			i++;
			continue;
		}
		update_commands2(ppx, cur_cmd);
		cur_cmd = cur_cmd->next;
		i++;
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
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		pipex->stop_word = argv[2];
	else
		pipex->stop_word = NULL;
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
	i = 2;
	pipex->commands = NULL;
	while (i < argc - 1)
		pipex->commands = add_text_to_list(
				create_text_item(argv[i++]), pipex->commands);
	update_commands(pipex);
	return (pipex);
}
