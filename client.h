/**
 * Simples 'client-server model' com socket
 *
 * @author Edson Onildo <edsononildo@id.uff.br>
 */

int client(char *hostname, int portno)
{  
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) error("Falha ao abrir socket");
  
    struct hostent * host = gethostbyname(hostname);  
    if (host == NULL) alert("Falha ao procurar servidor");
  
    struct sockaddr_in serv_addr, cli_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)host->h_addr, (char *)&serv_addr.sin_addr.s_addr, host->h_length);
    serv_addr.sin_port = htons(portno);
    
    if (connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) error("Falha ao conectar-se");
  
    char buffer[256];
    
    printf("Digite uma mensagem: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
  
    int n = write(sock, buffer, strlen(buffer));
    if (n < 0) error("Falha ao escrever no socket");
  
    bzero(buffer, 256);
  
    n = read(sock, buffer, 255);
    if (n < 0) error("Falha na leitura do socket");
  
    printf("%s\n", buffer);
  
    return 0;
}