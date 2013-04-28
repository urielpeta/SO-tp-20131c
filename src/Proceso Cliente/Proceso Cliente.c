/*
 * Proceso Cliente.c
 *
 *  Created on: 17/04/2013
 *      Author: utnso
 */
#include "Proceso Cliente.h"

int instancia_epoll;			// Instancia epoll
int sockfd, new_fd; 			// Escuchar sobre sock_fd, nuevas conexiones sobre new_fd
struct epoll_event event;		//
struct epoll_event *events;
struct sockaddr_in my_addr; 	// Información sobre mi dirección

/*
 * @NAME: connectServer
 * @DESC: Conecta a un  servidor. Recibe ip en formato string (ej "127.101
 * 		  type: codigo de mensaje, lenght: size of (variable que se adjunta),
 * 		  data: dirección de la variable a adjuntar.
 */
int connectServer(char *IP, int PORT){
	int sockfd; 					// Escuchar sobre sock_fd, nuevas conexiones sobre new_fd
	struct sockaddr_in their_addr; 	// Información sobre mi dirección
	struct hostent *server; 		// Información sobre el server


	////OBTENER INFORMACIÓN DEL SERVER
		if ((server = gethostbyname(IP)) == NULL) { // obtener información de máquina
		perror("gethostbyname");
		exit(1);
		}

		////SETEO CONFIGURACIONES DE IP + PUERTO
		their_addr.sin_family = AF_INET;  // Ordenación de bytes de la máquina
		their_addr.sin_port = htons(PORT); // short, Ordenación de bytes de la	red
		their_addr.sin_addr = *((struct in_addr *)server->h_addr);
		memset(&(their_addr.sin_zero), '\0', 8); // Poner a cero el resto de la estructura


		////PIDO EL SOCKET
		if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
			perror("socket");
			exit(1);
		}


	////INTENTO CONECTAR
		if (connect(sockfd, (struct sockaddr *)&their_addr,	sizeof(struct sockaddr)) == -1) {
			perror("connect");
			exit(1);
		}
		printf("Conectado con host \n");


	return sockfd;

}


void closeConnection (int fd){

	//CIERRO CONEXION
	close (fd);
	printf ("Desconectado del host\n");

}


/*
 * @NAME: mandarMensaje
 * @DESC: Envia un mensaje al descriptor que recibe como parametro. El resto son:
 * 		  type: codigo de mensaje, lenght: size of (variable que se adjunta),
 * 		  data: dirección de la variable a adjuntar.
 */
int mandarMensaje( int fd , char type, uint16_t lenght, void*data){
	char mensaje[lenght+3];
	mensaje[0]=type;
	memcpy(&mensaje[1],(void*)(&lenght),2);
	memcpy(&mensaje[3],(void*)data,lenght);

	if((send(fd , mensaje, lenght+3, 0)) == -1){
		return -1;
	}

	return 0;

}


/*
 * @NAME: obtenerData
 * @DESC: Recibe como parametro un puntero a la variable que se quiera recuperar
 * 		  del dato adjunto en el mensaje que recibe como parametro.
 */
int obtenerData(void* destino, Mensaje* miMensaje){
	memcpy(destino, (void*) miMensaje->data, miMensaje->lenght);
	return 0;

}


int make_socket_non_blocking (int sfd)
{
  int flags, s;

  flags = fcntl (sfd, F_GETFL, 0);
  if (flags == -1)
    {
      perror ("fcntl");
      return -1;
    }

  flags |= O_NONBLOCK;
  s = fcntl (sfd, F_SETFL, flags);
  if (s == -1)
    {
      perror ("fcntl");
      return -1;
    }

  return 0;
}

