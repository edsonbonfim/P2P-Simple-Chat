/**
 * Simple peer to peer chat program
 *
 * https://github.com/EdsonOnildoJR/P2P-Chat
 *
 * @author Edson Onildo <edsononildo@id.uff.br>
 */

int runClient()
{
    int client;
    int portNum = 1500;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
    const char* host = "localhost";
  
    struct sockaddr_in server_addr;
  
    /*
    |--------------------------------------------------------------------------
    | Estabelecendo conexão de socket
    |--------------------------------------------------------------------------
    |
    | A função socket() cria um novo socket. É preciso 3 argumentos:
    |
    | a) AF_INET: domínio de endereço do socket
    | b) SOCK_STREAM: tipo do socket
    | c) É um argumento de protocolo: deve ser sempre 0
    |
    | Isto irá retornar um pequeno inteiro e é usado para todas as
    | referências a este socket. Se a chamada de socket falhar, ele retorna -1
    |
    */

    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) {
        cout << "Falha ao estabelecer conexão socket..." << endl;
        exit(1);
    }
    cout << "\n=>Servidor socket foi criado com sucesso..." << endl;
  
    /*
    |--------------------------------------------------------------------------
    | Inicializando variáveis
    |--------------------------------------------------------------------------
    |
    | A variável serv_addr é uma estrutura de sockaddr_in.
    |
    | sin_family contém um código para a família de endereços.
    | deve sempre ser definido como AF_INET.
    |
    | INADDR_ANY contém o endereço IP do host. Para servidor, este será
    | sempre o endereço IP da máquina na qual o servidor está sendo executado.
    | 
    | htons() converte o número da porta da ordem de byte do host
    | para um número de porta na ordem de bytes da rede.
    |
    */
  
    struct hostent * ip = gethostbyname(host);

    server_addr.sin_family = AF_INET;
    memcpy((char*)&server_addr.sin_addr.s_addr, (char*)ip->h_addr, ip->h_length);
    server_addr.sin_port = htons(portNum);
  
    /*
    |--------------------------------------------------------------------------
    | Conectando ao socket
    |--------------------------------------------------------------------------
    |
    | A função de conexão é chamada pelo cliente para estabelecer uma
    | conexão com o servidor. É necessário três argumentos,
    |
    | a) O descritor de arquivo de socket
    | b) O endereço do host e porta ao qual deseja se conectar
    | c) O tamanho desse endereço.
    |
    | Esta função retorna 0 em caso de sucesso e -1 se falhar.
    | Observe que o cliente precisa saber o número da porta do servidor,
    | mas não seu próprio número de porta.
    |
    */
    
    if (connect(client, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
        cout << "=> Conectado ao servidor na porta " << portNum << endl;
        
    cout << "Aguardando confirmação do servidor..." << endl;
    recv(client, buffer, bufsize, 0);
    cout << "Conexão confirmada, tudo pronto!!";

    cout << "\n=> Digite # para finalizar a conexão" << endl;
  
    do {
        cout << "Client: ";
        do {
            cin >> buffer;
            send(client, buffer, bufsize, 0);
            if (*buffer == '#') {
                send(client, buffer, bufsize, 0);
                *buffer = '*';
                isExit = true;
            }
        } while (*buffer != 42);

        cout << "Server: ";
        do {
            recv(client, buffer, bufsize, 0);
            cout << buffer << " ";
            if (*buffer == '#') {
                *buffer = '*';
                isExit = true;
            }

        } while (*buffer != 42);
        cout << endl;

    } while (!isExit);
  
    /*
    |--------------------------------------------------------------------------
    | Encerrando chamadas
    |--------------------------------------------------------------------------
    |
    | Depois que o servidor pressionar # para terminar a conexão,
    | o loop irá quebrar e ele irá fechar a conexão
    | de soquete do servidor e a conexão do cliente.
    |
    */
  
    cout << "\n=>Conexão finalizada.\nThau!!\n";

    close(client);  
    return 0;
}