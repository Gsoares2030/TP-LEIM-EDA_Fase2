#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable: 4996)
#define TAM 50

typedef struct registo4
{
	int numerocliente; /*numero de cliente*/
	char nome[50];  /*nome do cliente*/
	char localizacao[TAM];/*Localização cliente*/
	struct registo4* seguinte; /*endereço de memoria para o proximo cliente*/
} *Cliente;

typedef struct registo3
{
	char tipotransporte[40];/*Tipo de Transporte*/
	int codigo;/*Codigo do meio de mobilidade*/
	char geocodigo[TAM]; /*Geocodigo onde se encontra o veiculo*/
	float bateria;/*Nivel de bateria do Meio de mobilidade*/
	struct registo3* seguinte; /*endreço de memoria para o proximo meio*/
} *Meios;


/*Representação de um grafo orientado e pesado*/ 
typedef struct registo2
{
	char vertice[TAM]; /*geocódigo what3words*/ 
	float peso; /*distancia de um meio ao outro*/
	struct registo2* seguinte; /*endereço de memoria para o proximo vertice adjacente*/
} *Adjacente;

typedef struct registo1
{
	char vertice[TAM]; /*geocódigo what3words*/ 
	Adjacente adjacentes;
	Meios meios; /*Lista ligada com os códigos dos meios de transporte existente neste geocódigo*/
	Cliente cliente;
	struct registo1* seguinte;
} *Grafo;

int inserirMeio(Grafo g, char tipotransporte[], char geocodigo[], int codigoMeio, float bateria);
void listarMeios(Grafo g, char geocodigo[]);
int criarVertice(Grafo* g, char novoId[]);
int existeVertice(Grafo g, char vertice[]);
int criarAresta(Grafo g, char vOrigem[], char vDestino[], float peso);
void listarAdjacentes(Grafo g, char vertice[]);
int inserirCliente(Grafo g, char nome[], char localizacaocliente[], int numerocliente);
void listarClientes(Grafo g, char localização[]);
int GuardarMeios(Grafo g);
int LerMeios(Grafo g);
int GuardarClientes(Grafo g);
int LerClientes(Grafo g);
void ListarporDistancia(Grafo g, int distancia, char localizacao[]);


