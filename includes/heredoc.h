/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:36:50 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/15 13:44:47 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

typedef struct s_shell	t_shell;
typedef struct s_redir	t_redir;
typedef struct s_pl		t_pl;
typedef struct s_arena	t_arena;

int						hd_loop(int fd, const char *delim, t_shell *shell,
							int expand);
int						heredoc_prepare_all(t_shell *shell);
void					heredoc_cleanup_all(t_pl *pl);
char					*hd_path_heap(unsigned int count, t_arena *arena);
int						hd_open_tmp(t_arena *arena, char **path_out);
char					*strip_quotes(t_arena *arena, const char *s);
char					*spliceline(t_shell *shell, char *line, char *key);
int						count_expanse(char *str);

#endif
