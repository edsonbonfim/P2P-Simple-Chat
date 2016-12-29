/**
 * Simples 'client-server model' com socket
 *
 * @author Edson Onildo <edsononildo@id.uff.br>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h> // Inclui uma série de definições de estruturas necessárias para sockets
#include <netinet/in.h> // Contém constantes e estruturas necessários para endereços de domínio Internet.
#include <netdb.h>      // Define a estrutura hostent.

/**
#define NRM  "\x1B[0m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define CYN  "\x1B[36m"
#define WHT  "\x1B[37m"
*/

/**
 * Esta função é chamada quando uma chamada de sistema falha
 * Ele exibe uma mensagem sobre o erro stderre, em seguida, interrompe o programa
 */
void error(char *msg)
{
    perror(msg);
    exit(1);
}

int sock, newsock; // São descritores de arquivos, ou seja, subscritos de matriz para a tabela de descritor de arquivo.
int n;             // É o valor de retorno para o read() e write() chamadas; Ou seja, contém o número de caracteres lidos ou escritos.
int clilen;

char buffer[256];  // O servidor lê caracteres da conexão para esse buffer.

struct hostent * host;
struct sockaddr_in serv_addr, cli_addr;

#include "server.h"
#include "client.h"