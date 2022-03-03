/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:07:34 by EClown            #+#    #+#             */
/*   Updated: 2022/03/03 21:38:56 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //TODO удалить
#include "pipex.h"

int main (int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	
}