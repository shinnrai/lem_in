/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlst_toarr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofedorov <ofedorov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 14:59:54 by ofedorov          #+#    #+#             */
/*   Updated: 2017/09/19 13:35:11 by sasha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lstlen(t_list *lst)
{
	register int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char		**ft_strlst_toarr(t_list *lst)
{
	char	**arr;
	int		index;
	int		length;

	if (!lst)
		return (NULL);
	length = ft_lstlen(lst);
	arr = (char**)ft_memalloc(sizeof(char*) * (length + 1));
	arr[length] = NULL;
	index = 0;
	while (index < length)
	{
		arr[index] = ft_strdup(lst->content);
		index++;
		lst = lst->next;
	}
	return (arr);
}
