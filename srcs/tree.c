/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 20:49:46 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/28 20:52:11 by cebouhad         ###   ########.fr       */
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

void bfs(t_request *root)
{
    int count_node;
    int level;

    level = 1;
    count_node = count_tree_node(root, 0);
   
    printf("The size of the tree is %d\n", count_node);
    printf("The level of the tree is %d\n",  tree_height(root));
}