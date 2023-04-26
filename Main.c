/*****************************************************************//**
 **\author: Gonçalo Soares
 * \brief: Projeto EDA fase 2
 *  
  *********************************************************************/


#include "Header.h";

int menu()
{
	int op;
	printf("--------------------------------------------\n");
	printf("M E N U\n");
	printf("1 Criar Vertice\n");
	printf("2 Criar Aresta\n");
	printf("3 Listar Vertices adjacentes");
	printf("4 Inserir Meio\n");
	printf("5 Listar Meios por Localização\n");
	printf("6 Inserir Cliente\n");
	printf("7 Listar Clientes por localização\n");
	printf("8 Guardar Meios\n");
	printf("9 Ler Meios\n");
	printf("10 Guardar Clientes");
	printf("11 Ler Clientes");
	printf("0 Sair\n");
	printf("Opcao:\n");
	scanf("%d", &op);
	printf("-------------------------------------------\n");
	return(op);
}

int main()
{

    Grafo g = NULL;

	char tipoveiculo, geocodigo, localizacaoVertice, verticeinico,verticefim,nomecliente;
	int codigo,op,peso,numerocliente,resultado;
	float bateria;

	do
	{
		op = menu();
		switch (op)
		{
		case 1: printf("Geocodigo do novo vertice do grafo:\n");
			scanf("%s", &localizacaoVertice);
			resultado=criarVertice(&g, localizacaoVertice);
			if (resultado==1)
			{
				printf("Novo vertice criado com sucesso\n");
			}
			else if (resultado==0)
			{
				printf("Erro na criação do vertice\n");
			}
			break;

		case 2:printf("Localização primeiro vertice da aresta\n");
			scanf("%s", &verticeinico);
			printf("Localização segundo vertice:\n");
			scanf("%s", &verticefim);
			printf("Peso entre vertices:\n");
			scanf("%d", &peso);
			resultado=criarAresta(g, verticeinico, verticefim, peso);
			if (resultado==1)
			{
				printf("Aresta criada com sucesso \n");
			}
			else if (resultado==-1)
			{
				printf("A localização do primeiro ou segundo vertice não existem no grafo\n");
			}
			else
			{
				printf("Não foi possivel criar a aresta \n");
			}
			
			break;

		case 3:printf("Localização do vertice no qual queremos ver os adjacentes: \n");
			scanf("%s", &geocodigo);
			listarAdjacentes(g, geocodigo);
			break;

		case 4: printf("Tipo de meio:\n");
			scanf("%s", &tipoveiculo);
			printf("Localização do meio:\n");
			scanf("%s", &geocodigo);
			printf("Codigo do meio:\n");
			scanf("%d", &codigo);
			printf("%0.2f", &bateria);
			printf("*******************************\n");
			resultado=inserirMeio(g, tipoveiculo, geocodigo, codigo,bateria);
			if (resultado== 1)
			{
				printf("Meio inserido com sucesso\n");
			}
			else if (resultado==0)
			{
				printf("Erro!! O grafo está vazio\n");
			}
			break;
			
		case 5: printf("Localização para procurar os meios:\n");
			scanf("%s", &geocodigo);
			printf("*******************************\n");
			listarMeios(g, geocodigo);
			printf("*******************************\n");
			break;

		case 6: printf("Nome do cliente:\n");
			scanf("%s", &nomecliente);
			printf("Localização do cliente:\n");
			scanf("%s", &geocodigo);
			printf("Número de cliente:\n");
			scanf("%d", &numerocliente);
			resultado=inserirCliente(g, nomecliente, geocodigo, numerocliente);
			if (resultado == 1)
			{
				printf("Cliente inserido com sucesso\n");
			}
			else if (resultado == 0)
			{
				printf("Erro!! O grafo está vazio\n");
			}
			break;

		case 7:printf("Localização onde seram procurados os clientes:\n");
			scanf("%s", &geocodigo);
			printf("----------------------------------------------\n");
			listarClientes(g, geocodigo);
			printf("----------------------------------------------\n");
			break;

		case 8:
			resultado=GuardarMeios(g);
			if (resultado==1)
			{
				printf("Meios Guardados com sucesso\n");
			}
			else if (resultado==0)
			{
				printf("Erro na abertura do ficheiro\n");
			}
			break;

		case 9: resultado = LerMeios(g);
			if (resultado==1)
			{
				printf("Meios lidos com sucesso\n");
			}
			else if (resultado==0)
			{
				printf("Erro na abertura do ficheiro");
			}
			break;

		case 10:
			resultado = GuardarClientes(g);
			if (resultado == 1)
			{
				printf("Clientes Guardados com sucesso\n");
			}
			else if (resultado == 0)
			{
				printf("Erro na abertura do ficheiro\n");
			}
			break;

		case 11: resultado = LerClientes(g);
			if (resultado == 1)
			{
				printf("Clientes lidos com sucesso\n");
			}
			else if (resultado == 0)
			{
				printf("Erro na abertura do ficheiro");
			}
			break;

		}
	} while (op != 0);

	return 0;
}
