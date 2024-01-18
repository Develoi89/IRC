#include "server.hpp"
bool stop = false;

bool    isNum(std::string str)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        if(str[i] > '9' || str[i] < '0')
            return false;
    }
    return true;
}

bool    Server::verifyPort(std::string port)
{
    int num;

    if (!isNum(port))
    {
        std::cout << "Error: Port should be numeric." << std::endl;
        return false;
    }

    num = std::stoi(port);
    if(num > 65535 || num < 1)
    {
        std::cout << "Error: invalid range of Port." << std::endl;
        return false;
    }
    std::cout << "port verifyed " << port << std::endl;
    return true;
}

Server::Server(int port, std::string password){
    _port = port;
    _password = password;
    int socketServidor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketServidor == -1) {
        std::cout << std::strerror(errno) << std::endl;
        exit(1);
    }

    sockaddr_in servAddr;//esto se utiliza para almacenar la información de 
    std::memset(&servAddr, 0, sizeof(servAddr)); //inicializa toda la estructura direccionServidor con ceros.
    servAddr.sin_family = AF_INET; //AF_INET establece el tipo de dirección como IPv4
    servAddr.sin_port = htons(_port); //Convierte el numero del puerto para ser usada en la red
    servAddr.sin_addr.s_addr = INADDR_ANY; //el servidor aceptará conexiones en cualquier interfaz de red disponible en la máquina.


    if (bind(socketServidor, reinterpret_cast<sockaddr*>(&servAddr), sizeof(servAddr)) == -1) { //se vincula el socket al servidor
        std::cout << std::strerror(errno) << std::endl;
        close(socketServidor);
        exit(1);
    }

    if (listen(socketServidor, 5) == -1) { //se pone el socket en modo de escucha para las nuevas conexiones entrantes(clientes) y el argumento 5 son las colas de conexion
        std::cout << std::strerror(errno) << std::endl;
        close(socketServidor);
        exit(1);
    }


    _pollsfd = std::vector<pollfd>(1);

    _serverfd_.fd = socketServidor;
    _pollsfd[0].fd = socketServidor;
    _pollsfd[0].events = POLLIN;
}

void handler(int signal) {(void) signal; stop = true;}

void Server::runCmd(std::string buffer, int i)
{
    std::vector<std::string> tokens;
    std::string word;
    std::stringstream str(buffer);
    while (std::getline(str, word, ' '))
    {
        size_t pos;
        while ((pos = word.find('\n')) != std::string::npos) {
            word.erase(pos, 1);
        }
        if (!word.empty()) {
            std::cout << word << std::endl;
            tokens.push_back(word);
        }
    }
    Client *aux(_map_clients[_pollsfd[i].fd]);
    if(aux->getPw() == false)
    {
        if(tokens[0] == "PASS")
            if(tokens[1] == _password)
            {
                send(_pollsfd[i].fd, "Conected.\n", 10, 0);
                aux->setPw(true);
            }
    }
    else
    {
        //el resto de comandos.
    }

}

void Server::_request(int i)
{
    char buffer[1024];
    ssize_t bytes = recv(_pollsfd[i].fd, buffer, sizeof(buffer), 0);
    // if(bytes == -1)
    // {
    // }
    // if(bytes == 0)
    // {
    // }
    std::string request(buffer, bytes);
    runCmd(request, i);
}

void Server::loop(){
    int cls = 1;
    char buffer[1024] = {0};
    
    std::signal(SIGINT, handler);

    while(!stop){
        if(poll(_pollsfd.data(), cls , -1) == -1){
            std::cout << std::strerror(errno) << std::endl;
            close( _serverfd_.fd);
            exit(1);
        }
        
            for(int i = 0; i < cls; i++){
                if (_pollsfd[i].revents & POLLIN) {
                    if (_pollsfd[i].fd == _serverfd_.fd)
                    {
                        int new_fd = accept(_serverfd_.fd, nullptr, nullptr);
                        _pollsfd[cls].fd = new_fd;
                        _pollsfd[cls].events = POLLIN;
                        _map_clients.insert(std::pair<int, Client *>(new_fd, new Client(new_fd)));
                        cls++;
                    }
                    else
                    {
                        _request(i);
                    }
                }
            }
           
        }
            
}



