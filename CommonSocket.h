/***********************************************
*   	        ___     _       _
*   	       / __|  _| |_   _| |_
*  	          | (__  |_   _| |_   _|
*  	           \___|   |_|     |_|
*
*                    SOCKET
*
*	             CommonSocket.h
*   	         Mickaël Debalme
*                 07/10/2017 (V2)
*    Classe mère de gestion d'une connexion 
*                    socket
*
*              Copyright (C) 2017
*
**********************************************/


#pragma once

#include <iostream>

#define BUFLEN 1024 // Taille du buffer de r�ception
#define SUCCES_SOCKET 1
#define ERREUR_SOCKET -1

#ifdef _WIN32

/* Winsock 2 */
#include <winsock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib") // Chargement de la dll pour visual

#endif

#ifdef __unix__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* D�finition des types */
typedef int SOCKET;

#define SOCKET_ERROR -1

#endif

/* Classe GestionErreurSocket */
#include "../ClasseGestionErreur/GestionErreurSocket.h"

/* Classe CommonSocket */
class CommonSocket {

	/* M�thodes public */
public:

	/* Constructeurs & destructeur */
	CommonSocket(int port); // Constructeur pour le serveur
	CommonSocket(const char* adresseIp, int port); // Constructeur pour le client
	virtual ~CommonSocket();

	/* Envoie un message via socket */
	virtual int envoyerMessage();

	/* Re�oit un message via socket */
	virtual std::string recevoirMessage();


	/* M�thodes private */
private:

#ifdef _WIN32
	/* Initialise la dll et g�re les erreurs */
	void initialiserDLL();

	/* Ferme la dll si elle a �t� ouverte */
	void fermerDLL();
#endif

	/* Cr�e le socket d'ecoute */
	int creerSocket();

	/* Initialise la structure */
	void initialiserStructureServeur();
	void initialiserStructureClient();

	/* Ferme le ou les socket */
	virtual void fermerSocket();

	/* Attributs protected */
protected:

	/* Variables SOCKET */
	SOCKET mSocket;

	/* Structure socket */
	sockaddr_in mSocketAddress;

	/* Informations de connexion */
	char mAdresseIp[17];
	int mPort;


	/* Attributs private */
private:

#ifdef _WIN32
	/* D�claration des donn�es pour WSAStartup (pour le chargement de la dll) */
	WORD wVersionRequested;
	WSADATA wsaData;

	/* Indique l'�tat du chargement de la dll */
	bool mDLL_OK;
#endif
};
