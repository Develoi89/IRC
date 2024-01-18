#include "server.hpp"
bool stop = false;
Server::Server(int port, std::string password){
    this->port = port;
    this->password = password;
    int socketServidor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketServidor == -1) {
        std::cout << std::strerror(errno) << std::endl;
        exit(1);
    }

    sockaddr_in servAddr;//esto se utiliza para almacenar la información de 
    std::memset(&servAddr, 0, sizeof(servAddr)); //inicializa toda la estructura direccionServidor con ceros.
    servAddr.sin_family = AF_INET; //AF_INET establece el tipo de dirección como IPv4
    servAddr.sin_port = htons(this->port); //Convierte el numero del puerto para ser usada en la red
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


    this->_pollsfd = std::vector<pollfd>(1);

    this->serverfd_.fd = socketServidor;
    this->_pollsfd[0].fd = socketServidor;
    this->_pollsfd[0].events = POLLIN;
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
            //std::cout << word << std::endl;
            tokens.push_back(word);
        }
    }
    Client *aux(map_clients[this->_pollsfd[i].fd]);
    if(aux->getPw() == false)
    {
        if(tokens[0] == "PASS")
            if(tokens[1] == this->password)
            {
                send(this->_pollsfd[i].fd, "Conected.\n", 10, 0);
                aux->setPw(true);
            }
    }
    else
    {
       if(aux->getRg() == false)
       {
        if(tokens[0] == "NICK")
            //implementar errores y CAMBIO DE NICK -- teo NICK oet
            aux->setNick(tokens[1]);
        }
        if(tokens[0] == "USER"){
            //implementar errores
            if(aux->getNick() == "")
                return ;
    
            aux->setUser(tokens[1]);
            aux->setName(tokens[4]);
            aux->setRg(true);
            aux->newMessage("WELCOME: " + aux->getNick() + ", " + aux->getName());

        }
    }

}

void Server::_request(int i)
{
    char buffer[1024];
    ssize_t bytes = recv(this->_pollsfd[i].fd, buffer, sizeof(buffer), 0);
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
        if(poll(this->_pollsfd.data(), cls , -1) == -1){
            std::cout << std::strerror(errno) << std::endl;
            close( this->serverfd_.fd);
            exit(1);
        }
        
            for(int i = 0; i < cls; i++){
                if (this->_pollsfd[i].revents & POLLIN) {
                    if (this->_pollsfd[i].fd == this->serverfd_.fd)
                    {
                        int new_fd = accept(this->serverfd_.fd, nullptr, nullptr);
                        this->_pollsfd[cls].fd = new_fd;
                        this->_pollsfd[cls].events = POLLIN;
                        this->map_clients.insert(std::pair<int, Client *>(new_fd, new Client(new_fd)));
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



