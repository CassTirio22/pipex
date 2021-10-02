/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 16:27:12 by ctirions          #+#    #+#             */
/*   Updated: 2021/10/02 16:44:25 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*
**    INCLUDES
*/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../libft/includes/libft.h"

/*
**    PROTOTYPES
*/

void	exec(char *argv, char **env);
void	begin_pipe(char **argv, char **env, int *fd);
void	end_pipe(char **argv, char **env, int *fd);

pid_t	init_pid(void);
void	free_my_lst(char **lst);
char	*pathfinder(char *cmd, char **env);
void	ft_error(int flag);

#endif