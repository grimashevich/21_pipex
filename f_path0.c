/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_path0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 21:39:19 by EClown            #+#    #+#             */
/*   Updated: 2022/03/23 19:31:08 by EClown           ###   ########.fr       */
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

	if (*str_list == NULL)
		return ;
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

void	free_text_list(t_text **str_list)
{
	t_text	*cur_item;
	t_text	*prev_item;
	char	**value;

	if (*str_list == NULL)
		return ;
	cur_item = *str_list;
	while (cur_item)
	{
		prev_item = cur_item;
		cur_item = cur_item->next;
		value = prev_item->value;
		while (*value)
		{
			free(*value);
			value++;
		}
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

t_text	*create_text_item(char *value)
{
	t_text	*result;

	if (! value)
		return (NULL);
	result = malloc(sizeof(t_text));
	if (! result)
		return (NULL);
	result->next = NULL;
	result->value = ft_split(value, ' ');
	if (! result->value)
	{
		free(result);
		return (NULL);
	}
	return (result);
}
