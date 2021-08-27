/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 16:29:05 by ctirions          #+#    #+#             */
/*   Updated: 2021/08/27 20:38:47 by ctirions         ###   ########.fr       */
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

void	exec(char *argv, char **env)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (execve(pathfinder(cmd[0], env), cmd, env) == -1)
		ft_error();
}

void	begin_pipe(char **argv, char **env, int *fd)
{
	int inputfd;

	inputfd = open(argv[1], O_RDONLY, 0777);
	if (inputfd == -1)
		ft_error();
	dup2(fd[1], STDOUT_FILENO);
	dup2(inputfd, STDIN_FILENO);
	close(fd[0]);
	exec(argv[2], env);
}

void	end_pipe(char **argv, char **env, int *fd)
{
	int	outputfile;

	outputfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outputfile == -1)
		ft_error();
	dup2(fd[0], STDIN_FILENO);
	dup2(outputfile, STDOUT_FILENO);
	close(fd[1]);
	exec(argv[3], env);
}

int main(int argc, char **argv, char **env)
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