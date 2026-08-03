/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cebouhad <cebouhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 12:56:58 by cebouhad          #+#    #+#             */
/*   Updated: 2026/08/03 10:33:27 by cebouhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"


void display_available_assertion(char **assertion_name)
{
    int i;

    i = 0;
    while (assertion_name[i])
        printf("%s\n", assertion_name[i++]);
    
}

int choose_assertion(char **assertion_name)
{
    char buffer[1024];
    int b_read;

    display_available_assertion(assertion_name);
    b_read = 0;
    while (b_read != 1)
    {
        write(STDOUT_FILENO,"choose your assertion: ", strlen("choose your assertion: "));

        b_read = read(STDIN_FILENO, buffer, 1024);
        buffer[b_read] = '\0';
        if(!strcmp(buffer,"1\n"))
            return (1);
        else if(!strcmp(buffer,"2\n"))
            return (2);
        else if(!strcmp(buffer,"3\n"))
            return (3);
        else if(!strcmp(buffer,"4\n"))
            return (4);
        else
            printf(REDB"Wrong input. Choose 1 or 2"CRESET"\n");
    }
    return (0);
}


static int assert_queue()
{
    poppush_queue_assert();
    bfs_binary_tree_as_arr_assert();
    push_request_assert();
    create_request_assert();
    remove_request_assert();
    return (0);
}

static int assert_thread(void)
{
    //thread_send_request_assert();
    //thread_consume_request_assert();
    //thread_coders_assert();
    thread_coders_and_monitor_assert();
    return (0);
}

static int assert_time(void)
{
    time_assertion();
    return (TRUE);
}

int main(void)
{
    int assertion;
    char *assertion_name[] = {"assert_queue [1]", "asset_thread [2]", "assert_time [3]" ,"All [4]", NULL};

    assertion = choose_assertion(assertion_name);

    if (assertion == 1)
        assert_queue();
    else if (assertion == 2)
        assert_thread();
    else if (assertion == 3)
        assert_time();
    else if (assertion == 4)
    {
        assert_queue();
        assert_thread();
        assert_time();
    }
    return (0);
}