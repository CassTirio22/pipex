/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 16:29:05 by ctirions          #+#    #+#             */
/*   Updated: 2021/09/11 12:43:17 by ctirions         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error(void)
{
	perror("Error !\n");
	exit(EXIT_FAILURE);
}

char	*pathfinder(char *cmd, char **env)
{
	char	**paths;
	char	*part_path;
	char	*path;
	int		i;

	i = -1;
	while (!ft_strnstr(env[++i], "PATH", 4))
		;
	paths = ft_split(env[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free (part_path);
		if (!access(path, F_OK))
			return (path);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	int	pid;

	argc++;
	if (pipe(fd) == -1)
		ft_error();
	pid = fork();
	if (pid == -1)
		ft_error();
	if (!pid)
		begin_pipe(argv, env, fd);
	waitpid(pid, 0, 0);
	end_pipe(argv, env, fd);
	close(fd[0]);
	close(fd[1]);
	return (0);
}
