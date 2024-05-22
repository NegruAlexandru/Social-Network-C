#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "posts.h"
#include "feed.h"
#include "users.h"
#include "feed_functions.h"

void handle_input_feed(char *input, int **adj_mat, post_array_t *posts)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "feed"))
		feed(input, adj_mat, posts);
	else if (!strcmp(cmd, "view-profile"))
		view_profile(input, posts);
	else if (!strcmp(cmd, "friends-repost"))
		friends_repost(input);
	else if (!strcmp(cmd, "common-groups"))
		common_groups(input, adj_mat);
	free(commands);
}
