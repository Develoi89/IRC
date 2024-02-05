#include "server.hpp"
#include "Utils.hpp"

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

void Server::runCmd(std::vector<std::string> tkn, int i)
{
    std::string word;
    for (std::vector<std::string>::iterator it = tkn.begin(); it != tkn.end(); ++it)
    {
        std::vector<std::string> tokens;
        std::istringstream iss(*it);
        while(std::getline(iss, word, ' '))
        {
            if (!word.empty()) 
                tokens.push_back(word);
        }
        Client *aux(map_clients[this->_pollsfd[i].fd]);
        if(!aux->getPw())
        {
            if(tokens[0] == "PASS")
                if(tokens[1] != this->password){
                    aux->newMessage(std::string("464 ") + " :Password incorrect");
                    return ;
                }
                aux->setPw(true);
        }
        else
        {
            if(!aux->getRg())
            {
                if(tokens[0] == "NICK")
                    cmdNick(aux, tokens);
                else if(tokens[0] == "USER")
                    cmdUser(aux, tokens);
            }
            else
                Server::checkCmd(aux, tokens);
        }
    }
}

void Server::_rmClient(const Client &c){
    for (size_t i = 0; i < this->_pollsfd.size(); ++i)
    {
        if (c.getFd() == this->_pollsfd[i].fd)
        {
            this->_pollsfd.erase(this->_pollsfd.begin() + i);
            this->cls--;
            break;
        }
    }
    int fd = c.getFd();
    close(fd);
    delete this->map_clients[fd];
    this->map_clients.erase(fd);
}



void Server::_request(int i)
{
    char buffer[1024];
    ssize_t bytes = recv(this->_pollsfd[i].fd, buffer, sizeof(buffer), 0);
    if(bytes == -1)
    {
        std::cerr << "recv() error: " << std::strerror(errno) << std::endl;
        return;
    }
    if(bytes == 0)
    {
        _rmClient(*this->map_clients[this->_pollsfd[i].fd]);
        return;
    }
    // std::cout << "Bytes: " << bytes << std::endl;
    // std::cout << "Buffer: " << buffer << std::endl;
//    std::map<int, Client *>::iterator it = map_clients.begin();
//    int h = 0;
//     while(it != map_clients.end()){
//         std::cout << h << " FD:  - " <<  (*it).second->getFd() << std::endl;
//         std::cout << h << " SIZE:  - " <<  map_clients.size() << std::endl;
//         std::cout << std::endl;
//         it++;
//         h++;
//     }
    std::string request(buffer, bytes);
    std::vector<std::string> cm = tkparser(request, "\r\n");
    memset(buffer, 0, sizeof(buffer));
    if(cm.size() == 0)
        return ;
    runCmd(cm, i);
}

void Server::loop(){
    this->cls = 1;
    
    std::signal(SIGINT, handler);

    while(!stop){
        if(poll(this->_pollsfd.data(), this->cls , -1) == -1){
            std::cout << std::strerror(errno) << std::endl;
            close( this->serverfd_.fd);
            exit(1);
        }
        
            for(int i = 0; i < this->cls; i++){
                if (this->_pollsfd[i].revents & POLLIN) {
                    if (this->_pollsfd[i].fd == this->serverfd_.fd)
                    {
                        struct sockaddr_storage	remotaddr;
                        socklen_t addrlen;
                        addrlen = sizeof remotaddr;

                                    
                        int new_fd = accept(this->serverfd_.fd, (struct sockaddr*)&remotaddr, &addrlen);
                        if(new_fd == -1){
                            std::cout << std::strerror(errno) << std::endl; 
                        }
                        else
                        {
                            struct pollfd pls;
                            this->_pollsfd.push_back(pls);
                            this->_pollsfd[this->cls].fd = new_fd;
                            this->_pollsfd[this->cls].events = POLLIN;
                            this->map_clients.insert(std::pair<int, Client *>(new_fd, new Client(new_fd)));
                            this->cls++;
                        }
                    }
                    else
                    {
                        _request(i);
                    }
                }
            }
           
        }
            
}

std::string Server::_currentTime()
{
    time_t t = std::time(0);
    struct tm *now = std::localtime(&t);
    std::string time(asctime(now));
    time.erase(--time.end());
    return time;
}



