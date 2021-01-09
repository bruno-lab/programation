#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

//essa funcao soma a quantidade de convidados
//ela recebe como parametro uma variavel com o valor de parada
//esse valor de parada vai indicar ate que casa do vetor ele vai somar
//exemplo pra gar?om somamos todas as casas,
// pq precisamos do total de convidados, ent?o passamos 3
//ja pra comida somamos as 2 primeiras, pq primeiro queremos a quantidade de adultos

int calculaConvidados(int *pConvidados, int parada){
	int totalConvidados = 0, i;
    for(i=0; i < parada; i++){
     totalConvidados = totalConvidados + pConvidados[i];
    }
    return totalConvidados;
}


//recebe como parametro a parcela e o total
//calcula quantos % a parcela é do total
//retorna o resultado
float calculaPercentual(float parcela, float total) {
float percentual = (parcela / total) * 100;
return percentual;
}


//essa funcao recebe como parametro os custos, para atualizar o valor
//chama a funcao que calcula o total de convidados, passa 3 de parametro
//divide o numero de convidados que retornou por 50
// e arredonda pra cima
//multiplica o resultado por 100 que é o custo de cada garçom
float calculaGarcon(float *custos, int *convidados){
	int parada = 3;
	int conv = calculaConvidados(convidados, parada);
    float garcon = conv / 50.0;
    int retorno = ceil(garcon);
    float custoGarcons = retorno * 100.00;
    *custos = *custos + custoGarcons;
    return custoGarcons;
}

//essa funcao recebe como parametro os custos, para atualizar o valor
//aqui chama a funcao de calcular convidados e passa 2 como parametro
//pq só queremos os adultos
//depois multiplica o numero de adultos por 25 que é o preço do buffet
// multiplica o numero de criancas por 12.5 que é o preço do buffet
//soma os 2 resultados e atualiza a variavel custos
float calculaComida(float *custos, int *convidados){
	int parada = 2;
	int convAdulto = calculaConvidados(convidados, parada);
	int convCrianca = convidados[2];
	float custoTotalComida = convAdulto * 25.00 + convCrianca * 12.50;
	*custos = *custos + custoTotalComida;
	return custoTotalComida;
}

//Esta função cria um arquivo com o orçamento, caso o usuário queira salvar
void salvaOrcamento(int *convidados, char retornoOrcamento[50], float gastos, float orcamento, float quantGarcon, float gastoComida){
	int parada = 3;
	int conv = calculaConvidados(convidados, parada);
	FILE *arquivo;
	char nomeArquivo[30];
	printf("\n informe o nome do arquivo sem espacos e caracteres especiais\n");
	scanf("%s", nomeArquivo);
	strcat(nomeArquivo, ".txt");
	arquivo = fopen(nomeArquivo, "wb");
	
	if (arquivo == NULL){
	printf("Problemas na criacao do arquivo\n");
		return;
	}
	
	char gastoGarcon[50], gastoTotal[50], gastoCom[50], dadosFesta[50], orcamentoPrevisto[50];
	sprintf(gastoTotal, "GASTO TOTAL: %.2f \n", gastos);
	sprintf(dadosFesta, "Evento para %d pessoas\n", conv);
	sprintf(orcamentoPrevisto, "Orçamento previsto %.2f \n", orcamento);
	sprintf(gastoGarcon, "vc vai gastar %.2f com garcons\n", quantGarcon);
	sprintf(gastoCom, "vc vai gastar %.2f com comida\n", gastoComida);
	
	char topo = fputs("### ORÇAMENTO ### \n\n", arquivo);
	char linha1 = fputs(dadosFesta, arquivo);
	char linha2 = fputs(orcamentoPrevisto, arquivo);
	char linha3 = fputs(gastoGarcon, arquivo);
	char linha4 = fputs(gastoCom, arquivo);
	char linha5 = fputs(gastoTotal, arquivo);
	char linha6 = fputs(retornoOrcamento, arquivo);
	
	fclose(arquivo);
}


//Nessa função eu chamo as funções que calculam comida e garçons
//as funções que calculam a comida e a quantidade de garçons atualiam a variavel gastos
//verifica se os gastos so maiores que o orçamento, se forem avisa que ultrapassou
// se os gastos forem iguais avisa que zerou
// se forem menores:
//subtrai valor de gastos do orçamento
//chama a função de percentual pra calcular quantos % do orcamento sobra
//mostra quanto gastou, quanto sobrou e quanto % sobrou
void compilaGastos(float orcamento, int *convidados) {
    float gastos;
    float quantGarcon = calculaGarcon(&gastos, convidados);
    float gastoComida = calculaComida(&gastos, convidados);
	char retornoOrcamento[50];
	
	printf("\n\n***** RELATORIO DO ORCAMENTO *****\n");
	
    if(orcamento > gastos) {
	strcpy(retornoOrcamento, "Os gastos estão dentro do orcamento previsto");
	float orcamentoRestante = orcamento - gastos;
	float percent = calculaPercentual(orcamentoRestante, orcamento);
	printf("\n vc vai gastar %.2f com garcons", quantGarcon);
	printf("\n vc vai gastar %.2f com comida", gastoComida);
	printf("\n vc vai gastar %.2f no total", gastos);
	printf("\n sobra %.2f", orcamentoRestante);
	printf("\n sobra %.2f por cento", percent);
	} else if(orcamento == gastos) {
 		printf("\n vc zerou seu orcamento nao pode mais gastar\n");
		strcpy(retornoOrcamento, "Os gastos são iguais ao orcamento previsto");
	} else if(orcamento < gastos) {
  		printf("\n ops os gastos ultrapassaram o orcamento \n");
		strcpy(retornoOrcamento, "Os gastos  ultrapassaram orcamento previsto");
	}

	int salvar;
	printf("\n\n ## SALVAR ORCAMENTO:\n  1 => Sim \n 0 =>  Nao\n Informe o numero referente a sua opcao\n" );
	scanf("%d", &salvar);
	if(salvar == 1){
		salvaOrcamento(convidados, retornoOrcamento, gastos, orcamento, quantGarcon, gastoComida);
	}
}

