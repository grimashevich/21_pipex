/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 21:39:19 by EClown            #+#    #+#             */
/*   Updated: 2022/03/31 18:45:31 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	unsigned int	result;

	result = 0;
	while (*(s++) != 0)
		result++;
	return (result);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*tmp;

	tmp = malloc(count * size);
	if (tmp == 0)
		return (0);
	ft_bzero(tmp, count * size);
	return (tmp);
}

void	ft_bzero(void *s, size_t n)
{
	while (n)
		((char *) s)[(n--) - 1] = 0;
}

char	*ft_strdup(const char *s1)
{
	char	*result;
	int		s1_size;
	int		i;

	s1_size = ft_strlen(s1) + 1;
	i = 0;
	result = malloc(s1_size);
	if (! result)
		return (NULL);
	while (i < s1_size)
	{
		result[i] = s1[i];
		i++;
	}
	return (result);
}
