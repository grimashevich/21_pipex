/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_path0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 21:39:19 by EClown            #+#    #+#             */
/*   Updated: 2022/03/04 00:05:38 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>


void	free_path(t_path **path)
{
	t_path	*cur_item;
	t_path	*prev_item;

	cur_item = *path;
	while (cur_item)
	{
		prev_item = cur_item;
		cur_item = cur_item->next;
		free(prev_item->value);
		free(prev_item);
	}
	*path = NULL;
}

t_path	*create_path_item(char *value)
{
	t_path	*result;

	if (! value)
		return (NULL);
	result = malloc(sizeof(t_path));
	if (! result)
		return (NULL);
	result->next = NULL;
	result->value = ft_strdup(value);
	if (! result->value)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

t_path	*get_path(char **envp)
{
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	// TODO Останавился тут
}