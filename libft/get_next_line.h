/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 19:08:06 by fmoran-m          #+#    #+#             */
/*   Updated: 2023/10/31 19:45:14 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H 
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42 
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include "libft.h"

char			*get_next_line(int fd);
char			*ft_strjoin_gnl(char *s1, char *s2);
size_t			ft_strlen_gnl(char *s);
char			*ft_strdup_gnl(char *s1);
char			*free_file(char **file);
#endif
