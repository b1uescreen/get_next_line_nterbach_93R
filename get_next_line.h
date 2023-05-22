/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterbach <nterbach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:42:07 by nterbach          #+#    #+#             */
/*   Updated: 2023/03/24 18:06:09 by nterbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 81
# endif
# include <stdlib.h>
# include <unistd.h>

extern char	*get_next_line(int fd);
extern char	*read_line(char *line, int fd, int *status);
extern char	*extend(char *line, char *bffr, int *status);
extern char	*fusion(char *line, char *bffr, char *xt_line);
extern char	*trim_rslt(char *line);
extern char	*update(char *line, int *status);
extern int	search_nl(char *line);
extern int	c_strlen(char *str);
extern void	c_cpy(char *line, char *rslt);

#endif
