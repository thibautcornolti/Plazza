/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#include "WebServer.hpp"

WebServer::WebServer(const std::string &ip, int port, const Router &router)
	: _ip(ip), _port(port), _socket(ip, port), _sockets(0), _router(router)
{
}

WebServer::~WebServer()
{
}

void WebServer::launch()
{
	while (1) {
		_waitEvent();
		if (_socket.isDataPending()) {
			TCPSocket client = _socket.accept();
			std::string inputs;
			do {
				inputs = client.receive();
				_ingestHeader(inputs);
			} while (inputs != "\r");
			auto res = _router(_lastMethod, _lastPath);
			client.send("HTTP/1.1 200 OK\n"
				    "Content-Type: text/html\n"
				    "Content-Length: " +
				std::to_string(res.length()) + "\r\n\r\n");
			client.send(res);
			client.close();
		}
		else {
		}
	}
}

void WebServer::_ingestHeader(const std::string &line)
{
	std::cmatch cm;
	if (std::regex_search(line.c_str(), cm, std::regex("^(GET|POST) ([^\\s]+)"))) {
		_lastMethod = cm[1];
		_lastPath = cm[2];
	}
}

void WebServer::_waitEvent()
{
	std::vector<struct pollfd> fds;

	fds.reserve(_sockets.size());
	for (size_t i = 0; i < _sockets.size(); i++)
		fds.push_back(pollfd{.fd = _sockets.at(i).getHandle(),
			.events = POLLIN,
			.revents = 0});
	fds.push_back(pollfd{
		.fd = _socket.getHandle(), .events = POLLIN, .revents = 0});
	poll(&fds[0], fds.size(), -1);
}
