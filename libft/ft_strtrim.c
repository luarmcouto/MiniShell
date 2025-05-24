/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwietzke <iwietzke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 20:46:05 by iwietzke          #+#    #+#             */
/*   Updated: 2024/05/22 15:42:03 by iwietzke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	i;
	size_t	len;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	len = ft_strlen(s1) - 1;
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (s1[len] && ft_strchr(set, s1[len]))
		len--;
	trimmed = ft_substr(s1, i, len - i + 1);
	return (trimmed);
}
/*
int	main(void)
{
    char str[] = "---Internacional-";
    char set[] = "-";

    char *trimmed_str = ft_strtrim(str, set);

    if (trimmed_str != NULL)
    {
        printf("String original: %s\n", str);
        printf("String trimada: %s\n", trimmed_str);
        free(trimmed_str);
    }
    else
        printf("Erro\n");
	//cc ft_strtrim.c ft_strchr.c ft_substr.c
	//ft_strlcpy.c ft_strlen.c ft_strdup.c
    return (0);
}*/