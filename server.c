/**
 * Simples 'client-server model' com socket
 *
 * @author Edson Onildo <edsononildo@id.uff.br>
 */

#include "bonfim.h"

void bonfim(int);

int main(int argc, char *argv[])
{  
    /**
    * O usuário precisa passar o número da porta em que o servidor aceitará conexões como um argumento.
    * Este código exibe uma mensagem de erro se o usuário não conseguir fazer isso.
    */
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
  
    // Retorna um descritor (socket ID) se criado com sucesso, -1 caso contrário
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) error("ERROR opening socket");
  
    // Reposiciona o ponteiro no índice zero
    bzero((char *) &serv_addr, sizeof(serv_addr));
    
    portno = atoi(argv[1]);
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    // Associa um socket ID a um endereço para que os processos possam comunicar.
    if (bind(sock, (struct sockaddr *) & serv_addr, sizeof(serv_addr)) < 0) error("ERROR on binding");
  
    // Especifica o número máximo de pedidos de conexões que podem estar em espera para este processo
    listen(sock, 5);
  
    clilen = sizeof(cli_addr);
  
    while (1) {
        // Estabelece conexão com o cliente especificado
        newsock = accept(sock, (struct sockaddr *) &cli_addr, &clilen);
  
        if (newsock < 0)
            error("ERROR on accept");
      
        if (fork() < 0)
            error("ERROR on fork");
      
        if (fork() == 0) {
            close(sock);
            bonfim(newsock);
            exit(0);
        }
      
        // Liberta as estruturas de dados do kernel
        else close(newsock);
    }
  
    // Estamos em um loop infinito e nunca entraremos aqui!
    return 0;
}

/**
 * Existe uma instância separada desta função para cada conexão.
 * Ele lida com todas as comunicações uma vez estabelecida uma conexão.
 */
void bonfim(int sock)
{
    bzero(buffer, 256);
    
    if (read(sock, buffer, 255) < 0) error("ERROR reading from socket");
    if (write(sock, "I got your message", 18) < 0) error("ERROR writing to socket");
  
    printf("Here is the message: %s\n", buffer);
}