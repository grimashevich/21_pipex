/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:25:42 by EClown            #+#    #+#             */
/*   Updated: 2022/03/26 12:21:45 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*null_return(char *s1, char *s2)
{
	if (! s1 && ! s2)
		return (NULL);
	if (!s1)
		return (s2);
	return (s1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*result;

	if (! s1 || ! s2)
		return (null_return((char *) s1, (char *) s2));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = malloc(s1_len + s2_len + 1);
	if (! result)
		return (NULL);
	i = 0;
	while (i < s1_len || i < s2_len)
	{
		if (i < s1_len)
			result[i] = s1[i];
		if (i < s2_len)
			result[i + s1_len] = s2[i];
		i++;
	}
	result[s1_len + s2_len] = 0;
	return (result);
}

void	error_exit(const char *msg, t_pipex *ppx)
{
	if (ppx != NULL)
		clear_t_pipex(ppx);
	perror(msg);
	exit(1);
}

void	*clear_pipe_fd_list(t_p_fd *list)
{
	t_p_fd	*prev;

	while (list)
	{
		prev = list;
		list = list->next;
		free(prev);
	}
	return (NULL);
}

t_p_fd	*get_pipe_fd_list(int count)
{
	t_p_fd	*first;
	t_p_fd	*current;

	first = malloc(sizeof(t_p_fd));
	if (! first)
		return (NULL);
	current = first;
	pipe(first->fd);
	first->next = NULL;
	while (count-- > 1)
	{
		current->next = malloc(sizeof(t_p_fd));
		if (! current->next)
			return clear_pipe_fd_list(first);
		current = current->next;
		current->next = NULL;
		pipe(current->fd);
	}
	return (first);
}

int get_fd_in(t_pipex *ppx, int count)
{
	t_p_fd	*tmp;
	int		n;

	if (count == 1)
		return (ppx->infile_fd);
	n = 2;
	tmp = ppx->pipes;
	while (n++ < count)
		tmp = tmp->next;
	return (tmp->fd[0]);
}

int get_fd_out(t_pipex *ppx, int count)
{
	t_p_fd	*tmp;
	int		n;

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
		if (current->fd[0] !=  exclude1 && current->fd[0] != exclude2)
			close(current->fd[0]);
		if (current->fd[1] !=  exclude1 && current->fd[1] != exclude2)
			close(current->fd[1]);
		current = current->next;
	}
}
