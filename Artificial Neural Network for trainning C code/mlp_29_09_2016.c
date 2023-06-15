#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ENTRADAS        2
#define SAIDAS          1
#define NR_AMOSTRAS     4
#define NR_NEURON_O     2
#define EPOCAS          10000
#define TX_APRENDIZADO  1

#define ZERO_TEST       0


/*
Dados para o treinamento da rede
*/
int cj_treinamento[NR_AMOSTRAS][ENTRADAS+SAIDAS] = {{0, 0, 0},
                                                    {0, 1, 1},
                                                    {1, 0, 1},
                                                    {1, 1, 0}};

                                                    // Angulo 0 10 amostras
/*int cj_treinamento[NR_AMOSTRAS][ENTRADAS+SAIDAS] = {{0,0},
                                                    {2,0},
                                                    {4,0},
                                                    {6,0},
                                                    {8,0},
                                                    {10,0},
                                                    {12,0},
                                                    {14,0},
                                                    {16,0},
                                                    {19,0},
                                                    // Angulo 18 4 amostras
                                                    {20,18},
                                                    {23,18},
                                                    {26,18},
                                                    {29,18},
                                                    // Angulo 36 4 amostras
                                                    {30,36},
                                                    {33,36},
                                                    {36,36},
                                                    {39,36},
                                                    // Angulo 54 4 amostras
                                                    {40,54},
                                                    {43,54},
                                                    {46,54},
                                                    {49,54},
                                                    // Angulo 72 5 amostras
                                                    {50,72},
                                                    {56,72},
                                                    {59,72},
                                                    {64,72},
                                                    {69,72},
                                                    // Angulo 90 5 amostras
                                                    {70,90},
                                                    {72,90},
                                                    {73,90},
                                                    {74,90},
                                                    {77,90},
                                                    // Angulo 108 10 amostras
                                                    {78,108},
                                                    {79,108},
                                                    {80,108},
                                                    {85,108},
                                                    {86,108},
                                                    {87,108},
                                                    {90,108},
                                                    {92,108},
                                                    {95,108},
                                                    {99,108},
                                                    // Angulo 126 5 amostras
                                                    {100,126},
                                                    {108,126},
                                                    {115,126},
                                                    {123,126},
                                                    {129,126},
                                                    // Angulo 144 5 amostras
                                                    {130,144},
                                                    {137,144},
                                                    {145,144},
                                                    {150,144},
                                                    {154,144},
                                                    // Angulo 162 4 amostras
                                                    {155,162},
                                                    {159,162},
                                                    {164,162},
                                                    {169,162},
                                                    // Angulo 180 4 amostras
                                                    {170,180},
                                                    {189,180},
                                                    {235,180},
                                                    {250,180}}; //total 60 amostras
/*
Variáveis globais
*/
double w_e_o[ENTRADAS+1][NR_NEURON_O];
double w_o_s[NR_NEURON_O+1][SAIDAS];


void foo() {
    w_e_o[0][0] = 3.1952;       //bias 1
    w_e_o[0][1] = -9.6999;      //bias 2
    w_e_o[1][0] = -7.5380;      //w1n1
    w_e_o[1][1] = 6.3061;       //w1n2
    w_e_o[2][0] = -7.5453;      //w2n1
    w_e_o[2][1] = 6.3074;       //w2n2

    w_o_s[0][0] = 5.2960;       //bias 3
    w_o_s[1][0] = -14.6309;     //w1n3
    w_o_s[2][0] = -14.7504;     //w2n3
}

double saida_o[NR_NEURON_O];
double saida_s[SAIDAS];
double delta_saida[SAIDAS];
double gradiente_oculta[NR_NEURON_O];
double delta_oculta[NR_NEURON_O];
double media_erro = 0.0;


/*
Cabeçalho das funções auxiliares
*/
void inicializa_sinapses();
int gera_nr_aleatorios();
void mostrar_sinapses();
double f_sigmoid(double net);
void calcular_saidas(double entradas[ENTRADAS]);
void treinar_RNA();
double calcular_erro(double desejado, double saida);
void menu();
void calcular_delta_saida(double desejado);
void calcular_delta_oculta();
void calcular_gradiente_oculta();
void ajustar_pesos_sinapticos(double entradas[ENTRADAS]);

double sigmoide_normalizada(double net);
void calcular_saidas_normalizadas(double entradas[ENTRADAS]);

/*
Função principal
*/
int main()
{
  srand(time(NULL));

  while (1) {

    menu();

  }

  return 0;
}

