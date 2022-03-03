/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:38:10 by EClown            #+#    #+#             */
/*   Updated: 2022/03/03 22:35:06 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>

# define USLEEP_TIME 0

typedef struct s_path
{
	char			*value;
	struct s_path	*next;
}	t_path;

char	*ft_strdup(const char *s1);
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);

#endif