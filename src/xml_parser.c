#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/xml_parser.h"

/** @brief Function to parse the xml file that contains
 *         list of legitimate processes name
 *
 *  @param filePath path to the file
 *  @return SystemUsernamesList a struct that contains a list of legitimate processes name
 *  and the number of legitimate processes
 */
SystemUsernamesList parseSystemUsernames(const char *filePath)
{
	SystemUsernamesList userList;
    userList.usernames = NULL;
    userList.count = 0;

    xmlDocPtr doc;
    xmlNodePtr root;
    doc = xmlReadFile(filePath, NULL, 0);

    if (doc == NULL)
    {
        fprintf(stderr, "Error: Couldn't parse XML file %s\n", filePath);
        return userList;
    }
    
    root = xmlDocGetRootElement(doc);
    
    for (xmlNodePtr node = root->children; node != NULL; node = node->next)
    {
        if (node->type == XML_ELEMENT_NODE && xmlStrEqual(node->name, (const xmlChar *)"systemUsernames"))
        {
            char *username = (char *)xmlNodeGetContent(node);
            
            userList.usernames = (char **)realloc(userList.usernames, (userList.count + 1) * sizeof(char *));
            userList.usernames[userList.count] = username;
            userList.count++;
        }
    }
    
    xmlFreeDoc(doc);

    return userList;
}

/** @brief Function to free the allocated memory of the usernames 
 *
 *  @param userList a reference to the SystemUsernamesList
 *  @return void
 */
void freeSystemUsernamesList(SystemUsernamesList *userList)
{
    for (size_t i = 0; i < userList->count; i++)
    {
        free(userList->usernames[i]);
    }
    free(userList->usernames);
}