/*
 * Proceso Server.h
 *
 *  Created on: 13/04/2013
 *      Author: utnso
 */

#ifndef PROCESO_SERVER_H_
#define PROCESO_SERVER_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <fcntl.h>
#include "collections/queue.h"
//#define MYPORT 3490
// Puerto al que conectarán los usuarios

#define BACKLOG 20
// Cuántas conexiones pendientes se mantienen en cola

#define MAXEVENTS 20
// Cuántas conexiones atiende y supervisa.

typedef struct {
	char name [20];
	int fd;
} Conexion;

typedef struct {
	int from;			//fileDescriptor de la conexion
	char type;
	uint16_t lenght;
	void* data;
} Mensaje;


////PROTOTIPOS DE FUNCIONES
void Cerrar_Conexion (int);
static int make_socket_non_blocking (int);
int initServer(int);
int mensajes(t_queue* , t_list* );
int mandarMensaje( int , char , uint16_t, void*);
int obtenerData(void* ,Mensaje* );
//void setConnectionName(t_list , int, char*);

#endif /* PROCESO_SERVER_H_ */
