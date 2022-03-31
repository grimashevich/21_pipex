/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:25:12 by EClown            #+#    #+#             */
/*   Updated: 2022/03/31 18:35:03 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_spc(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static char	*clear_digit(char *s)
{
	int		i;
	int		j;
	char	*result;

	result = malloc(ft_strlen(s) + 1);
	if (! result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]))
			result[j++] = s[i];
		i++;
	}
	while (j <= i)
		result[j++] = 0;
	return (result);
}

static int	return_clear(void *p, int res)
{
	if (p)
		free(p);
	p = NULL;
	return (res);
}

static int	is_overlong(char *s, int sign)
{
	char	*border_int;
	int		result;
	size_t	border_size;

	border_size = ft_strlen(LLI_MIN);
	if (ft_strlen(s) < border_size)
		return (return_clear(s, 0));
	else if (ft_strlen(s) > border_size)
		return (return_clear(s, sign));
	if (sign > 0)
		border_int = LLI_MAX;
	else
		border_int = LLI_MIN;
	result = ft_strncmp(s, border_int, border_size);
	if (result > 0)
		return (return_clear(s, sign));
	return (return_clear(s, 0));
}

int	ft_atoi(const char *str)
{
	int				i;
	short int		sign;
	int				res;
	int				overlong;

	i = 0;
	sign = 1;
	res = 0;
	while (is_spc(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	overlong = is_overlong(clear_digit((char *) &(str[i])), sign);
	if (! ft_isdigit(str[i]) || overlong < 0)
		return (0);
	else if (overlong > 0)
		return (-1);
	while ((str[i] >= 48 && str[i] <= 57))
		res = res * 10 + (str[i++] - 48) * sign;
	return ((int) res);
}
