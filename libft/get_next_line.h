/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:38:44 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/07/29 15:49:08 by jjaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
/*define BUFFER_SIZE if not defined*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
/*define OPEN_MAX if not defined*/
# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif
/*includes*/
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
/*get_next_line_utils*/
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
/*get_next_line*/
char	*get_next_line(int fd);
char	*extract_line(char *ptr);
char	*trim_stash(char **stash);
char	*ft_strjoin_free(char *s1, char *s2);
void	gnl_free(char **s);

#endif