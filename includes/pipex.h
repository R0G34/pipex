/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abausa-v <abausa-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:28:05 by abausa-v          #+#    #+#             */
/*   Updated: 2024/03/30 16:28:07 by abausa-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

// Estructura para manejar los datos necesarios
typedef struct s_pipex
{
    int     pipefd[2];
    int     infile;
    int     outfile;
    char    *cmd1;
    char    *cmd2;
    pid_t   child1;
    pid_t   child2;
}           t_pipex;

// Declaraciones de funciones
void    child_process1(t_pipex pipex);
void    child_process2(t_pipex pipex);
void    exit_error(void);
void    custom_error(char *header, char *msg);
void    free_split(char **str);
char    *get_cmd_path(char *cmd, char **envp);
char    *ft_strjoin_free(char *s1, char *s2, int free_s1);
void    run_cmd(char *cmd, char **envp);
void    handle_error(const char *msg, int fd1, int fd2);

#endif
