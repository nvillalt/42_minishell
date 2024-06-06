/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:49:09 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/06 16:51:18 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

typedef struct sigaction	t_sigaction;
void	set_child_signals(void);
void	ignore_signals(void);
void	set_signals(void);
void	heredoc_signals(void);

#endif