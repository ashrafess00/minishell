/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_built_ins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kslik <kslik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:48:02 by aessaoud          #+#    #+#             */
/*   Updated: 2023/05/21 17:17:35 by kslik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	my_echo(t_tree *tree, int *exit_code)
{
	int	i;
	int	pid;
	int	status;

	i = 1;
	pid = fork();
	if (pid == -1)
	{
		perror("Fork Error");
		*exit_code = 1;
	}
	if (pid == 0)
	{
		redirect_it (tree, 1);
		if (!tree->cmd_node->args[1])
		{
			printf("\n");
			exit(0);
		}
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
	waitpid(pid, &status, 0);
	*exit_code = WEXITSTATUS(status);
}

void	my_cd(t_tree *tree, int *exit_code)
{
	redirect_it(tree, DONT_REDIRECT);
	if (!tree->cmd_node->args[1])
		return ;
	if (chdir(tree->cmd_node->args[1]))
	{
		write(2, "our@shell: cd: ", 11);
		perror(tree->cmd_node->args[1]);
		*exit_code = 1;
		return ;
	}
	*exit_code = 0;
}

void	my_exit(t_tree *tree)
{
	redirect_it(tree, DONT_REDIRECT);
	exit(0);
}

void	my_pwd(t_tree *tree, int *exit_code)
{
	char	cwd[512];
	int		pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		redirect_it(tree, REDIRECT);
		getcwd(cwd, sizeof(cwd));
		printf("%s\n", cwd);
		exit(0);
	}
	waitpid(pid, &status, 0);
	*exit_code = WEXITSTATUS(status);
}

char **my_env_to_array(t_my_env **my_env) 
{
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
	int si = 0;
	int ps =0;
	head = *my_env;
	tmp = *my_env;
	while (tmp != NULL)
	{
		i = 0;
		ps = 0;
		si = 0;
		while(tmp->val[i])
		{
			ps = 0;
			si = 0;
			if(tmp->val[i + 1] == '\0' && tmp->val[i] == ljadid[i])
			{
				k = 200;
				tmp->val = ft_strdup(ljadid);
				break;
			}
			if(tmp->val[i + 1] == '\0' && tmp->val[i] == ljadid[i])
			{
				fl = 0;
				while(tmp->val[fl] != '=' && si == 0 && tmp->val[fl])
				{
					if(tmp->val[fl] != ljadid[fl])
						si = 10;
					fl++;
				}
				if(si != 10)
					return;
			}
			else if(tmp->val[i] == '=')
			{
				fl = 0;
				while(ljadid[fl] != '=' && ljadid[fl])
				{
					if(tmp->val[fl] != ljadid[fl])
						ps = 10;
					fl++;
				}
				if(tmp->val[fl] != '=')
					ps = 10;
				if(ps != 10)
				{
					k = 200;
					free(tmp->val);
					tmp->val = ft_strdup(ljadid);
				}
				break;
			}
			i++;
		}
		tmp = tmp->next;
	}
	if(k == 200)
	{
		return;
	}
	t_my_env *new_node = malloc(sizeof(t_my_env));
	if (!new_node)
		exit(1);
	new_node->val = ft_strdup(ljadid);
	new_node->next = NULL;
	if (head == NULL)
		*my_env = new_node;
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = new_node;
	}
}

int ex_err(char *cmd, int c)
{
	int i = 0;
	if(cmd[0] == '=' || cmd[0] == '$')
	{
		if(c == 2)
			printf(" export \'%s\' : not a valid identifier\n", cmd);
		return(0);
	}
	if(!((cmd[0] >= 97 && cmd[0] <= 122) || (cmd[0] >= 65 && cmd[0] <= 90)))
	{
		if(c == 2)
			printf(" export \'%s\' : not a valid identifier\n", cmd);
		return(0);
	}
	while(cmd[i] != '=')
		i++;
	i = i - 1;
	if(!((cmd[i] >= 97 && cmd[i] <= 122) || (cmd[i] >= 65 && cmd[i] <= 90)))
		return(0);
	return (1);
}
int unset_err(char *cmd)
{
	int i = 0;
	while(cmd[i] != '\0')
	{
		if(!((cmd[i] >= 97 && cmd[i] <= 122) || (cmd[i] >= 65 && cmd[i] <= 90)))
		{
			printf(" export \'%s\' : not a valid identifier\n", cmd);
			return(0);
		}
		i++;
	}
	return (1);
}
//-----------------------------------------------------------------------------|
//-----------------------------------------------------------------------------|
//-----------------------------------------------------------------------------|
void	my_export(t_tree *tree, t_my_env **my_env, int *exit_code)
{
	char **en_tmp;
	int i = 0;
	int c = 0;
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
		free_arr(en_tmp);
	}
	else
	{
		while(tree->cmd_node->args[i] != NULL)
			i++;
		c = i;
		i = 1;
		while(tree->cmd_node->args[i] != NULL)
		{
			if(ex_err(tree->cmd_node->args[i], c) == 1)
				update_or_add_my_env_node(my_env, tree->cmd_node->args[i]);
			else
				*exit_code = 1;
			i++;
		}
	}
	*exit_code = 0;
}
void freeNode(t_my_env *node)
{
    free(node->val);
    free(node);
}
void deleteNode(t_my_env **my_env, char *key)
{
    t_my_env *tmp;
    t_my_env *prev = NULL;
    tmp = *my_env;
	int i;
	int si;
    while (tmp != NULL) 
	{
        i = -1;
        si = 0;
        while (tmp->val[++i]) 
		{
            if (tmp->val[i] == '=') 
			{
                int q = 0;
                while (tmp->val[q] != '=' && si == 0) 
				{
                    if (tmp->val[q] != key[q])
                        si = 10;
                    q++;
                }
				if(key[q] != '\0')
					si = 10;
                if (si != 10)
                    break;
            }
        }
        if (si != 10) 
		{
            if (prev == NULL) 
			{
                *my_env = tmp->next;
				freeNode(tmp);
                tmp = *my_env;
            } 
			else 
			{
                prev->next = tmp->next;
				freeNode(tmp);
                tmp = prev->next;
            }
        }
		else 
		{
            prev = tmp;
            tmp = tmp->next;
		}
    }
}

void	my_unset(t_tree *tree, t_my_env **my_env, int *exit_code)
{
	int i = 1;
	while(tree->cmd_node->args[i] != NULL)
	{
		if(unset_err(tree->cmd_node->args[i]) == 1)
			deleteNode(my_env, tree->cmd_node->args[i]);
		else
			*exit_code = 1;
		i++;
	}
	// print_envs(*my_env); 
}
//-----------------------------------------------------------------------------|
//-----------------------------------------------------------------------------|
//-----------------------------------------------------------------------------|

void	call_built_in(t_tree *tree, t_my_env **my_env, int *exit_code)
{
	if (!ft_strcmp(tree->cmd_node->args[0], "echo"))
		my_echo(tree, exit_code);
	else if (!ft_strcmp(tree->cmd_node->args[0], "cd"))
		my_cd (tree, exit_code);
	else if (!ft_strcmp(tree->cmd_node->args[0], "exit"))
		my_exit (tree);
	else if (!ft_strcmp(tree->cmd_node->args[0], "pwd"))
		my_pwd (tree, exit_code);
	else if (!ft_strcmp(tree->cmd_node->args[0], "export"))
		my_export (tree, my_env, exit_code);
	else if (!ft_strcmp(tree->cmd_node->args[0], "unset"))
		my_unset (tree, my_env, exit_code);
}


int	is_built_in(t_tree *tree)
{
	if (!tree->cmd_node->args || !*tree->cmd_node->args)
		return (0);
	if (!ft_strcmp(tree->cmd_node->args[0], "cd") || !ft_strcmp(tree->cmd_node->args[0], "echo")
		|| !ft_strcmp(tree->cmd_node->args[0], "exit") || !ft_strcmp(tree->cmd_node->args[0], "pwd")
		|| !ft_strcmp(tree->cmd_node->args[0], "export") || !ft_strcmp(tree->cmd_node->args[0], "unset"))
		return (1);
	return (0);
}


