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
 * Esta função é chamada quando uma chamada de sistema falha
 * Ele exibe uma mensagem sobre o erro stderre, em seguida, interrompe o programa
 */
void error(char *msg)
{
    perror(msg);
    exit(1);
}

int sockfd, newsockfd; // São descritores de arquivos, ou seja, subscritos de matriz para a tabela de descritor de arquivo.
int portno;            // Armazena o número da porta na qual o servidor aceita conexões.
int n;                 // É o valor de retorno para o read() e write() chamadas; Ou seja, contém o número de caracteres lidos ou escritos.
int clilen;

char buffer[256];      // O servidor lê caracteres da conexão para esse buffer.

struct hostent * server;
struct sockaddr_in serv_addr, cli_addr;