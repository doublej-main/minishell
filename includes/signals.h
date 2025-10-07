/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahdekiv <vahdekiv@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:37:52 by vahdekiv          #+#    #+#             */
/*   Updated: 2025/10/02 17:37:55 by vahdekiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

/*
** Includes
*/
# include <signal.h>
# include <termios.h>

/*
** Prototypes
*/
void	signals_interactive(void);
void	signals_default(void);
void	disable_echoctl(void);
void	set_sigaction(int sig, void (*handler)(int), int flags);
void	signals_heredoc(void);
void	signals_init(void);

#endif