void inicializa_sinapses()
{
  int i, j;

  // Inicializa pesos sinápticos da entrada para a camada oculta
  for (i = 0; i < ENTRADAS+1; i++) {
    for (j =0; j < NR_NEURON_O; j++) {
     #if ZERO_TEST
      w_e_o[i][j] = 0.0;
     #else
      w_e_o[i][j] = gera_nr_aleatorios();
     #endif
    }
  }

  // Inicializa pesos sinápticos da camada oculta para a saída
  for (i = 0; i < NR_NEURON_O+1; i++) {
    for (j =0; j < SAIDAS; j++) {
     #if ZERO_TEST
      w_o_s[i][j] = 0.0;
     #else
      w_o_s[i][j] = gera_nr_aleatorios();
     #endif
    }
  }

}

int gera_nr_aleatorios()
{
  int numeros[2] = {-1, 1};
  // Retorna -1 ou 1
  return (numeros[rand() % 2]);
}

void mostrar_sinapses()
{
  int i, j;

  // Inicializa pesos sinápticos da entrada para a camada oculta
  for (i = 0; i < ENTRADAS+1; i++) {
    for (j =0; j < NR_NEURON_O; j++) {
      printf("w_e_o[%d][%d]: %f ", i, j, w_e_o[i][j]);
    }
    printf("\n");
  }

  // Inicializa pesos sinápticos da camada oculta para a saída
  for (i = 0; i < NR_NEURON_O+1; i++) {
    for (j =0; j < SAIDAS; j++) {
      printf("w_o_s[%d][%d]: %f ", i, j, w_o_s[i][j]);
    }
    printf("\n");
  }
}

double f_sigmoid(double net)
{
  return 1 / (1 + exp(-net));
}

