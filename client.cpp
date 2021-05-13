#include <cstring>
#include <iostream>
#include <asio.hpp>
#include <string>
#include "asio/buffer.hpp"
#include "message.h"
#define PORT 5000

std::vector<std::string> split(const std::string& text) {
    std::string tmp;
    std::vector<std::string> stk;
    std::stringstream ss(text);
    while(getline(ss,tmp,' ')) {
        stk.push_back(tmp);
    }
    return stk;
}

int main(int argc, char* argv[]){
    Message message;
    std::string command;
    asio::io_context context;
    asio::error_code ec;
    asio::ip::udp::endpoint endpoint(asio::ip::make_address("127.0.0.1", ec), PORT);
    asio::ip::udp::socket socket(context);
    socket.open(asio::ip::udp::v4());
    std::cout << "Welcome to the ATJU shell!" << std::endl;
    std::cout << "[atju@atnix]$ ";
    if(socket.is_open()){
        for(;;){
            std::getline(std::cin, command);
            if(command == "clear"){
                std::cout << "\033[2J\033[1;1H";
                std::cout << "[atju@atnix]$ ";
                continue;
            }
            else if(command == "exit"){
                message.type = EXIT;
            }
            else if(command.find("program") != std::string::npos){
                std::vector<std::string> fields = split(command);
                message.type = PROGRAM;
                strcpy(message.programName, fields[1].data());
                message.pTime = atoi(fields[2].data());
            }
            else if(command.find("kill") != std::string::npos){
                std::vector<std::string> fields = split(command);
                message.type = KILL;
                message.pTime = atoi(fields[1].data());
            }
            asio::mutable_buffer buffer(&message, sizeof(message));
            socket.send_to(asio::buffer(buffer, sizeof(buffer)), endpoint);
            if(message.type == EXIT)
                break;
            std::cout << "[atju@atnix]$ ";
        }
    }
    return 0;
}