//esta função é uma alternativa para a função strcmp, ela recebe duas strings e retorna 1 se forem iguais
int comparaString(char primeiraString[30], char segundaString[30]){
    int cont = 0, i;
    int tamanho = strlen(primeiraString);
    for(i=0; i<tamanho; i++){
        if(primeiraString[i] == segundaString[i]) {
        cont = cont + 1;
        }
    }

    if(cont == tamanho) {
        return 1;
    } else {
        return 0;
    }
}

//essa funcao informa os gastos extras que serão necessários com o evento de acordo com o tipo de festa
//quero melhorar ela depois pra ter mais itens e mais detalhados
void gastosExtras() {
	char tipoFesta[30], tipoFestaCompara1[30] = "infantil", tipoFestaCompara2[30] = "adulto", tipoFestaCompara3[30] = "debutante" ;
	printf("\ninforme se a festa eh  infantil, adulto, debutante\n");
	scanf("%s", tipoFesta);
	
	if(comparaString(tipoFesta,tipoFestaCompara1)) {
	    printf("\n\nvc precisa fazer orcamento para brinquedos e animador de festa\n\n");
	} else if(comparaString(tipoFesta,tipoFestaCompara2)) {
	    printf("\n\nsem gastos adicionais\n\n");
	} else if(comparaString(tipoFesta,tipoFestaCompara3)) {
	    printf("\n\nvc precisa fazer orcamento para balada e barman\n\n");
	} else {
	    printf("\n\nesse tipo de festa nao corresponde as opcoes disponiveis\n\n");
	}
}

//considera
//500ml refri por convidado
//500ml de agua por convidado
//400ml chopp por convidada mulher adulta
//600ml chopp por convidado homem adulto
void calculaBebidas(int *convidados){
	int parada = 3;
	int conv = calculaConvidados(convidados, parada);
	float quantRefri = conv * 0.5;
	float choppHomem = convidados[0] * 0.6;
	int choppMulher = convidados[1] *0.4;
	float quantChopp = choppHomem + choppMulher;
	printf("\n### Quantidade de bebida ###\n");
	printf("%.2f litros de chopp\n", quantChopp);
	printf("%.2f litros de agua e refri\n", quantRefri);
}


//esta é uma função recursiva que ordena strings em ordem alfabética
void ordenaAlfabetica(char **conv, int *quantConvFam, int parada){
 char aux[30];
 int j, auxiliar;
 if(parada>0) {
    for(j=0;j<parada-1;j++) {
        if(strcmp(conv[j], conv[j+1]) > 0) {
            strcpy(aux, conv[j]);
            strcpy(conv[j], conv[j+1]);
            strcpy(conv[j+1], aux);
			auxiliar = quantConvFam[j];
			quantConvFam[j] = quantConvFam[j+1];
			quantConvFam[j+1] = auxiliar;
        }

    }
  ordenaAlfabetica(conv,quantConvFam,parada-1);
  }
  else {
       return;
  }
}

// essa funcao recebe os nomes das familias convidadas e organiza em mesas de forma alfabetica
// para isso ela chama a funcao ordenaAlfabetica
// depois quero melhorar esta funcao para que ela divida as mesas com numero igual de convidados
// Os vetores utilizados nesta função são alocados dinamicamente
void divideMesas(int *convidados) {
	int i,parada;
	char **conv;
	printf("\ninforme quantas familias estao convidadas\n");
	scanf("%d", &parada);
	int *quantCov;
	conv = malloc(sizeof(char*)*parada);
	quantCov = malloc(sizeof(int*)*parada);
	int indice;
	for(indice=0;indice < parada;indice++){ 
	    conv[indice] = malloc(sizeof(char)*30);
	}

	printf("\n***Informe os sobrenomes e a quantidade de pessoas convidadas de cada familia***\n");
	for(i=0;i<parada;i++) {
		printf("\nInforme o sobrenome da %d familia\n", i+1);
		scanf("%s", conv[i]);
		printf("\nInforme quantas pessoas da familia %s estao convidadas\n", conv[i]);
		scanf("%d", &quantCov[i]);
	}
	
	int paradaTotal = 3;
	int convidadosTotal = calculaConvidados(convidados, paradaTotal);
	int paradaPorFamilia = parada;
	int convidadosTotalFamilias = calculaConvidados(quantCov, paradaPorFamilia);
	if(convidadosTotal != convidadosTotalFamilias) {
		printf("\n### ALERTA: A quantidade de convidados informada por familia eh diferente da quantidade informada por sexo e idade, por favor verifique ###\n");
	}

	ordenaAlfabetica(conv, quantCov, parada);
	
	int cont = 0;
	printf("\n\n## Divisao mesas ##\n");
	
	for(i=0;i<parada;i++) {
		if(quantCov[i] > 5) {
			printf("\n mesas %d  e %d familia %s\n", cont+1, cont+2, conv[i]);
			cont = cont + 2;
		} else {
			printf("\n mesa %d familia %s\n", cont+1, conv[i]);
			cont ++;
		}
	}
	free(conv);
	free(quantCov);
}
