/***********************************************
*   	        ___     _       _
*   	       / __|  _| |_   _| |_
*  	          | (__  |_   _| |_   _|
*  	           \___|   |_|     |_|
*
*                    SOCKET
*
*	             ServeurSocket.h
*   	         Mickaël Debalme
*                 07/10/2017 (V2)
*       Classe de gestion d'une connexion
*                 socket serveur
*            Hérite de CommonSocket
*
*              Copyright (C) 2017
*
**********************************************/

#pragma once

// Inclusion de la classe m�re
#include "../../ClasseCommonSocket/CommonSocket.h"

/* Classe ServeurSocket qui h�rite de CommonSocket */
class ServeurSocket : public CommonSocket {

	/* M�thodes public */
public:

	/* Constructeur & destructeur */
	ServeurSocket(int port);
	virtual ~ServeurSocket();

	/* Démarre le serveur et attend une connexion */
	int start();

	/* Envoie un message via socket */
	virtual int envoyerMessage(const char* message);

	/* Re�oit un message via socket */
	virtual std::string recevoirMessage();


	/* M2thodes private */
private:

	/* Connecte le tunnel des deux c�t�s */
	int associerConnexion();

	/* Attend un message */
	int ecouterReseau();

	/* Re�oit et accepte une connexion */
	int accepterConnexion();

	/* Ferme les sockets */
	void fermerSocket();


	/* Attributs private */
private:

	/* Socket servant � la communication */
	SOCKET mSocketCommunication;

};
