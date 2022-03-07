/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_path0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 21:39:19 by EClown            #+#    #+#             */
/*   Updated: 2022/03/07 20:35:49 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_str_array(char **arr)
{
	char	**cur_str;

	cur_str = arr;
	while (*cur_str)
	{
		free(*cur_str);
		cur_str++;
	}
	free(arr);	
}

void	free_str_list(t_str **str_list)
{
	t_str	*cur_item;
	t_str	*prev_item;

	cur_item = *str_list;
	while (cur_item)
	{
		prev_item = cur_item;
		cur_item = cur_item->next;
		free(prev_item->value);
		free(prev_item);
	}
	*str_list = NULL;
}

t_str	*create_str_item(char *value, int need_dup)
{
	t_str	*result;

	if (! value)
		return (NULL);
	result = malloc(sizeof(t_str));
	if (! result)
		return (NULL);
	result->next = NULL;
	if (need_dup)
		result->value = ft_strdup(value);
	else
		result->value = value;
	if (! result->value)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

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

t_str	*get_path(char **envp)
{
	char	**path_var;
	char	**path_vars;
	t_str	*result;

	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			break;
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
			create_str_item(ft_strjoin(*path_var, "/"), 0), result );
		path_var++;
	}
	free_str_array(path_vars);
	return (result);
}
