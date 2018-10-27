/***********************************************
*���	        ___���� _������ _
*�  	       / __|� _| |_�� _| |_
*� 	          | (__� |_�� _| |_�� _|
*��	           \___|�� |_|���� |_|
*
*���������           SOCKET
*
*	             ClientSocket.h
*�� 	         Micka�l Debalme
*�                07/10/2017 (V2)
*       Classe de gestion d'une connexion
*                 socket client
*            H�rite de CommonSocket
*
*���           Copyright (C) 2017
*
**********************************************/

#pragma once

#include "../../ClasseCommonSocket/CommonSocket.h"

class ClientSocket : public CommonSocket {

public:

	/* Constructeur & destructeur */
	ClientSocket(const char* adresseIp, int port);
	~ClientSocket();

	int connecterServeur();
	
	int envoyerMessage(const char* message);
	
	std::string recevoirMessage();

protected:

private:
};
