/**
 * P2P-Chat
 *
 * https://github.com/EdsonOnildoJR/P2P-Chat
 *
 * @author Edson Onildo <edsononildo@id.uff.br>
 */

#include "bonfim.hpp"

int msg()
{
    cout << "The available commands are:" << endl;
    cout << "    server    Start server with a specific port" << endl;
    cout << "    client    Connect a specific server" << endl;
    return 0;
}

int main(int argc, char *argv[])
{  
    if (argc < 2) return msg();
    if (*argv[1] == 115) return runServer(atoi(argv[2]));
    if (*argv[1] == 99)  return runClient(argv[2], atoi(argv[3]));
    return msg();
}