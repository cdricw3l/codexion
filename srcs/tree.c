/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdric.b <cdric.b@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 20:49:46 by cebouhad          #+#    #+#             */
/*   Updated: 2026/07/28 21:26:16 by cdric.b          ###   ########.fr       */
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


void tree_bfs(t_request *root, int level)
{
    int height;

    if(!root)
        return ;
    height = tree_height(root);
    if(height == level)
        display_request(*root);
    tree_bfs(root->left, level);
    tree_bfs(root->right, level);
}

void bfs(t_request *root)
{
    tree_bfs(root, 2);
}