/*****************************************************************//**
 **\author:Gonçalo Soares
 * \brief:Funções utilizadas na resolução da segunda fase do projeto
 *  
  *********************************************************************/

#include "Header.h"
#include <limits.h>


#pragma warning(disable: 4996)
 
#pragma region Meios
/**
 * \Enter: Entra o grafo, o geocodigo do novo meio e o codigo do novo meio
 * \brief: A função vai inserir meio de transporte na localização com geocódigo passado por parâmetro
 * \return: Devolve 1 em caso de sucesso ou 0 caso contrário
 */
int inserirMeio(Grafo g, char tipotransporte[],char geocodigo[], int codigoMeio, float bateria)
{
    while ((g!= NULL) && (strcmp(g->vertice, geocodigo) != 0))
        g = g->seguinte;
    if (g == NULL)
        return(0);
    else {
        Meios novo = malloc(sizeof(struct registo3));
        strcpy(novo->tipotransporte, tipotransporte);
        strcpy(novo->geocodigo, geocodigo);
        novo->codigo = codigoMeio;
        novo->bateria = bateria;
        novo->seguinte = g->meios;
        g->meios = novo;
        return(1);
    }
}

/*
 * \Enter: Entra o endereço inicial do grafo e o nome do novo vertice 
 * \brief: A função irá um grafo novo (auxiliar) onde irá guardar o nome do novo vertice, os meios exitentes nesse vertice
 e depois irá guardar no endereço seguinte o endereço inicial do grafo ja existente e vai mudar de seguida o endereço inicial do grafo para o endereço inicial do novo vertice.
 * \return:  Devolve 1 em caso de sucesso ou 0 caso contrário
 * 
 */
int criarVertice(Grafo* g, char novoId[])
{
    Grafo novo = malloc(sizeof(struct registo1));
    if (novo != NULL)
    {
        strcpy(novo->vertice,novoId);
        novo->meios = NULL;
        novo->cliente = NULL;
        novo->seguinte = *g;
        novo->adjacentes = NULL;
        *g = novo;
        return(1);
    }
    else return(0);
}

/**
 * \Enter: Entra o grafo e o geocodigo no qual iremos ver quais meios exitem nessa localização 
 * \brief:Lista os códigos dos meios de transporte presente numa determinada localização passada por parâmetro 
 */
void listarMeios(Grafo g, char geocodigo[])
{
    while ((g != NULL) && (strcmp(g->vertice, geocodigo)!= 0))
        g = g->seguinte;
    if (g != NULL)
    {
        Meios aux = g->meios;
        if (aux == NULL) printf("sem meios de transporte\n");
        else while (aux != NULL)
        {
            printf("Codigo meio: %d \n Tipo transporte: %s\n Nivel de bateria %.2f\n", aux->codigo,aux->tipotransporte,aux->bateria);
            aux = aux->seguinte;
            printf("----------------------------------------\n");
        }
    }
    else printf("geocodigo inexistente\n");
}

/**
 * 
 * \Enter: Entra o grafo e o vertice que queremos procurar
 * \brief: A função irá comparar os vertices exitentes no grafo, com o que queremos procurar
 * \return: Devolve 1 se o vertice existe no grafo ou 0 caso contrário
 */
int existeVertice(Grafo g, char vertice[])
{
    while (g != NULL)
    {
        if (strcmp(g->vertice, vertice) == 0) 
            return(1);
        else
            g = g->seguinte;
    }
    return(0);
}


/**
 * \Enter: Entra o grafo, o vertice de origem e de destino da aresta que queremos e o peso dessa aresta
 * \brief: A função irá criar uma aresta, para isso verifica se os vertices pedidos existem, caso exista ira criar uma aresta 
 * \return: Devolve 1 em caso de sucesso ou 0 caso contrário
 * 
 */
int criarAresta(Grafo g, char vOrigem[], char vDestino[], float peso)
{
    Adjacente novo;
    if (existeVertice(g, vOrigem) && existeVertice(g, vDestino))
    {
        while (strcmp(g->vertice, vOrigem) != 0)
            g = g->seguinte;
        novo = malloc(sizeof(struct registo2));
        if (novo != NULL)
        {
            strcpy(novo->vertice, vDestino);
            novo->peso = peso;
            novo->seguinte = g->adjacentes;
            g->adjacentes = novo;
            return(1);
        }
        else return(0);
    }
    else return(-1);
}
/**
 * \Enter: Entra o grafo e o vertice no qual queremos ver os adjacenetes
 * \brief: A função irá verificar a existencia desse vertice no grafo e de seguida irá listar os adjacentes
 */
