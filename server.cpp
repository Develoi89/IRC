#include "server.hpp"

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

// bool singIn()
// {

// }

void Server::loop(){
    int cls = 1;
    while(true){
        if(poll(this->_pollsfd.data(), cls , -1) == -1){
            std::cout << std::strerror(errno) << std::endl;
            close( this->serverfd_.fd);
            exit(1);
        }
        
            for(int i = 0; i < cls; i++){
                if (this->_pollsfd[i].revents & POLLIN) {
                    if (this->_pollsfd[i].fd == this->serverfd_.fd)
                    {
                        int nuevoSocket = accept(this->serverfd_.fd, nullptr, nullptr);
                        this->_pollsfd[cls].fd = nuevoSocket;
                        this->_pollsfd[cls].events = POLLIN;
                        std::cout << "CLIENTE NUEVO " << std::endl;
                        cls++;
                    }
                    
                }
            }
           
        }
            
}



