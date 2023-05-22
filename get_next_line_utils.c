/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterbach <nterbach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:42:51 by nterbach          #+#    #+#             */
/*   Updated: 2023/03/24 18:04:30 by nterbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
	Searches the given character array for a newline. It returns the index of 
	the first newline found or a -42 if there is none. If the pointer is NULL,
	then -1 is returned instead.
*/
int	search_nl(char *line)
{
	int	ndx;

		ndx = 0;
	if (line == NULL)
	{
		return (-1);
	}
	else
	{
		while (line[ndx] && line[ndx] != '\n')
		{
			ndx++;
		}
		if (line[ndx] == '\n')
		{
			return (ndx);
		}
		else
		{
			return (-42);
		}
	}
}

/*
	Returns the length of the given string pointed to by 'str'. If 'str' is a 
	null pointer, 0 is returned instead. Please note that this program also 
	returns a 0 if the length of 'str' is 0. Range is limited to int.
*/
int	c_strlen(char *str)
{
	int	ndx;

		ndx = 0;
	if (str != NULL)
	{
		while (str[ndx] != '\0')
		{
			ndx++;
		}
	}
	return (ndx);
}

/*
	Copies all contents of 'line' until a newline is copied.
	If 'line' doesn't contain any newlines, an exact copy is made.
	Memory is allocated for the resulting string, which is then returned.
	If 'line' is NULL, NULL is returned instead.
*/
char	*trim_rslt(char *line)
{
	char	*rslt;
	int		ndx;

		ndx = 0;
	if (line == NULL)
	{
		return (NULL);
	}
	while (line[ndx] && line[ndx] != '\n')
	{
		ndx++;
	}
	if (line[ndx] == '\0')
	{
		ndx--;
	}
	rslt = (char *) malloc(ndx + 2);
	if (rslt != NULL)
	{
		c_cpy(line, rslt);
	}
	return (rslt);
}

/*
	Copies the contents of 'line' into 'rslt' but stops after copying a
	newline if there is one. Guarantees null termination if there is enough
	space.
*/
void	c_cpy(char *line, char *rslt)
{
	int	ndx;

		ndx = 0;
	while (line[ndx] && line[ndx] != '\n')
	{
		rslt[ndx] = line[ndx];
		ndx++;
	}
	rslt[ndx] = line[ndx];
	if (line[ndx] == '\n')
	{
		rslt[ndx + 1] = '\0';
	}
}