void calcular_saidas(double entradas[ENTRADAS])
{
  int i, j;

  // Calcular os nets da entrada para a camada oculta
  for (i = 0; i < NR_NEURON_O; i++) {
    saida_o[i] = 0.0;
    saida_o[i] += w_e_o[0][i] * 1;  // Calcula saida para bias

    for (j = 1; j < ENTRADAS+1; j++) {
     saida_o[i] += w_e_o[j][i] * entradas[j-1];
    }

    // Calcular a saida de saida_o[i]
    saida_o[i] = f_sigmoid(saida_o[i]);
  }

  // Calcular os nets da camada oculta para a saída
  for (i = 0; i < SAIDAS; i++) {
    saida_s[i] = 0.0;
    saida_s[i] += w_o_s[0][i] * 1;  // Calcula saida para bias

    for (j = 1; j < NR_NEURON_O+1; j++) {
      saida_s[i] += w_o_s[j][i] * saida_o[j-1];
    }

    saida_s[i] = f_sigmoid(saida_s[i]);
  }

}
double sigmoide_normalizada(double net)
{
    double saida;
                if ((net < -4.1))

					saida = 0.01;

				else if((net >= -4.1) && (net < -3.6))

					saida = 0.02;

				else if((net >= -3.6) && (net < -3.3))

					saida = 0.03;

				else if((net >= -3.3) && (net < -3.0))

					saida = 0.04;

				else if((net >= -3.0) && (net < -2.8))

					saida = 0.05;

				else if((net >= -2.8) && (net < -2.6))

					saida = 0.06;

				else if((net >= -2.6) && (net < -2.5))

					saida = 0.07;

				else if((net >= -2.5) && (net < -2.3))

					saida = 0.08;

				else if((net >= -2.3) && (net < -2.2))

					saida = 0.09;

				else if((net >= -2.2) && (net < -2.1))

					saida = 0.10;

				else if((net >= -2.1) && (net < -2.0))

					saida = 0.11;

				else if((net >= -2.0) && (net < -1.9))

					saida = 0.12;

				else if((net >= -1.9) && (net < -1.8))

					saida = 0.13;

				else if((net >= -1.8) && (net < -1.7))

					saida = 0.14;

				else if((net >= -1.7) && (net < -1.6))

					saida = 0.15;

				else if((net >= -1.6) && (net < -1.5))

					saida = 0.17;

				else if((net >= -1.5) && (net < -1.4))

					saida = 0.18;

				else if((net >= -1.4) && (net < -1.3))

					saida = 0.20;

				else if((net >= -1.3) && (net < -1.2))

					saida = 0.21;

				else if((net >= -1.2) && (net < -1.1))

					saida = 0.23;

				else if((net >= -1.1) && (net < -1.0))

					saida = 0.25;

				else if((net >= -1.0) && (net < -0.9))

					saida = 0.27;

				else if((net >= -0.9) && (net < -0.8))

					saida = 0.29;

				else if((net >= -0.8) && (net < -0.7))

					saida = 0.31;

				else if((net >= -0.7) && (net < -0.6))

					saida = 0.33;

				else if((net >= -0.6) && (net < -0.5))

					saida = 0.35;

				else if((net >= -0.5) && (net < -0.4))

					saida = 0.38;

				else if((net >= -0.4) && (net < -0.3))

					saida = 0.40;

				else if((net >= -0.3) && (net < -0.2))

					saida = 0.43;

				else if((net >= -0.2) && (net < -0.1))

					saida = 0.45;

				else if((net >= -0.1) && (net < 0.0))

					saida = 0.48;

				else if((net >= 0.0) && (net < 0.1))

					saida = 0.5;

				else if((net >= 0.1) && (net < 0.2))

					saida = 0.52;

				else if((net >= 0.2) && (net < 0.3))

					saida = 0.55;

				else if((net >= 0.3) && (net < 0.4))

					saida = 0.57;

				else if((net >= 0.4) && (net < 0.5))

					saida = 0.60;

				else if((net >= 0.5) && (net < 0.6))

					saida = 0.62;

				else if((net >= 0.6) && (net < 0.7))

					saida = 0.65;

				else if((net >= 0.7) && (net < 0.9))

					saida = 0.70;

				else if((net >= 0.9) && (net < 1.0))

					saida = 0.71;

				else if((net >= 1.0) && (net < 1.1))

					saida = 0.73;

				else if((net >= 1.1) && (net < 1.2))

					saida = 0.75;

				else if((net >= 1.2) && (net < 1.3))

					saida = 0.77;

				else if((net >= 1.3) && (net < 1.4))

					saida = 0.78;

				else if((net >= 1.4) && (net < 1.5))

					saida = 0.80;

				else if((net >= 1.5) && (net < 1.6))


					saida = 0.82;

				else if((net >= 1.6) && (net < 1.7))

					saida = 0.83;

				else if((net >= 1.7) && (net < 1.8))

					saida = 0.85;

				else if((net >= 1.8) && (net < 1.9))

					saida = 0.86;

				else if((net >= 1.9) && (net < 2.0))

					saida = 0.87;

				else if((net >= 2.0) && (net < 2.1))

					saida = 0.88;

				else if((net >= 2.1) && (net < 2.2))

					saida = 0.89;

				else if((net >= 2.2) && (net < 2.3))

					saida = 0.90;

				else if((net >= 2.3) && (net < 2.4))

					saida = 0.91;

				else if((net >= 2.4) && (net < 2.6))

					saida = 0.92;

				else if((net >= 2.6) && (net < 2.7))

					saida = 0.93;

				else if((net >= 2.7) && (net < 2.9))

					saida = 0.94;

				else if((net >= 2.9) && (net < 3.1))

					saida = 0.95;

				else if((net >= 3.1) && (net < 3.4))

					saida = 0.96;

				else if((net >= 3.4) && (net < 3.7))

					saida = 0.97;

				else if((net >= 3.7) && (net < 4.3))

					saida = 0.98;

				else if((net >= 4.3))
					saida = 0.99;

            return saida;

}

void calcular_saidas_normalizadas(double entradas[ENTRADAS])
{
  int i, j;

  // Calcular os nets da entrada para a camada oculta
  for (i = 0; i < NR_NEURON_O; i++) {
    saida_o[i] = 0.0;
    saida_o[i] += w_e_o[0][i] * 1;  // Calcula saida para bias

    for (j = 1; j < ENTRADAS+1; j++) {
     saida_o[i] += w_e_o[j][i] * entradas[j-1];
    }

    // Calcular a saida de saida_o[i]
    saida_o[i] = sigmoide_normalizada(saida_o[i]);
  }

  // Calcular os nets da camada oculta para a saída
  for (i = 0; i < SAIDAS; i++) {
    saida_s[i] = 0.0;
    saida_s[i] += w_o_s[0][i] * 1;  // Calcula saida para bias

    for (j = 1; j < NR_NEURON_O+1; j++) {
      saida_s[i] += w_o_s[j][i] * saida_o[j-1];
    }

    saida_s[i] = sigmoide_normalizada(saida_s[i]);
  }

}

