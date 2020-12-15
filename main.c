#include <stdio.h>
#include <math.h>
#include <string.h>
#include "functions.c"

int main() {
	int convidados[3];
    float orcamento;
    printf("\n***** INFORMACOES INICIAIS *****\n");
 	printf("\n informe quantos homens adultos estao convidados\n");
    scanf("%d", &convidados[0]);
    printf("\n informe quantas mulheres adultas estao convidadas\n");
    scanf("%d", &convidados[1]);
    printf("\n informe quantas criancas estao convidadas\n");
    scanf("%d", &convidados[2]);
    printf("\nInforme o orcamento do evento\n");
    scanf("%f", &orcamento);
    compilaGastos(orcamento, &convidados);
    
    printf("\n\n***** GASTOS EXTRAS *****\n");
	gastosExtras();
	
	printf("\n\n***** ORGANIZACAO MESAS *****\n");
	divideMesas();
}
