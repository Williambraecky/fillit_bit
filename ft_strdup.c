/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 08:21:49 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/06/12 13:51:29 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *str)
{
	char	*dup;
	size_t	strlen;

	strlen = ft_strlen(str) + 1;
	dup = (char *)malloc(sizeof(char) * (strlen));
	if (dup == NULL)
		return (NULL);
	while (strlen--)
		dup[strlen] = str[strlen];
	return (dup);
}
