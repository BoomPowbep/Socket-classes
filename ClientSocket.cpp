/***********************************************
*   	        ___     _       _
*   	       / __|  _| |_   _| |_
*  	          | (__  |_   _| |_   _|
*  	           \___|   |_|     |_|
*
*                    SOCKET
*
*	            ClientSocket.cpp
*   	         Mickaël Debalme
*                 07/10/2017 (V2)
*       Classe de gestion d'une connexion
*                 socket client
*            Hérite de CommonSocket
*
*              Copyright (C) 2017
*
**********************************************/

#include "ClientSocket.h"

ClientSocket::ClientSocket(const char* adresseIp, int port) : CommonSocket(adresseIp, port) {

}

ClientSocket::~ClientSocket() {

}

int ClientSocket::connecterServeur() {

	// Connexion au serveur
	int status = connect(mSocket, (SOCKADDR*)&mSocketAddress, sizeof(mSocketAddress));

	// Gestion des erreurs
	if (status == SOCKET_ERROR) {

		return ERREUR_SOCKET;
	}
	else {

		return SUCCES_SOCKET;
	}
}

int ClientSocket::envoyerMessage(const char* message) {

	// Tentative d'envoi du message
	int status = send(mSocket, message, (size_t)strlen(message) * sizeof(char), 0);

	// Gestion des erreurs
	if (status == SOCKET_ERROR) {

		return ERREUR_SOCKET;
	}
	else {

		return SUCCES_SOCKET;
	}
}

std::string ClientSocket::recevoirMessage() {

	char superBuffer[BUFLEN] = { 0 };

	int status = recv(mSocket, superBuffer, BUFLEN, 0);

	// Gestion des erreurs
	if(status == SOCKET_ERROR) {

		return "NOK";
	}
	else {

		std::string messageRecu(superBuffer);

		return messageRecu;
	}
}
