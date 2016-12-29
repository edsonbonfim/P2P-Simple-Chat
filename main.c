/**
 * Simples 'client-server model' com socket
 *
 * @author Edson Onildo <edsononildo@id.uff.br>
 */

#include "bonfim.h"

int msg()
{
    printf("The available commands are:\n");
    printf("    server    Start server with a specific port\n");
    printf("    client    Connect a specific server\n");
    return 0;
}

int main(int argc, char *argv[])
{  
    if (argc < 2) return msg();
    if (*argv[1] == 115) return server(atoi(argv[2]));
    if (*argv[1] == 99)  return client(argv[2], atoi(argv[3]));
    return msg();
}