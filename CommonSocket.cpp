/***********************************************
*   	        ___     _       _
*   	       / __|  _| |_   _| |_
*  	          | (__  |_   _| |_   _|
*  	           \___|   |_|     |_|
*
*                    SOCKET
*
*	            CommonSocket.cpp
*   	         Mickaël Debalme
*                 07/10/2017 (V2)
*    Classe mère de gestion d'une connexion
*                    socket
*
*              Copyright (C) 2017
*
**********************************************/

#include "CommonSocket.h"

/* Constructeur du serveur */
CommonSocket::CommonSocket(int port) {

	// Attribution des valeurs aux attributs de la classe
	strcpy(mAdresseIp, "");
	mPort = port;
	mSocket = 0;

#ifdef _WIN32
	// Initialisation de la dll
	this->initialiserDLL();
#endif

	// Initialisation de la structure sockaddr_in
	this->initialiserStructureServeur();

	// Création du socket d'écoute
	this->creerSocket();
}

/* Constructeur du client */
CommonSocket::CommonSocket(const char* adresseIp, int port) {

	// Attribution des valeurs aux attributs de la classe
	strcpy(mAdresseIp, adresseIp);
	mPort = port;
	mSocket = 0;

#ifdef _WIN32
	// Initialisation de la dll
	this->initialiserDLL();
#endif

	// Initialisation de la structure sockaddr_in
	this->initialiserStructureClient();

	// Création du socket d'écoute
	this->creerSocket();
}

CommonSocket::~CommonSocket() {

	this->fermerSocket();

#ifdef _WIN32
	this->fermerDLL(); // Fermeture de la dll
#endif
}


/* Les m�thodes concernant la DLL ne sont utilis�es que sous Windows */
#ifdef _WIN32

void CommonSocket::initialiserDLL() {

	// Fixe la version de la DLL socket pour l'application � 2;
	wVersionRequested = MAKEWORD(2, 2);

	// Traitement des erreurs pour API Windows
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		mDLL_OK = false; // On pr�cise que la dll n'a pas �t� charg�e

		fprintf(stderr, "DLL ERROR: %s\n", GestionErreurSocket::GetLastSocketErrorAsString());
	}
	else {

		mDLL_OK = true; // On pr�cise que la dll a �t� charg�e
	}
}

void CommonSocket::fermerDLL() {

	/* On ferme la dll si elle a bien �t� charg�e */
	if (mDLL_OK) {

		//Fin d'utilisation de la DLL
		WSACleanup();
	}
}

#endif
/* Fin condition */


void CommonSocket::initialiserStructureServeur() {

	// D�finition des attributs de la structure
	mSocketAddress.sin_family = AF_INET;

	/* D�finition de l'adresse */
	mSocketAddress.sin_addr.s_addr = htonl(INADDR_ANY); // Le serveur recoit toutes les adresses

	mSocketAddress.sin_port = htons(mPort);
}

void CommonSocket::initialiserStructureClient() {

	// D�finition des attributs de la structure
	mSocketAddress.sin_family = AF_INET;

	/* D�finition de l'adresse */
	inet_pton(AF_INET, mAdresseIp, &mSocketAddress.sin_addr.s_addr); // On indique l'adresse du serveur

	mSocketAddress.sin_port = htons(mPort);
}


int CommonSocket::creerSocket() {

	// Cr�ation du socket
	mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// Gestion des erreurs
	if (mSocket == SOCKET_ERROR) {

		return ERREUR_SOCKET;
	}
	else {

		return SUCCES_SOCKET;
	}
}


int CommonSocket::envoyerMessage() {

	return 0;
}

std::string CommonSocket::recevoirMessage() {

	return nullptr;
}


void CommonSocket::fermerSocket() {

	// Fermeture du socket
#ifdef _WIN32
	int status = closesocket(mSocket);
#endif

#ifdef __unix__
	int status = close(mSocket);
#endif
	// Gestion des erreurs
	if (status == SOCKET_ERROR) {

		fprintf(stderr, "SOCKET ERROR: %s\n", GestionErreurSocket::GetLastSocketErrorAsString());
	}
}