void treinar_RNA()                  //treinamento da rede
{
  int i, j;
  double entradas[ENTRADAS];        //variáveis de entrada

  printf("Treinando Rede...\n");
  for (i = 1; i <= EPOCAS; i++) {       //Treinamento que deve acontecer de 1 a n épocas

    for (j = 0; j < NR_AMOSTRAS; j++) {     //Até completar o número de amostras
      entradas[0] = cj_treinamento[j][0];   //Escolhe a entrada 0 da amostra j
      entradas[1] = cj_treinamento[j][1];   //Escolhe a entrada 1 da amostra j

      // Feedforward
      calcular_saidas(entradas);            //calcula saidas com as 2 entradas (fase feedfoward)

      // Backward (backpropagation)
      calcular_delta_saida(cj_treinamento[j][2]);   //
      calcular_gradiente_oculta();
      calcular_delta_oculta();
      ajustar_pesos_sinapticos(entradas);
      //system("cls");
 //       printf("Enviado: %d \n",cj_treinamento[j][0]);
   //     printf("Recebido: %lf \n",saida_s[0]);
     //   printf("Desejado: %d \n",cj_treinamento[j][1]);
     // printf("%d de 4 amostras concluidas! \n", j);
    }

      printf("%d de %d epocas concluidas! \n", i, EPOCAS);
  }

  // Mostra media dos erros
  printf("RNA TREINADA - Media dos erros: %lf\n", media_erro);
}

double calcular_erro(double desejado, double saida)
{
  return desejado - saida;
}

void menu()
{
  int opcao;
  double entradas[ENTRADAS];

  printf("Rede Neural Perceptron de Multiplas Camadas\n");
  printf("Problema do OU EXCLUSIVO - XOR\n");
  printf("*******************************************\n\n");
  printf("1.Treinar a rede\n");
  printf("2.Usar a rede\n");
  printf("3.Ver pesos sinpaticos\n");
  printf("4.Sair\n");
  printf("Opcao? ");
  scanf("%d", &opcao);

  switch (opcao) {

    case 1: inicializa_sinapses();
            treinar_RNA();
            //foo();
            break;

    case 2: printf("Entrada 1: ");
            scanf("%lf", &entradas[0]);
            printf("Entrada 2: ");
            scanf("%lf", &entradas[1]);
            //calcular_saidas_normalizadas(entradas);
            calcular_saidas(entradas);
            printf("\nResposta da RNA: %lf\n\n\n", saida_s[0]);
            break;

    case 3: mostrar_sinapses();
            break;

    case 4: exit(0);

  }
}

void calcular_delta_saida(double desejado)
{
  int i;
  for (i = 0; i < SAIDAS; i++)
   delta_saida[i] = calcular_erro(desejado, saida_s[i]) * (1 - saida_s[i] * saida_s[i]); //utiliza momentum

}

void calcular_gradiente_oculta()
{
  int i, j;

  for (i = 0; i < SAIDAS; i++) {
    for (j = 1; j < NR_NEURON_O+1; j++) {
      gradiente_oculta[j-1] = delta_saida[i] * w_o_s[j][i];
    }
  }
}

void calcular_delta_oculta()
{
  int i;
  for (i = 0; i < NR_NEURON_O; i++)
    delta_oculta[i] = gradiente_oculta[i] * saida_o[i] * (1 - saida_o[i]);

}

void ajustar_pesos_sinapticos(double entradas[ENTRADAS])
{
  int i, j;

  // Ajusta os pesos sinápticos da camada intermediária para a camada de saída
  for (i = 0; i < SAIDAS; i++) {
    w_o_s[0][i] = w_o_s[0][i] + TX_APRENDIZADO * delta_saida[i] * 1;        //Atualiza os bias

    for (j = 1; j < NR_NEURON_O+1; j++) {
      w_o_s[j][i] = w_o_s[j][i] + TX_APRENDIZADO * delta_saida[i] * saida_o[j-1];       //Atualiza os pesos
    }

  }

  // Ajusta os pesos sinápticos da camada de saida para a camada intermediária
  for (i = 0; i < NR_NEURON_O; i++) {
    w_e_o[0][i] = w_e_o[0][i] + TX_APRENDIZADO * delta_oculta[i] * 1;

    for (j = 1; j < ENTRADAS+1; j++) {
     w_e_o[j][i] = w_e_o[j][i] + TX_APRENDIZADO * delta_oculta[i] * entradas[j-1];
    }
  }

}

