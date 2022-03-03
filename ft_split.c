/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:25:12 by EClown            #+#    #+#             */
/*   Updated: 2022/03/03 21:46:22 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	get_split_count(const char *s, char c)
{
	size_t	i;
	size_t	result;

	if (s == NULL || *s == 0)
		return (0);
	i = 0;
	result = 0;
	if (s[i] != c && s[i] != 0)
		result++;
	i++;
	while (s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			result++;
		i++;
	}
	return (result);
}

static int	*get_words_len(const char *s, char c, size_t size)
{
	size_t	cnt[2];
	int		*result;

	result = ft_calloc(size * 2, sizeof(int));
	if (! result)
		return (NULL);
	cnt[0] = 0;
	cnt[1] = 0;
	while (s[cnt[0]] == c)
		cnt[0]++;
	result[0] = (int) cnt[0];
	while (s[cnt[0]] && cnt[1] < size * 2)
	{
		if (s[cnt[0]] != c && cnt[1] > 0 && result[cnt[1]] == 0)
			result[cnt[1]] = (int) cnt[0];
		else if (s[cnt[0]] == c && s[cnt[0] - 1] != c)
		{
			result[cnt[1] + 1] = (int) cnt[0] - 1;
			cnt[1] += 2;
		}
		cnt[0]++;
	}
	if (result[size * 2 - 1] == 0)
		result[size * 2 - 1] = (int) cnt[0] - 1;
	return (result);
}

static void	*clear_memory(void **s, void *l)
{
	int	i;

	if (l)
		free(l);
	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i])
				free(s[i++]);
		}
		free(s);
	}
	return (NULL);
}

char	**ft_split_sub(size_t cnt[], int *words_len, char **result, \
														const char *s)
{
	size_t	j;

	while (cnt[1] < cnt[0])
	{
		result[cnt[1]] = malloc(words_len[cnt[1] * 2 + 1] - \
				words_len[cnt[1] * 2] + 2);
		if (! result[cnt[1]])
			return (clear_memory((void **) result, words_len));
		result[cnt[1]][words_len[cnt[1] * 2 + 1] - \
						words_len[cnt[1] * 2] + 1] = 0;
		j = words_len[cnt[1] * 2];
		while ((int) j <= words_len[cnt[1] * 2 + 1])
		{
			result[cnt[1]][j - words_len[cnt[1] * 2]] = s[j];
			j++;
		}
		cnt[1]++;
	}
	free(words_len);
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		*words_len;
	size_t	cnt[2];

	if (s == NULL)
		return (NULL);
	cnt[0] = get_split_count(s, c);
	words_len = 0;
	if (cnt[0] > 0)
		words_len = get_words_len(s, c, cnt[0]);
	result = malloc(sizeof(char *) * (cnt[0] + 1));
	if (! result)
		return (NULL);
	cnt[1] = 0;
	while (cnt[1] < cnt[0] + 1)
		result[cnt[1]++] = 0;
	result[cnt[0]] = NULL;
	cnt[1] = 0;
	return (ft_split_sub(cnt, words_len, result, s));
}
