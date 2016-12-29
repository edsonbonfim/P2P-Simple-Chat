/**
 * Simples 'client-server model' com socket
 *
 * @author Edson Onildo <edsononildo@id.uff.br>
 */

int server(int portno)
{  
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) error("ERROR opening socket");
  
    struct sockaddr_in serv_addr, cli_addr;
  
    bzero((char *) &serv_addr, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    if (bind(sock, (struct sockaddr *) & serv_addr, sizeof(serv_addr)) < 0) error("ERROR on binding");
  
    listen(sock, 5);
    int clilen = sizeof(cli_addr);
    char buffer[256];
  
    while (1) {
        int newsock = accept(sock, (struct sockaddr *) &cli_addr, &clilen);
  
        if (newsock < 0) error("ERROR on accept");
        if (fork() < 0)  error("ERROR on fork");
      
        if (fork() == 0) {
            close(sock);
            bzero(buffer, 256);
    
            if (read(newsock, buffer, 255) < 0) error("ERROR reading from socket");
            if (write(newsock, "I got your message", 18) < 0) error("ERROR writing to socket");
  
            printf("Here is the message: %s\n", buffer);
          
            exit(0);
        }
        else close(newsock);
    }
    return 0;
}