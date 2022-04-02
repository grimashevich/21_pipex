/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:25:42 by EClown            #+#    #+#             */
/*   Updated: 2022/04/02 16:22:33 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_fd_in(t_pipex *ppx, int count)
{
	t_p_fd	*tmp;
	int		n;

	if (count == 1)
	{
		if (ppx->stop_word)
			return (0);
		return (ppx->infile_fd);
	}
	else if (count == 2 && ppx->stop_word)
		return (ppx->tmp_file_fd_rd);
	n = 2;
	tmp = ppx->pipes;
	while (n++ < count)
		tmp = tmp->next;
	return (tmp->fd[0]);
}

int	get_fd_out(t_pipex *ppx, int count)
{
	t_p_fd	*tmp;
	int		n;

	if (count == 1 && ppx->stop_word)
		return (ppx->tmp_file_fd_wr);
	if (count == ppx->commands_count)
		return (ppx->outfile_fd);
	n = 1;
	tmp = ppx->pipes;
	while (n++ < count)
		tmp = tmp->next;
	return (tmp->fd[1]);
}

void	close_pipes_fd(t_pipex *ppx, int exclude1, int exclude2)
{
	t_p_fd	*current;

	current = ppx->pipes;
	while (current)
	{
		if (current->fd[0] != exclude1 && current->fd[0] != exclude2)
			close(current->fd[0]);
		if (current->fd[1] != exclude1 && current->fd[1] != exclude2)
			close(current->fd[1]);
		current = current->next;
	}
	if (ppx->tmp_file_fd_rd >= 0)
		close(ppx->tmp_file_fd_rd);
	if (ppx->tmp_file_fd_wr >= 0)
		close(ppx->tmp_file_fd_wr);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, &s[0], ft_strlen(s));
}

char	*str_join3(char *str1, char *str2, char *str3)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(str1, str2);
	if (! tmp)
		return (NULL);
	result = ft_strjoin(tmp, str3);
	free(tmp);
	return (result);
}
