#include "client.h"

// DataPC
class DataPC
{
public:
    std::string username = getenv("username");
    std::string computer = getenv("computername");
    std::string appdata = getenv("appdata");
    std::string operatingSystem = getenv("os");
};
DataPC DataPC;

//
void Client()
{
    const string ipAddress = "127.0.0.1";			// IP Address of the server
    const int port = 13254;						// Listening port # on the server

    // Initialize WinSock
    WSAData data{};
    WORD ver = MAKEWORD(2, 2);
    int wsResult = WSAStartup(ver, &data);
    if (wsResult != 0)
    {
        cerr << "Can't start Winsock, Err #" << wsResult << endl;
        return;
    }

    // Create socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
        WSACleanup();
        return;
    }

    // Fill in a hint structure
    sockaddr_in hint{};
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    // Connect to server
    int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connResult == SOCKET_ERROR)
    {
        cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
        closesocket(sock);
        WSACleanup();
        return;
    }

    // While loop to send and receive data
    char buf[4096];

    // Send data PC
    string codePC = "A";
    string pc = codePC + " " + DataPC.username + " | " + DataPC.computer + " | " + DataPC.operatingSystem + " | " + DataPC.appdata;

    cout << pc << endl;

    send(sock, pc.c_str(), pc.size() + 1, 0);

    while (true)
    {
        ZeroMemory(buf, 4095);

        //
        int bytesReceived = recv(sock, buf, 4096, 0);
        if (bytesReceived == SOCKET_ERROR)
        {
            cerr << "Error in recv(). Quitting" << endl;
            break;
        }

        //
        string command = string(buf, 0 , bytesReceived);

        //
        if (command == string("-Connect"))
        {
            string test = "TEST228\n";
            cout << test;
        }
        else
        {
            cout << command << endl;
        }
    }

    // Gracefully close down everything
    closesocket(sock);
    WSACleanup();
}
