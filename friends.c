#include <stdlib.h>
#include <string.h>

#include "friends.h"
#include "users.h"
#include "friends_functions.h"

void handle_input_friends(char *input, int **adj_mat, int *no_friends)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "add"))
		add_friend(input, adj_mat, no_friends);
	else if (!strcmp(cmd, "remove"))
		remove_friend(input, adj_mat, no_friends);
	else if (!strcmp(cmd, "suggestions"))
		suggestions(input, adj_mat);
	else if (!strcmp(cmd, "distance"))
		distance_between_friends(input, adj_mat);
	else if (!strcmp(cmd, "common"))
		common_friends(input, adj_mat);
	else if (!strcmp(cmd, "friends"))
		number_friends(input, no_friends);
	else if (!strcmp(cmd, "popular"))
		popular_friends(input, adj_mat, no_friends);

	free(commands);
}
