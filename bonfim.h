/**
 * Simples 'client-server model' com socket
 *
 * @author Edson Onildo <edsononildo@id.uff.br>
 */

#define NRM  "\x1B[0m"
#define RED  "\x1B[31m"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void alert(char *msg) { fprintf(stderr,"%s%s%s\n", RED, msg, NRM); exit(0); }
void error(char *msg) { perror(msg); exit(1); }

#include "server.h"
#include "client.h"