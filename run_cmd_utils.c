/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:35:16 by kdzhoha           #+#    #+#             */
/*   Updated: 2024/02/25 17:29:15 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*file_name(char *str)
{
	char	*res;
	int		i;

	i = 0;
	if (str[0] == str[1])
		i = 2;
	else
		i = 1;
	while (str[i] && is_whitespace(str[i]))
		i++;
	res = &str[i];
	return (res);
}

char	*get_delim(char *str)
{
	char	*res;
	int		i;

	i = 2;
	res = NULL;
	while (is_whitespace(str[i]))
		i++;
	if (str[i])
		res = &str[i];
	return (res);
}

void	open_pipes(t_data *data)
{
	int	**pp_fds;
	int	*p_fds;
	int	i;

	pp_fds = NULL;
	pp_fds = (int **)malloc(data->pipes_nb * sizeof(int *));
	if (!pp_fds)
		malloc_error();
	i = 0;
	while (i < data->pipes_nb)
	{
		p_fds = (int *)malloc(2 * sizeof(int));
		if (!p_fds)
			malloc_error();
		if (pipe(p_fds) == -1)
		{
			put_error(data, "Pipe open failed", errno);
			return ;
		}
		pp_fds[i] = p_fds;
		i++;
	}
	data->pipe_fds = pp_fds;
	return ;
}

void	close_pipes(t_data *data)
{
	int	**fds;
	int	i;
	int	j;

	if (!data->pipe_fds)
		return ;
	fds = data->pipe_fds;
	i = 0;
	while (i < data->pipes_nb)
	{
		j = 0;
		while (j < 2)
		{
			if (close(fds[i][j]) == -1)
				j++;
			else
				j++;
		}
		i++;
	}
}

void	close_pipes_free(t_data *data)
{
	if (data->pipe_fds != NULL)
	{
		close_pipes(data);
		free_array(data->pipe_fds, data->pipes_nb);
	}
}
