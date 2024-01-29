#include "server.hpp"
#include "Utils.hpp"
#include "Comands.hpp"

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
            {
                tokens.push_back(word);
            }
        }
        Client *aux(map_clients[this->_pollsfd[i].fd]);
        if(!aux->getPw())
        {
            if(tokens[0] == "PASS")
                if(tokens[1] == this->password)
                {
                    //std::cout << "connected" << std::endl;
                    aux->setPw(true);
                }
        }
        else
        {
            if(!aux->getRg())
            {
                if(tokens[0] == "NICK")
                {
                    //implementar errores y CAMBIO DE NICK -- teo NICK oet
                    aux->setNick(tokens[1]);
                    //std::cout << "nick setted" << std::endl;
                }
                else if(tokens[0] == "USER")
                {
                    //implementar errores
                    if(aux->getNick() == "")
                        return ;

                    aux->setUser(tokens[1]);
                    aux->setName(tokens[1]);
                    aux->setRg(true);
                    registerMsg(*aux);
                    // std::cout << "registered" << std::endl;
                    // std::cout << aux->getNick() << std::endl;
                    // std::cout << aux->getUser() << std::endl;
                }
            }
            else
            {
                //Todos los comandos:
                Comands::checkCmd(aux, tokens);

            }

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
    std::string request(buffer, bytes);
    std::vector<std::string> cm = tkparser(request, "\r\n");
     //std::cout << buffer << std::endl;
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
                        int new_fd = accept(this->serverfd_.fd, nullptr, nullptr);
                        if(new_fd == -1){
                            std::cout << std::strerror(errno) << std::endl; 
                        }
                        this->_pollsfd[this->cls].fd = new_fd;
                        this->_pollsfd[this->cls].events = POLLIN;
                        this->map_clients.insert(std::pair<int, Client *>(new_fd, new Client(new_fd)));
                        this->cls++;
                    }
                    else
                    {
                        _request(i);
                    }
                }
            }
           
        }
            
}



