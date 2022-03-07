/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fucntions1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 20:25:42 by EClown            #+#    #+#             */
/*   Updated: 2022/03/07 20:25:58 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*null_return(char *s1, char *s2)
{
	if (! s1 && ! s2)
		return (NULL);
	if (!s1)
		return (s2);
	return (s1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*result;

	if (! s1 || ! s2)
		return (null_return((char *) s1, (char *) s2));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = malloc(s1_len + s2_len + 1);
	if (! result)
		return (NULL);
	i = 0;
	while (i < s1_len || i < s2_len)
	{
		if (i < s1_len)
			result[i] = s1[i];
		if (i < s2_len)
			result[i + s1_len] = s2[i];
		i++;
	}
	result[s1_len + s2_len] = 0;
	return (result);
}
