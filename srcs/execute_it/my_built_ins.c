/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_built_ins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:48:02 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/12 15:37:50 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	my_echo(t_tree *tree)
{
	int	i;
	int	pid;

	i = 1;
	pid = fork();
	if (pid == 0)
	{
		redirect_it (tree, 1);
		if (!tree->cmd_node->args[1])
			return ;
		while (!ft_strcmp(tree->cmd_node->args[i], "-n"))
			i++;
		i--;
		while (tree->cmd_node->args[++i])
		{
			if (tree->cmd_node->args[i + 1])
				printf("%s ", tree->cmd_node->args[i]);
			else
				printf("%s", tree->cmd_node->args[i]);
		}
		if (ft_strcmp(tree->cmd_node->args[1], "-n"))
			printf("\n");
		exit(0);
	}
	waitpid(pid, NULL, 0);
}

void	my_cd(t_tree *tree)
{
	redirect_it(tree, 0);
	if (!tree->cmd_node->args[1])
		return ;
	if (chdir(tree->cmd_node->args[1]))
	{
		write(2, "our@shell: cd: ", 11);
		perror(tree->cmd_node->args[1]);
	}
}

void	my_exit(t_tree *tree)
{
	redirect_it(tree, 0);
	exit(0);
}

void	my_pwd(t_tree *tree)
{
	char	cwd[512];
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		redirect_it(tree, 1);
		getcwd(cwd, sizeof(cwd));
		printf("%s\n", cwd);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}
char **my_env_to_array(t_my_env **my_env) {
    int size = 0;
    int i = 0;
    t_my_env *current = *my_env;
    while (current != NULL) 
	{
        size++;
        current = current->next;
    }
    char **envp = (char **) malloc((size + 1) * sizeof(char *));
    current = *my_env;
    while (current != NULL) 
	{
        envp[i] = current->val;
        current = current->next;
        i++;
    }
    envp[size] = NULL;
    return envp;
}

void update_or_add_my_env_node(t_my_env **my_env, char *ljadid)
{
	t_my_env	*tmp;
	t_my_env	*head;
	int i = 0;
	int j = 0;
	int k = 0;
	int m = 0;
	int fl = 0;
	int plus =0;
	head = *my_env;
	tmp = *my_env;
	while (tmp != NULL)
	{
		i = 0;
		while(tmp->val[i])
		{
			k = 0;
			j = 0;
			plus =0;
			m = 0;
			if(tmp->val[i + 1] == '\0' && tmp->val[i] == ljadid[i])
			{
				k = 200;
				j = 100;
			}
			if(ljadid[i + 1] == '\0' && tmp->val[i] == ljadid[i])
				return;
			else if(tmp->val[i] == '=' && ljadid[i - 1] == tmp->val[i - 1])
			{
				plus = 0;
				m = 0;
				while(plus == 0 && tmp->val[m])
				{	if(tmp->val[m] == '=')
						plus++;
					if(tmp->val[m] != ljadid[m])
					{
						m = 100; 
						break;
					}
					m++;
				}
				if(m == 100)
				{
					free(tmp->val);
					tmp->val = ft_strdup(ljadid);
				}
			}
			if(j == 100 || fl == 10)
			{
				free(tmp->val);
				tmp->val = ft_strdup(ljadid);
			}
			i++;
		}
		tmp = tmp->next;
	}
	if(k == 200)
		return;
	// key not found, add new node to linked list
	t_my_env *new_node = malloc(sizeof(t_my_env));
	if (!new_node)
		exit(1);
	new_node->val = ft_strdup(ljadid);
	new_node->next = NULL;
	if (head == NULL)
	{
		*my_env = new_node;
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = new_node;
	}
}



//-----------------------------------------------------------------------------|
//-----------------------------------------------------------------------------|
//-----------------------------------------------------------------------------|
void	my_export(t_tree *tree, t_my_env **my_env)
{
	char **en_tmp;
	if(tree->cmd_node->args[1] == NULL)
	{
		int i = 0;
		en_tmp = my_env_to_array(my_env);
		en_tmp = exp_no_opt(en_tmp);
		while(en_tmp[i])
		{
			printf("%s\n", en_tmp[i]);
			i++;
		}
		free(en_tmp);
	}
	else
	{
		update_or_add_my_env_node(my_env, tree->cmd_node->args[1]);
		print_envs(*my_env);
	}
}

void	my_unset(t_tree *tree, char **env)
{
	
}
//-----------------------------------------------------------------------------|
//-----------------------------------------------------------------------------|
//-----------------------------------------------------------------------------|

void	call_built_in(t_tree *tree, t_my_env **my_env)
{
	if (!ft_strcmp(tree->cmd_node->args[0], "echo"))
		my_echo(tree);
	else if (!ft_strcmp(tree->cmd_node->args[0], "cd"))
		my_cd (tree);
	else if (!ft_strcmp(tree->cmd_node->args[0], "exit"))
		my_exit (tree);
	else if (!ft_strcmp(tree->cmd_node->args[0], "pwd"))
		my_pwd (tree);
	else if (!ft_strcmp(tree->cmd_node->args[0], "export"))
		my_export (tree, my_env);
	// else if (!ft_strcmp(tree->cmd_node->args[0], "unset"))
	// 	my_unset (tree, env);

	
}


int	is_built_in(t_tree *tree)
{
	if (!*tree->cmd_node->args)
		return (0);
	if (!ft_strcmp(tree->cmd_node->args[0], "cd") || !ft_strcmp(tree->cmd_node->args[0], "echo")
		|| !ft_strcmp(tree->cmd_node->args[0], "exit") || !ft_strcmp(tree->cmd_node->args[0], "pwd")
		|| !ft_strcmp(tree->cmd_node->args[0], "export") || !ft_strcmp(tree->cmd_node->args[0], "unset"))
		return (1);
	return (0);
}

