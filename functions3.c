/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:25:42 by EClown            #+#    #+#             */
/*   Updated: 2022/04/02 16:59:05 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	ft_isnumeric(char *str)
{
	if (str == NULL || *str == 0)
		return (0);
	if (*str == '-')
		str++;
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}

void	do_exit_func(char **command)
{
	char	*err_msg;
	int		exit_code;

	if (command[1] == NULL)
		exit(10);
	if (! ft_isnumeric(command[1]))
	{
		err_msg = str_join3("pipex: exit: ", command[1],
				": numeric argument required");
		perror(err_msg);
		free(err_msg);
		exit(255);
	}
	if (command[2] != NULL)
	{
		err_msg = ft_strjoin("pipex: ", "exit: too many arguments");
		perror(err_msg);
		free(err_msg);
		exit(1);
	}
	exit_code = ft_atoi(command[1]) % 256;
	exit(exit_code);
}

void	my_error(int exit_code, char *s1, char *s2, char *s3)
{
	char	*msg;

	if (s1 == NULL)
		exit(exit_code);
	if (s2 == NULL)
	{
		ft_putstr_fd(s1, 2);
		exit(exit_code);
	}
	if (s3 == NULL)
		msg = ft_strjoin(s1, s2);
	else
		msg = str_join3(s1, s2, s3);
	if (msg != NULL)
	{
		ft_putstr_fd(msg, 2);
		free(msg);
	}
	exit(exit_code);
}
