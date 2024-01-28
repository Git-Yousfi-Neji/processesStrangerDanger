
#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char **usernames;
    size_t count;
} SystemUsernamesList;

SystemUsernamesList parseSystemUsernames(const char *filePath);
void freeSystemUsernamesList(SystemUsernamesList *userList);

#endif // CONFIG_PARSER_H