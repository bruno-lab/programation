#include <stdio.h>
#include <math.h>
#include <string.h>
#include "functions.h"

//essa fun��o soma a quantidade de convidados
//ela recebe como parametro uma variavel com o valor de parada
//esse valor de parada vai indicar at� que casa do vetor ele vai somar
//exemplo pra gar�om somamos todas as casas,
// pq precisamos do total de convidados, ent�o passamos 3
//j� pra comida somamos as 2 primeiras, pq primeiro queremos a quantidade de adultos
int calculaConvidados(int *pConvidados, int parada){ 
	int totalConvidados = 0, i;
    for(i=0; i < parada; i++) {
     totalConvidados = totalConvidados + pConvidados[i];
    }
    return totalConvidados;
}


//recebe como parametro a parcela e o total
//calcula quantos % a parcela � do total
//retorna o resultado
float calculaPercentual(float parcela, float total) {
	float percentual = (parcela / total) * 100;
	return percentual;
}


//essa fun��o recebe como parametro os custos, para atualizar o valor
//chama a fun��o que calcula o total de convidados, passa 3 de parametro
//divide o numero de convidados que retornou por 50
// e arredonda pra cima
//multiplica o resultado por 100 que � o custo de cada gar�om
float calculaGarcon(float *custos, int *convidados){
	int parada = 3;
	int conv = calculaConvidados(convidados, parada);
    float garcon = conv / 50.0;
    int retorno = ceil(garcon);
    float custoGarcons = retorno * 100.00;
    *custos = *custos + custoGarcons;
    return custoGarcons;
}

//essa fun��o recebe como parametro os custos, para atualizar o valor
//aqui chama a fun��o de calcular convidados e passa 2 como parametro
//pq s� queremos os adultos
//depois multiplica o numero de adultos por 25 que � o pre�o do buffet
// multiplica o numero de criancas por 12.5 que � o pre�o do buffet
//soma os 2 resultados e atualiza a variavel custos
float calculaComida(float *custos, int *convidados) {
	int parada = 2;
	int convAdulto = calculaConvidados(convidados, parada);
	int convCrianca = convidados[2];
	float custoTotalComida = convAdulto * 25.00 + convCrianca * 12.50;
	*custos = *custos + custoTotalComida;
	return custoTotalComida;
}


//Nessa fun��o eu chamo as fun��es que calculam comida e gar�ons 
//as fun��es que calculam a comida e a quantidade de gar�ons atualiam a variavel gastos
//verifica se os gastos s�o maiores que o or�amento, se forem avisa que ultrapassou
// se os gastos forem iguais avisa que zerou
// se forem menores:
//subtrai valor de gastos do or�amento
//chama a fun��o de percentual pra calcular quantos % do orcamento sobra
//mostra quanto gastou, quanto sobrou e quanto % sobrou
void compilaGastos(float orcamento, int *convidados) {
    float gastos;
//    int convidados = convidados;
    float quantGarcon = calculaGarcon(&gastos, convidados);
    float gastoComida = calculaComida(&gastos, convidados);
      
    if(orcamento > gastos) {
	    float orcamentoRestante = orcamento - gastos;
	    float percent = calculaPercentual(orcamentoRestante, orcamento);
	    printf("\n vc vai gastar %.2f com garcons", quantGarcon);
	    printf("\n vc vai gastar %.2f com comida", gastoComida);
	    printf("\n vc vai gastar %.2f no total", gastos);
	    printf("\n sobra %.2f", orcamentoRestante);
	    printf("\n sobra %.2f por cento", percent);
	} else if(orcamento == gastos) {
	  	printf("\n vc zerou seu orcamento nao pode mais gastar\n");
	} else if(orcamento < gastos) {
	  	printf("\n ops os gastos ultrapassaram o orcamento \n");
	}
}
 
//esta fun��o � uma alternativa para a fun��o strcmp, ela recebe duas strings e retorna 1 se forem iguais  
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

//essa funcao informa os gastos extras que ser�o necess�rios com o evento de acordo com o tipo de festa
//quero melhorar ela depois pra ter mais itens e mais detalhados
void gastosExtras() {
	char tipoFesta[30], tipoFestaCompara1[30] = "infantil", tipoFestaCompara2[30] = "adulto", tipoFestaCompara3[30] = "debutante" ;
	printf("\ninfrome se a festa eh  infantil, adulto, debutante\n");
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

//esta � uma fun��o recursiva que ordena strings em ordem alfab�tica
void ordenaAlfabetica(char (*conv)[30],int parada){
 char aux[30];
 int j;
 if(parada>0) {
    for(j=0;j<parada-1;j++) {
        if(strcmp(conv[j], conv[j+1]) > 0) {
                strcpy(aux, conv[j]);
                strcpy(conv[j], conv[j+1]);
                strcpy(conv[j+1], aux);
            }
    }
  ordenaAlfabetica(conv,parada-1);
  }
  else {
       return;
  }
}

//essa funcao recebe os nomes das familias convidadas e organiza em mesas de forma alfab�tica
//para isso ela chama a fun��o ordenaAlfabetica
//depois quero melhorar esta fun��o para que ela divida as mesas com numero igual de convidados
void divideMesas() {
	int i,parada;
	printf("\ninforme quantas familias estao convidadas\n");
	scanf("%d",&parada);
	char conv[parada][30];
	printf("\nInforme os sobrenomes\n");
	for(i=0;i<parada;i++) {
 		scanf("%s", &conv[i]);
	}
	ordenaAlfabetica(conv,parada);
	for(i=0;i<parada;i++) {
 		printf("\n mesa %d familia %s\n", i+1, &conv[i]);
	}
}
