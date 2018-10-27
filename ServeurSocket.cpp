/***********************************************
*   	        ___     _       _
*   	       / __|  _| |_   _| |_
*  	          | (__  |_   _| |_   _|
*  	           \___|   |_|     |_|
*
*                    SOCKET
*
*	            ServeurSocket.cpp
*   	         Mickaël Debalme
*                 07/10/2017 (V2)
*       Classe de gestion d'une connexion
*                 socket serveur
*            Hérite de CommonSocket
*
*              Copyright (C) 2017
*
**********************************************/

#include "ServeurSocket.h"

ServeurSocket::ServeurSocket(int port) : CommonSocket(port) {

	mSocketCommunication = 0;
}

ServeurSocket::~ServeurSocket() {

	this->fermerSocket();
}

int ServeurSocket::associerConnexion() {

	// Association de l'addresse locale avec le socket
	int status = bind(mSocket, (const sockaddr*)&mSocketAddress, sizeof(mSocketAddress));

	// Gestion des erreurs
	if (status == SOCKET_ERROR) {

		return ERREUR_SOCKET;
	}
	else {

		return SUCCES_SOCKET;
	}
}

int ServeurSocket::ecouterReseau() {

	// Ecoute le r�seau
	int status = listen(mSocket, SOMAXCONN);

	// Gestion des erreurs
	if (status == SOCKET_ERROR) {

		return ERREUR_SOCKET;
	}
	else {

		return SUCCES_SOCKET;
	}
}

int ServeurSocket::accepterConnexion() {

	socklen_t socketAddrSize = sizeof(mSocketAddress);

	// Attend une connexion
	mSocketCommunication = accept(mSocket, (sockaddr*)&mSocketAddress, &socketAddrSize);

	// Gestion des erreurs
	if (mSocketCommunication == SOCKET_ERROR) {

		return ERREUR_SOCKET;
	}
	else {

		return SUCCES_SOCKET;
	}
}

int ServeurSocket::start() {

	/* 1: association */
	int statutAssociation = this->associerConnexion();

	if(statutAssociation == SUCCES_SOCKET) {

		/* 2: ecoute */
		int statutEcoute = this->ecouterReseau();

		if(statutEcoute == SUCCES_SOCKET) {

			/* 3: acceptation */
			int statutAcceptation = this->accepterConnexion();

			if(statutAcceptation == SUCCES_SOCKET) {

				return statutAcceptation;
			}
		}
	}

	return ERREUR_SOCKET;
}

int ServeurSocket::envoyerMessage(const char* message) {

	// Tentative d'envoi du message
	int status = send(mSocketCommunication, message, (size_t)strlen(message) * sizeof(char), 0);

	// Gestion des erreurs
	if (status == SOCKET_ERROR) {

		return ERREUR_SOCKET;
	}
	else {

		return SUCCES_SOCKET;
	}
}

std::string ServeurSocket::recevoirMessage() {

	char superBuffer[BUFLEN] = { 0 };

	int status = recv(mSocketCommunication, superBuffer, BUFLEN, 0);

	// Gestion des erreurs
	if(status == SOCKET_ERROR) {

		return "NOK";
	}
	else {

		std::string messageRecu(superBuffer);

		return messageRecu;
	}
}

void ServeurSocket::fermerSocket() {

	// Fermeture du socket
#ifdef _WIN32
	int statusComm = closesocket(mSocketCommunication);
	int statusListen = closesocket(mSocket);
#endif

#ifdef __unix__
	int statusComm = close(mSocketCommunication);
	int statusListen = close(mSocket);
#endif

	// Gestion des erreurs
	if (statusComm == SOCKET_ERROR || statusListen == SOCKET_ERROR) {

		fprintf(stderr, "%s\n", GestionErreurSocket::GetLastSocketErrorAsString());
	}
}

