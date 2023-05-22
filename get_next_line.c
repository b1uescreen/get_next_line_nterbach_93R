/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterbach <nterbach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:42:01 by nterbach          #+#    #+#             */
/*   Updated: 2023/03/24 18:54:59 by nterbach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*line;
	char		*rslt;
	int			*status;
	int			error;

		error = 0;
		status = &error;
	if (fd < 0 || BUFFER_SIZE < 1)
	{
		return (NULL);
	}
	line = read_line(line, fd, status);
	rslt = trim_rslt(line);
	line = update(line, status);
	if (*status == -1)
	{
		free(line);
		line = NULL;
		free(rslt);
		rslt = NULL;
	}
	return (rslt);
}

/*
	Reads from the file descriptor until a newline was read, the end of file
	was reached or something went wrong. NULL is returned to indicate errors.
	'line' is dynamically extended to contain the whole line that was read 
	(likely plus some characters of the following line).
	If the memory allocation of 'bffr' fails, 'status' is set to -1 so that
	everything that needs to be freed can be freed later. My functions are
	robust enough to handle malloc-failures.
*/
char	*read_line(char *line, int fd, int *status)
{
	char	*bffr;
	int		bytes_read;

		bytes_read = 42;
		bffr = (char *) malloc(BUFFER_SIZE + 1);
	if (bffr == NULL)
	{
		*status = -1;
		return (NULL);
	}
	while (search_nl(line) < 0 && bytes_read > 0)
	{
		bytes_read = read(fd, bffr, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			bffr[bytes_read] = '\0';
			line = extend(line, bffr, status);
		}
		else if (bytes_read < 0)
			*status = -1;
	}
	free(bffr);
	bffr = NULL;
	return (line);
}

/*
	Merges the recently read characters (bffr) with all previous ones (line).
	Returns NULL if the memory allocation failed. Additionally, the status
	is set to -1 to let "get_next_line" know that it has to return NULL.
*/
char	*extend(char *line, char *bffr, int *status)
{
	char	*temp;
	char	*xt_line;

		xt_line = NULL;
		temp = (char *) malloc(c_strlen(line) + c_strlen(bffr) + 1);
	if (temp != NULL)
	{
		xt_line = fusion(line, bffr, temp);
	}
	else
	{
		*status = -1;
	}
	free(line);
	line = NULL;
	return (xt_line);
}

/*
	This function copies the contents of 'line' (if any) and copies them to 
	'xt_line'. It then appends the content of 'bffr' to 'xt_line'. 
	'xt_line' will be null terminated but won't contain any other nullbytes.
	'fusion' still works if 'line' is a null pointer - it copies only the
	contents of 'bffr' in that case.
*/
char	*fusion(char *line, char *bffr, char *temp)
{
	size_t	ndx_bffr;
	size_t	ndx_line;

		ndx_bffr = 0;
		ndx_line = 0;
	if (line != NULL)
	{
		while (line[ndx_line])
		{
			temp[ndx_line] = line[ndx_line];
			ndx_line++;
		}
	}
	while (bffr[ndx_bffr])
	{
		temp[ndx_line] = bffr[ndx_bffr];
		ndx_bffr++;
		ndx_line++;
	}
	temp[ndx_line] = '\0';
	return (temp);
}

/*
	This function checks if there are characters past the newline in 'line'.
	If so, then those are copied to a new string that is then returned.
	The return is NULL if there were no characters (other than nullbytes) or
	if the memory allocation failed. In that case, 'status' is also set to -1
	so that "get_next_line" returns NULL.
*/
char	*update(char *line, int *status)
{
	char	*updated;
	int		offset;
	int		ndx;

		updated = NULL;
		offset = search_nl(line) + 1;
		ndx = 0;
	if (offset >= 1 && (c_strlen(line) - offset) > 0)
	{
		updated = (char *) malloc((c_strlen(line) - offset) + 1);
		if (updated != NULL)
		{
			while (line[offset + ndx])
			{
				updated[ndx] = line[offset + ndx];
				ndx++;
			}
			updated[ndx] = '\0';
		}
		else
			*status = -1;
	}
	free(line);
	return (updated);
}
