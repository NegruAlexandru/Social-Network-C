#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"
#include "posts.h"
#include "posts_functions.h"

void handle_input_posts(char *input, post_array_t *posts)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "create"))
		create_post(input, posts);
	else if (!strcmp(cmd, "repost"))
		create_repost(input, posts);
	else if (!strcmp(cmd, "common-repost"))
		common_repost(input, posts);
	else if (!strcmp(cmd, "like"))
		like_post(input, posts);
	else if (!strcmp(cmd, "ratio"))
		ratio_post(input, posts);
	else if (!strcmp(cmd, "delete"))
		delete_post(input, posts);
	else if (!strcmp(cmd, "get-likes"))
		get_likes(input, posts);
	else if (!strcmp(cmd, "get-reposts"))
		get_reposts(input, posts);

	free(commands);
}

