/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 22:44:36 by luamonteiro       #+#    #+#             */
/*   Updated: 2025/10/06 11:04:45 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *str, char c)
{
	int		start;
	int		end;
	int		len;
	char	*trimmed;
	int		i;

	if (!str)
		return (NULL);
	start = 0;
	end = ft_strlen(str) - 1;
	while (str[start] && str[start] == c)
		start++;
	while (end >= start && str[end] == c)
		end--;
	len = end - start + 1;
	if (len <= 0)
		return (ft_strdup(""));
	trimmed = malloc((len + 1) * sizeof(char));
	if (!trimmed)
		return (NULL);
	i = -1;
	while (++i < len)
		trimmed[i] = str[start + i];
	trimmed[i] = '\0';
	return (trimmed);
}
