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
	printf("3 Listar Vertices adjacentes\n");
	printf("4 Inserir Meio\n");
	printf("5 Listar Meios por localizacao\n");
	printf("6 Inserir Cliente\n");
	printf("7 Listar Clientes por localizacao\n");
	printf("8 Guardar Meios\n");
	printf("9 Ler Meios\n");
	printf("10 Guardar Clientes\n");
	printf("11 Ler Clientes\n");
	printf("12 Guardar Grafo\n");
	printf("13 Ler Grafo\n");
	printf("14 Listar Meios num determinado raio a volta do cliente\n");
	printf("0 Sair\n");
	printf("Opcao:\n");
	scanf("%d", &op);
	printf("-------------------------------------------\n");
	return(op);
}

int main()
{

    Grafo g = NULL;
	int caminho[TAM];

	char tipoveiculo[40], geocodigo[TAM], localizacaoVertice[TAM], verticeinico[TAM],verticefim[TAM],nomecliente[50],localizacao[TAM];
	int codigo,op,numerocliente,resultado;
	float bateria,peso,distancia;

	do
	{
		op = menu();
		switch (op)
		{
		case 1: printf("Geocodigo do novo vertice do grafo:\n");
			scanf("%s", &localizacaoVertice);
			resultado=criarVertice(&g, localizacaoVertice);
			printf("-------------------------------------\n");
			if (resultado==1)
			{
				printf("Novo vertice criado com sucesso\n");
			}
			else if (resultado==0)
			{
				printf("Erro ao criar o vertice\n");
			}
			break;

		case 2:printf("Localizacao primeiro vertice da aresta\n");
			scanf("%s", &verticeinico);
			printf("Localizacao segundo vertice:\n");
			scanf("%s", &verticefim);
			printf("Peso entre vertices:\n");
			scanf("%f", &peso);
			resultado=criarAresta(g, verticeinico, verticefim, peso);
			printf("-------------------------------------\n");
			if (resultado==1)
			{
				printf("Aresta criada com sucesso \n");
			}
			else if (resultado==-1)
			{
				printf("A localizacao do primeiro ou segundo vertice nao existem no grafo\n");
			}
			else
			{
				printf("Nao foi possivel criar a aresta \n");
			}
			
			break;

		case 3:printf("Localizacao do vertice no qual queremos ver os adjacentes: \n");
			scanf("%s", &geocodigo);
			printf("-------------------------------------------------\n");
			listarAdjacentes(g, geocodigo);
			break;

		case 4: printf("Tipo de meio:\n");
			scanf("%s", &tipoveiculo);
			printf("Localizacao do meio:\n");
			scanf("%s", &geocodigo);
			printf("Codigo do meio:\n");
			scanf("%d", &codigo);
			printf("Nivel de bateria: \n");
			scanf("%f", &bateria);
			printf("--------------------------------------------\n");
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
			
		case 5: printf("Localizacao para procurar os meios:\n");
			scanf("%s", &geocodigo);
			printf("----------------------------------------\n");
			listarMeios(g, geocodigo);
			break;

		case 6: printf("Nome do cliente:\n");
			scanf("%s", &nomecliente);
			printf("Localizacao do cliente:\n");
			scanf("%s", &geocodigo);
			printf("Número de cliente:\n");
			scanf("%d", &numerocliente);
			resultado=inserirCliente(g, nomecliente, geocodigo, numerocliente);
			printf("----------------------------------------\n");
			if (resultado == 1)
			{
				printf("Cliente inserido com sucesso\n");
			}
			else if (resultado == 0)
			{
				printf("Erro!! O grafo está vazio\n");
			}
			break;

		case 7:printf("Localizacao onde seram procurados os clientes:\n");
			scanf("%s", &geocodigo);
			printf("----------------------------------------------\n");
			listarClientes(g, geocodigo);
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
				printf("Erro na abertura do ficheiro\n");
			}
			break;
		case 12: resultado = GuardarGrafo(g);

			if (resultado==0)
			{
				printf("Grafo guardado com sucesso\n");
			}
			if (resultado == -1)
			{
				printf("Erro ao guardar o grafo\n");
			}
			break;

		case 13:



			break;

		case 14: 
			printf("Indique a localizacao do cliente:\n");
			scanf("%s", &localizacao);
			printf("Indique o raio em metros:\n");
			scanf("%f", &distancia);
			printf("Indique o tipo de meio de transporte: \n");
			scanf("%s", &tipoveiculo);
			printf("-------------------------------------------\n");
			ListarporDistancia(g, distancia, localizacao,tipoveiculo);
			break;


		default: printf("Opcao invalida!!!\n");

		}
	} while (op != 0);

}
