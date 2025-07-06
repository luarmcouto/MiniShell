/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luamonteiro <luamonteiro@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:07:58 by luamonteiro       #+#    #+#             */
/*   Updated: 2025/06/30 16:53:53 by luamonteiro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    Getwd(char *buf)
{
    if (NULL == getwd(buf))
        perror("getwd failed");
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
        buf = NULL;

        if (feof(stdin))
            printf("[EOF]");
        else
            printf("getline failed");

        printf("%s inputfunction ON \n", buf);
    }
    printf("end function");
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
        pause();
    }

    return (0);
}