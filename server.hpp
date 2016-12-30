/**
 * P2P-Chat
 *
 * https://github.com/EdsonOnildoJR/P2P-Chat
 *
 * @author Edson Onildo <edsononildo@id.uff.br>
 */

int runServer(int portNum)
{
    int client, server;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
  
    struct sockaddr_in server_addr;
    socklen_t size;
  
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

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(portNum);

    /*
    |--------------------------------------------------------------------------
    | Ligando o socket
    |--------------------------------------------------------------------------
    |
    | A chamada de sistema bind() vincula um socket a um endereço,
    | neste caso o endereço do host atual e número de porta
    | no qual o servidor será executado. É preciso três argumentos:
    | 
    | a) O descritor de arquivo de soquete
    | b) Um ponteiro para uma estrutura do tipo sockaddr
    | c) O tamanho do ponteiro passado como segundo argumento
    |
    */

    if ((bind(client, (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0) {
        cout << "Falha ao realizar a ligação. O socket já foi estabelecido..." << endl;
        return -1;
    }
    
    // size é um tipo intr de largura de pelo menos 32 bits
    size = sizeof(server_addr);
  
    /*
    |--------------------------------------------------------------------------
    | Escutando chamadas
    |--------------------------------------------------------------------------
    |
    | A chamada de sistema de escuta permite ao processo ouvir conexões socket.
    | O programa permanecerá ocioso aqui se não houver conexões de entrada.
    | 
    | É preciso 2 argumentos:
    | a) Descritor de arquivo de socket
    | b) Tamanho para o número de clientes (MAX = 5)
    |
    */
  
    cout << "=>Procurando Clientes..." << endl;
    listen(client, 1);
  
    /*
    |--------------------------------------------------------------------------
    | Aceitando Clientes
    |--------------------------------------------------------------------------
    |
    | A chamada de sistema accept() faz com que o processo bloqueie
    | até que um cliente se conecte ao servidor.
    | Assim, ele acorda o processo quando uma conexão de um cliente foi
    | estabelecida com êxito. Ele retorna um novo descritor de arquivo,
    | e toda comunicação nessa conexão deve ser feita usando o novo
    | descritor de arquivo. O segundo argumento é um ponteiro de referência
    | para o endereço do cliente na outra extremidade da conexão
    | e o terceiro argumento é o tamanho dessa estrutura.
    |
    */
  
    int clientCount = 1;
    server = accept(client, (struct sockaddr *)&server_addr, &size);

    // Primeiro verifique se ele é válido ou não
    if (server < 0)
        cout << "Falha ao aceitar a conexão..." << endl;

    while (server > 0)
    {
        /*
        |--------------------------------------------------------------------------
        | Obs;
        |--------------------------------------------------------------------------
        |
        | Observe que só chegaríamos a este ponto após um cliente ter
        | conectado com êxito ao nosso servidor. Isso lê a partir do socket.
        | Observe que o read() irá bloquear até que haja algo para ele ler
        | no socket, ou seja, após o cliente ter executado um send().
        | Ele irá ler o número total de caracteres no soquete ou 1024
        |
        */

        strcpy(buffer, "=> Servidor conectado!!\n");
        send(server, buffer, bufsize, 0);
        cout << "=> Conectado com o cliente #" << clientCount << ", tudo pronto!!" << endl;
        cout << "\n=> Digite # para finalizar a conexão" << endl;
      
        /*
        |--------------------------------------------------------------------------
        | Obs 2;
        |--------------------------------------------------------------------------
        |
        | Uma vez estabelecida uma conexão, ambas as extremidades podem ler e
        | gravar na conexão. Naturalmente, tudo escrito pelo cliente será lido
        | pelo servidor, e tudo escrito pelo servidor será lido pelo cliente.
        |
        */
      
        cout << "Client: ";
      
        do {
            recv(server, buffer, bufsize, 0);
            cout << buffer << " ";
            if (*buffer == '#') {
                *buffer = '*';
                isExit = true;
            }
        } while (*buffer != '*');

        do {
            cout << "\nServer: ";
            do {
                cin >> buffer;
                send(server, buffer, bufsize, 0);
                if (*buffer == '#') {
                    send(server, buffer, bufsize, 0);
                    *buffer = '*';
                    isExit = true;
                }
            } while (*buffer != '*');

            cout << "Client: ";
            do {
                recv(server, buffer, bufsize, 0);
                cout << buffer << " ";
                if (*buffer == '#') {
                    *buffer == '*';
                    isExit = true;
                }
            } while (*buffer != '*');
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
      
        cout << "\n\n=> Conexão finalizada com o IP " << inet_ntoa(server_addr.sin_addr);
        close(server);
        cout << "\nThau!!" << endl;
        isExit = false;
        exit(1);
    }
  
    close(client);
    return 0;
}