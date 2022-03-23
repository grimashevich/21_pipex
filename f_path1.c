/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_path1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:31:15 by EClown            #+#    #+#             */
/*   Updated: 2022/03/23 19:31:25 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_str	*add_str_to_list(t_str *new_item, t_str *list_start)
{
	t_str	*cur_item;

	if (new_item == NULL)
		return (list_start);
	if (list_start == NULL)
		return (new_item);
	cur_item = list_start;
	while (cur_item->next)
		cur_item = cur_item->next;
	cur_item->next = new_item;
	return (list_start);
}

t_text	*add_text_to_list(t_text *new_item, t_text *list_start)
{
	t_text	*cur_item;

	if (new_item == NULL)
		return (list_start);
	if (list_start == NULL)
		return (new_item);
	cur_item = list_start;
	while (cur_item->next)
		cur_item = cur_item->next;
	cur_item->next = new_item;
	return (list_start);
}

t_str	*get_path(char **envp)
{
	char	**path_var;
	char	**path_vars;
	t_str	*result;

	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			break ;
		envp++;
	}
	if (! *envp)
		return (NULL);
	path_vars = ft_split((*envp) + 5, ':');
	path_var = path_vars;
	result = NULL;
	while (*path_var)
	{
		result = add_str_to_list(
				create_str_item(ft_strjoin(*path_var, "/"), 0), result);
		path_var++;
	}
	free_str_array(path_vars);
	return (result);
}