void listarAdjacentes(Grafo g, char vertice[])
{
    Adjacente aux;
    if (existeVertice(g, vertice))
    {
        while (strcmp(g->vertice, vertice) != 0)
            g = g->seguinte;
        aux = g->adjacentes;
        if (aux == NULL)
        {
            printf("O vertice do grafo indicado nao tem adjacentes\n");
        }
        while (aux != NULL)
        {
            printf("Adjacente:%s  Peso:%.2f\n", aux->vertice, aux->peso);
            aux = aux->seguinte;
        }
        
    }
    else
    {
        printf("O vertice indicado nao existe \n");
    }
}

/**
 * 
 * \Enter: Entra o grafo
 * \brief: A função vai guardando os meios presentes na lista ligada
 * \return: Devolve 1 em caso de sucesso e 0 caso haja algum erro
 * 
 */
int GuardarMeios(Grafo g)
{
    FILE* fp;
    fp = fopen("meios2.txt", "w");
    if (fp != NULL)
    {
        Meios aux = g->meios;
        while (aux!= NULL)
        {
            fprintf(fp, "%s;%s;%d;%.2f;\n", aux->tipotransporte, aux->geocodigo,aux->codigo,aux->bateria);
            aux = aux->seguinte;
        }
        fclose(fp);
        return(1);
    }
    else return(0);
}

/**
 * 
 * \Enter: Entra o grafo 
 * \brief: A função irá ler os meios presentes no ficheiro de texto e de seguida vai inserir os meios no grafo.
 * \return: Devolve 1 em caso de sucesso e 0 caso haja algum erro
 * 
 */
int LerMeios(Grafo g)
{
    FILE* fp;
    int cod;
    char tipotransporte[TAM],geocodigo[TAM];
    float bateria;
    fp = fopen("meios2.txt", "r");
    if (fp != NULL)
    {
        while (!feof(fp))
        {
            fscanf(fp, "%[^;];%[^;];%d;%.2f;\n",tipotransporte,geocodigo,&cod,&bateria);
            inserirMeio(g, tipotransporte, geocodigo,cod,bateria);
        }
        fclose(fp);
        return (1);
    }
    return(0);
}


/**
 * 
 * \Enter: Entra o grafo
 * \brief: A função vai guardar num ficheiro de texto os vertices do grafo e os adjacntes a esses vertices, vem como o peso das arestas
 * \return: Retorna 0 em caso de
 * 
 */
int GuardarGrafo(Grafo g)
{
    Adjacente adj;
    FILE* fp;
    fp = fopen("grafo.txt", "w");
    if (fp != NULL)
    {
        while (g!= NULL)
        {
            adj = g->adjacentes;

            while (adj != NULL)
            {
                fprintf(fp, "%s;%s;%.2f;\n", g->vertice, adj->seguinte->vertice, adj->peso);
                adj = adj->seguinte;
            }
            g = g->seguinte;
        }
        return (1);
    }
    return (0);
}


/**
 * 
 * \Enter: Entra e o apontador para o inicio do grafo e o conteudo do grafo
 * \brief: A função vai ler o conteudo do ficheiro e guardae os diferentes parametros em variaveis. De seguida vai criar os vertices no grafo
 *  e as arestas com os diferentes pesos entre os vertices
 * \return: Retorna 1 em caso de sucesso e 0 em caso de erro
 * 
 */
int LerGrafo(Grafo g,Grafo* g1)
{
    FILE* fp;
    char vertice[TAM], verticeadjacente[TAM];
    float peso;
    fp = fopen("grafo.txt", "r");
    if (fp != NULL)
    {
        while (!feof(fp))
        {
            fscanf(fp, "%[^;];%[^;];%d;%.2f;\n", vertice, verticeadjacente, &peso);
            criarVertice(g1, vertice);
            criarAresta(g, vertice, verticeadjacente, peso);
        }
        fclose(fp);
        return (1);
    }
    return(0);
}

#pragma endregion

#pragma region Cliente

/**
 * \Enter: Entra o grafo,o nome do cliente, o localização do novo cliente e o numero de cliente do novo meio
 * \brief: A função vai inserir o cliente na localização passado por parâmetro
 * \return: Devolve 1 em caso de sucesso ou 0 caso contrário
 */
