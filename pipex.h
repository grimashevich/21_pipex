/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: EClown <eclown@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:38:10 by EClown            #+#    #+#             */
/*   Updated: 2022/03/07 20:33:11 by EClown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h> //TODO DELETE
# include <unistd.h>
# include <stdlib.h>

# define USLEEP_TIME 0

typedef struct s_str
{
	char			*value;
	struct s_str	*next;
}	t_str;

typedef struct pipex
{
	char	*infile;
	char	*outfile;
	t_str	*path;
	t_str	*commands;
}	t_pipex;


char	*ft_strdup(const char *s1);
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
t_str	*get_path(char **envp);
void	free_str_list(t_str **str_list);
t_str	*create_str_item(char *value, int need_dup);
t_str	*add_str_to_list(t_str *new_item, t_str *list_start);
void	cleat_t_pipex(t_pipex *ppx);
t_pipex	*get_t_pipex(int argc, char **argv, char **envp);
void	clear_t_pipex(t_pipex *ppx);
char	*ft_strjoin(char const *s1, char const *s2);

#endif