/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaaskel <jjaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:17:02 by jjaaskel          #+#    #+#             */
/*   Updated: 2025/09/29 17:41:32 by jjaaskel         ###   ########.fr       */
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