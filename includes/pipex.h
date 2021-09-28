/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 16:27:12 by ctirions          #+#    #+#             */
/*   Updated: 2021/09/28 16:32:08 by ctirions         ###   ########.fr       */
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

char	*pathfinder(char *cmd, char **env);
void	ft_error(int flag);

#endif