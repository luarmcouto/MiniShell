/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luarodri <luarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:07:58 by luamonteiro       #+#    #+#             */
/*   Updated: 2025/06/30 17:40:09 by luarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    Getwd(char *buf)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    if (NULL == getwd(buf))
        perror("getwd failed");
#pragma GCC diagnostic pop
}
char    *input_read_line(void)
{
    char    *buf;
    char    cwd[BUFSIZ];
    size_t  buffsize;

    buf = NULL;

    Getwd(cwd);
    printf("🐚  %s  🐚 $>", cwd);
    
    if (getline(&buf, &buffsize, stdin) == -1)
    {
        free(buf);
        if (feof(stdin))
            printf("\n[EOF]\n");
        else
            perror("getline failed");
        return (NULL);
    }
    return (buf);
}

int main(int argc, char *argv[], char *envp[])
{
    (void)argc;
    (void)argv;
    (void)envp;
    char    *line;

    while ((line = input_read_line()))
    {
        printf("%s \n", line);
        free(line);
    }

    return (0);
}