int inserirCliente(Grafo g, char nome[], char localizacaocliente[], int numerocliente)
{
    while ((g != NULL) && (strcmp(g->vertice, localizacaocliente) != 0))
        g = g->seguinte;
    if (g == NULL)
        return(0);
    else {
        Cliente novo = malloc(sizeof(struct registo4));
        strcpy(novo->nome,nome);
        strcpy(novo->localizacao,localizacaocliente);
        novo->numerocliente =numerocliente;
        novo->seguinte = g->cliente;
        g->cliente = novo;
        return(1);
    }
}
/**
 * \Enter: Entra o grafo e o geocodigo no qual iremos ver quais clientes exitem nessa localização
 * \brief:Lista os nomes dos clientes e o número de cliente dos cleintes presente numa determinada localização passada por parâmetro
 */
void listarClientes(Grafo g, char localização[])
{
    while ((g != NULL) && (strcmp(g->vertice, localização) != 0))
        g = g->seguinte;
    if (g != NULL)
    {
        Cliente aux = g->cliente;
        if (aux == NULL)
            printf("Sem clientes na localização indicada\n");
        else while (aux != NULL)
        {
            printf("Nome cliente: %s\n Numero de Clinte: %d\n", aux->nome,aux->numerocliente);
            aux = aux->seguinte;
        }
    }
    else printf("Localização inexistente\n");
}


/**
 * 
 * \Enter: Entra o grafo
 * \brief: A função vai guardando no ficheiro de texto os clinetes presentes na lista ligada
 * \return: Devolve 1 caso guarde com sucesso e 0 caso haja algum erro
 * 
 */
int GuardarClientes(Grafo g)
{
    FILE* fp;
    fp = fopen("clientes2.txt", "w");
    if (fp != NULL)
    {
        Cliente aux = g->cliente;
        while (aux != NULL)
        {
            fprintf(fp, "%s;%s;%d;\n", aux->nome,aux->localizacao,aux->numerocliente);
            aux = aux->seguinte;
        }
        fclose(fp);
        return(1);
    }
    else return(0);
}

/**
 * 
 * \Enter: Entra o grafo 
 * \brief: A função vai lendo os clientes que se encontaravam guardados no ficheiro de texto e vai adicionando-os ao grafo
 * \return: Devolve 1 caso consiga ler e 0 caso haja algum erro na leitura
 * 
 */
int LerClientes(Grafo g)
{
    FILE* fp;
    int ncliente;
    char nome[TAM], localizacao[TAM];
    fp = fopen("clientes2.txt", "r");
    if (fp != NULL)
    {
        while (!feof(fp))
        {
            fscanf(fp, "%[^;];%[^;];%d;\n", nome,localizacao,&ncliente);
            inserirCliente(g, nome,localizacao,ncliente);
        }
        fclose(fp);
        return (1);
    }
    return(0);
}

/**
 * 
 * \Enter: Entra o grafo, a distancia maxima a que um meio pode estar do cliente e a localização do cliente
 * \brief: A função irá ver primeiramente se a localização indicada existe no garfo, para isso compara os vertices existentes no grafo com a localização
e de seguida vai percorer o grafo ate chegar ao vertice com a determinada localização, depois vai comparar a distancia desse vertice aos adjacentes
com a distancia indicada e se estiverem entre 0 e o maximo da distancia, seram listados os meios desses vertices
 * 
 */
void ListarporDistancia(Grafo g, float distancia, char localizacao[],char tipotranporte[])
{
    Meios aux3;
    Adjacente aux2;
    Grafo vertice;
    int encontrado = 0; // variável de controle para verificar se pelo menos um meio foi encontrado
    if (existeVertice(g, localizacao))
    {
        while (strcmp(g->vertice, localizacao) != 0)
        {
            g = g->seguinte;
        }
        vertice = g->vertice;
        aux3 = vertice->meios;
        aux2 = g->adjacentes;
        while (aux2 != NULL)
        {
            if (aux2->peso <= distancia && strcmp(aux3->tipotransporte,tipotranporte)==0)
            {
                printf("Nome do meio:%s \n Nivel de bateria:%.2f \n Localizacao:%s \n", aux3->tipotransporte, aux3->bateria, aux3->geocodigo);
                encontrado = encontrado+1; // atualiza a variável de controle
                aux2 = aux2->seguinte;
            }
            if (aux2 != NULL)
            {
                vertice= aux2->vertice;
                aux3 = vertice->meios;
             }

           
        }    
        if (encontrado == 0)
        {
            printf("Nao existem meios num raio de %.2f\n", distancia);
        }
       
    }
    else
    {
        printf("Nao existe o vertice indicado \n");
    }
}


#pragma endregion 
