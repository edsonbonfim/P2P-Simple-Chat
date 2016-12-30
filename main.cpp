/**
 * Simple peer to peer chat program
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
    if (*argv[1] == 115) return runServer();
    if (*argv[1] == 99)  return runClient();
    return msg();
}