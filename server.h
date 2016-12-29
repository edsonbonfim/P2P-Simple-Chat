/**
 * Simples 'client-server model' com socket
 *
 * @author Edson Onildo <edsononildo@id.uff.br>
 */

int server(int portno)
{  
    // Retorna um descritor (socket ID) se criado com sucesso, -1 caso contrário
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) error("ERROR opening socket");
  
    // Reposiciona o ponteiro no índice zero
    bzero((char *) &serv_addr, sizeof(serv_addr));
    
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
            
            bzero(buffer, 256);
    
            if (read(newsock, buffer, 255) < 0) error("ERROR reading from socket");
            if (write(newsock, "I got your message", 18) < 0) error("ERROR writing to socket");
  
            printf("Here is the message: %s\n", buffer);
          
            exit(0);
        }
      
        // Liberta as estruturas de dados do kernel
        else close(newsock);
    }
  
    // Estamos em um loop infinito e nunca entraremos aqui!
    return 0;
}