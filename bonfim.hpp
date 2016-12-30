/**
 * Simple peer to peer chat program
 *
 * https://github.com/EdsonOnildoJR/P2P-Chat
 *
 * @author Edson Onildo <edsononildo@id.uff.br>
 */

#define NRM  "\x1B[0m"
#define RED  "\x1B[31m"

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

using namespace std;

#include "server.hpp"
#include "client.hpp"