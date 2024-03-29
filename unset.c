/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohladkov <ohladkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:41:14 by ohladkov          #+#    #+#             */
/*   Updated: 2024/02/22 11:56:39 by ohladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

/*    input[0]  [1]  [2]
unset var1 var2 var3 */
void	unset(t_data *data, char **input)
{
	int	i;

	data->exit_status = 0;
	i = 0;
	while (input[++i])
	{
		if (env_isvar_name(data, input[i]))
			ft_delnode_env(&data->env_lst, input[i]);
	}
}
