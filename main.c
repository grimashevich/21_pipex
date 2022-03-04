/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:07:34 by EClown            #+#    #+#             */
/*   Updated: 2022/03/04 19:02:12 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //TODO удалить
#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_str	*path;

	(void) argc;
	(void) argv;
	path = get_path(envp);
	while (path)
	{
		printf("%s\n", path->value);
		path = path->next;
	}
}
