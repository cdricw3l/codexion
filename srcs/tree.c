/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 20:49:46 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/28 22:09:42 by cdric.b          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void display_tree(t_request *root)
{
    if(!root)
        return;

    display_tree(root->left);
    display_tree(root->right);
    display_request(*root);
}
/* get_tree_size - 1  is the size of the binary tree */
int count_tree_node(t_request *root, int size)
{
    if(!root)
        return (1);
    return (count_tree_node(root->left, size + 1) + count_tree_node(root->right, size + 1)) ;
}


int tree_height(t_request *root)
{
    int left_h;
    int right_h;

    if(!root)
        return(0);
    left_h = tree_height(root->left);
    right_h = tree_height(root->right);
    return(max(left_h, right_h) + 1);
}


// void tree_bfs(t_request *root, int level,  t_request *queue)
// {
//     int height;

//     if(!root)
//         return ;
    
// }


void enqueue(t_request **queue, t_request *node)
{
    int i;

    i = 0;
    while (queue[i])
        i++;
    queue[i] = node;    
}

void dequeue(t_request **queue)
{
    int i;
    t_request *tmp;

    i = 1;
    while (queue[i])
    {
        tmp = queue[i];
        
        queue[i - 1] = queue[i];
        i++;
    }
    
}

void bfs(t_request *root)
{
    int number_of_node;
    t_request **queue;
    int i;
    number_of_node = count_tree_node(root, 0) - 1;
    queue = malloc(sizeof(t_request *) * number_of_node);
    i = 0;
    enqueue(queue, root);
    enqueue(queue, root->left);
    enqueue(queue, root->right);
    while (queue[i])
    {
        printf("noeud %d: %p\n", i, queue[i]);
        i++;
    }
    printf("start dequeue\n");
    dequeue(queue);
    dequeue(queue);
    i = 0;
    while (queue[i])
    {
        printf("noeud %d: %p\n", i, queue[i]);
        i++;
    }
    
    printf("le nombre de noeud est %d\n", number_of_node);
    
}