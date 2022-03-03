/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 21:39:19 by EClown            #+#    #+#             */
/*   Updated: 2022/03/03 22:01:04 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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

int	ft_strlen(const char *s)
{
	unsigned int	result;

	result = 0;
	while (*(s++) != 0)
		result++;
	return (result);
}