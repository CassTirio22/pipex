/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:35:20 by ctirions          #+#    #+#             */
/*   Updated: 2021/09/28 17:02:41 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	begin_pipe(char **argv, char **env, int *fd)
{
	int	inputfd;

	inputfd = open(argv[1], O_RDONLY, NULL);
	if (inputfd == -1)
		ft_error(1);
	dup2(fd[1], STDOUT_FILENO);
	dup2(inputfd, STDIN_FILENO);
	close(fd[0]);
	exec(argv[2], env);
}

void	end_pipe(char **argv, char **env, int *fd)
{
	int	outputfile;

	outputfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, NULL);
	if (outputfile == -1)
		ft_error(1);
	dup2(fd[0], STDIN_FILENO);
	dup2(outputfile, STDOUT_FILENO);
	close(fd[1]);
	exec(argv[3], env);
}

void	exec(char *argv, char **env)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (execve(pathfinder(cmd[0], env), cmd, env) == -1)
		ft_error(1);
}
