/*
 * nivel_library.h
 *
 *  Created on: 18/04/2013
 *      Author: utnso
 */

#ifndef NIVEL_LIBRARY_H_
#define NIVEL_LIBRARY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <commons/config.h>
#include <commons/string.h>
#include <commons/collections/list.h>
#include <commons/Connections/EstructurasMensajes.h>
#include <so-nivel-gui-library-master/nivel-gui/nivel.h>


/*define el tipo t_nivel, que representa un nivel creado a partir de un archivo de configuracion dado
con toda su estructura de datos
	*/
typedef struct t_nivel{
	ITEM_NIVEL *nivel_items;
	Direccion nivel_orquestador;
	long nivel_tiempo_deadlock;
	int nivel_recovery;
	} t_nivel;

t_nivel *read_nivel_archivo_configuracion(char* path);
t_nivel *create_nivel(t_config *n);
ITEM_NIVEL *create_lista_cajas(t_config *n);
void imprimir_lista_cajas(t_list *cajas);
void ListItems_add_caja(t_config *n, char *buffer_caja_num, ITEM_NIVEL **list);


/*funciones para usar en el dibujo de nivel
	*/
ITEM_NIVEL *crear_lista_items(t_list *cajas, t_list *personajes);
void add_personaje_item_nivel(t_personaje_en_nivel *personaje, ITEM_NIVEL **list, char tipo);
void BorrarItem(ITEM_NIVEL** i, char id);
void MoverPersonaje(ITEM_NIVEL* ListaItems, char id, int x, int y);

#endif /* NIVEL_LIBRARY_H_ */
