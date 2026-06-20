
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

void gotoxy(int col, int lin)
{
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        (COORD){col - 1, lin - 1}
    );
}

void clreol()
{
    gotoxy(8, 23);
    printf("                                                            ");
}

int main()
{
    setlocale(LC_ALL, "portuguese");

    const float preco_chopps        = 15.0;
    const float preco_pizza         = 55.0;
    const float preco_cobertura     = 10.0;
    const float preco_refrigerante  = 8.0;
    const float preco_agua          = 6.0;
    const float porcentagem_gorjeta = 10.0;

    const float desconto_ate400   = 5.2f;
    const float desconto_ate700   = 8.0f;
    const float desconto_acima700 = 10.0f;

    float vet_acumulador_vendas[10] = {0};

    unsigned int vet_acumulador_pessoas[10] = {0};

    float mat_consumo[10][5] = {0};

    float valor_total_consumo,
          valor_gorjeta,
          valor_total_apagar,
          valor_a_pagar_pessoas,
          valor_chopps,
          valor_pizza,
          valor_cobertura,
          valor_refrigerante,
          valor_agua,
          porcentagem_desconto,
          valor_desconto,
          valor_conta_descontado,
          faturamento_dia = 0,
          media_faturamento = 0;

    unsigned int qntd_pessoas,
                 qntd_agua,
                 qntd_chopps,
                 qntd_pizzas,
                 qntd_coberturas,
                 qntd_refrigerantes,
                 num_mesa, mesas = 0, indC;

    do
    {
        system("cls");

        gotoxy(17, 2);
        printf("<<  Pizzaria Franzinnis  >>");

        gotoxy(16, 4);
        printf("<<  Consumo da Mesa:     [0 = Sair]    >>");

        gotoxy(37, 4);
        scanf("%u", &num_mesa);

        if (num_mesa == 0)
            break;

        while (num_mesa > 10)
        {
            gotoxy(8, 23);
            printf("Numero da Mesa deve estar entre 1 e 10, inclusive.");

            Sleep(2000);

            clreol();

            gotoxy(37, 4);
            printf("     ");

            gotoxy(37, 4);
            scanf("%2u", &num_mesa);
        }

        gotoxy(20, 6);
        printf("Chopps........:");

        gotoxy(20, 7);
        printf("Pizzas Mistas.:");

        gotoxy(20, 8);
        printf("Coberturas....:");

        gotoxy(20, 9);
        printf("Refrigerantes.:");

        gotoxy(20, 10);
        printf("Aguas.........:");

        gotoxy(20, 12);
        printf("Pessoas na Mesa:");

        gotoxy(36, 6);
        scanf("%u", &qntd_chopps);

        gotoxy(36, 7);
        scanf("%u", &qntd_pizzas);

        gotoxy(36, 8);
        scanf("%u", &qntd_coberturas);

        while (qntd_pizzas == 0 && qntd_coberturas > 0)
        {
            gotoxy(8, 23);
            printf("Informe a quantidade de Pizzas.");

            Sleep(2000);

            clreol();

            gotoxy(36, 7);
            printf("     ");

            gotoxy(36, 7);
            scanf("%u", &qntd_pizzas);
        }

        while (qntd_coberturas == 0 && qntd_pizzas > 0)
        {
            gotoxy(8, 23);
            printf("Informe a quantidade de Cobertura.");

            Sleep(2000);

            clreol();

            gotoxy(36, 8);
            printf("     ");

            gotoxy(36, 8);
            scanf("%u", &qntd_coberturas);
        }

        gotoxy(36, 9);
        scanf("%u", &qntd_refrigerantes);

        gotoxy(36, 10);
        scanf("%u", &qntd_agua);

        gotoxy(37, 12);
        scanf("%u", &qntd_pessoas);

        while (qntd_pessoas == 0)
        {
            gotoxy(8, 23);
            printf("Obrigatorio informar o numero de Pessoas na mesa");

            Sleep(2000);

            clreol();

            gotoxy(37, 12);
            printf("     ");

            gotoxy(37, 12);
            scanf("%u", &qntd_pessoas);
        }

        valor_chopps       = qntd_chopps * preco_chopps;
        valor_pizza        = qntd_pizzas * preco_pizza;
        valor_cobertura    = qntd_coberturas * preco_cobertura;
        valor_refrigerante = qntd_refrigerantes * preco_refrigerante;
        valor_agua         = qntd_agua * preco_agua;

        valor_total_consumo =
            valor_chopps +
            valor_pizza +
            valor_cobertura +
            valor_refrigerante +
            valor_agua;

        valor_gorjeta = valor_total_consumo * (porcentagem_gorjeta / 100);

        valor_total_apagar = valor_total_consumo + valor_gorjeta;

        if (valor_total_apagar <= 400)
            porcentagem_desconto = desconto_ate400;
        else if (valor_total_apagar <= 700)
            porcentagem_desconto = desconto_ate700;
        else
            porcentagem_desconto = desconto_acima700;

        valor_desconto = valor_total_apagar * (porcentagem_desconto / 100);

        valor_conta_descontado = valor_total_apagar - valor_desconto;

        valor_a_pagar_pessoas = valor_conta_descontado / qntd_pessoas;

        vet_acumulador_vendas[num_mesa - 1] += valor_conta_descontado;

        vet_acumulador_pessoas[num_mesa - 1] += qntd_pessoas;

        mat_consumo[num_mesa - 1][0] += valor_pizza;
        mat_consumo[num_mesa - 1][1] += valor_cobertura;
        mat_consumo[num_mesa - 1][2] += valor_chopps;
        mat_consumo[num_mesa - 1][3] += valor_refrigerante;
        mat_consumo[num_mesa - 1][4] += valor_agua;

        system("cls");

        gotoxy(25, 2);
        printf("<<  Pizzaria Franzinnis  >>");

        gotoxy(17, 4);
        printf("<<   Fechamento da Conta da Mesa:      >>");

        gotoxy(51, 4);
        printf("%u", num_mesa);

        gotoxy(19, 6);
        printf("Valor Total do Consumo....:");

        gotoxy(19, 7);
        printf("%% da Gorjeta do Garcom....:");

        gotoxy(19, 8);
        printf("Valor da Gorjeta..........:");

        gotoxy(19, 9);
        printf("Valor Total da Conta......:");

        gotoxy(19, 10);
        printf("%% do Desconto.............:");

        gotoxy(19, 11);
        printf("Valor do Desconto.........:");

        gotoxy(19, 13);
        printf("Valor Total a Pagar.......:");

        gotoxy(19, 15);
        printf("Quantidade Pessoas Mesa...:");

        gotoxy(19, 16);
        printf("Valor por Pessoa..........:");

        gotoxy(47, 6);
        printf("%.2f", valor_total_consumo);

        gotoxy(47, 7);
        printf("%.1f", porcentagem_gorjeta);

        gotoxy(47, 8);
        printf("%.2f", valor_gorjeta);

        gotoxy(47, 9);
        printf("%.2f", valor_total_apagar);

        gotoxy(47, 10);
        printf("%.1f", porcentagem_desconto);

        gotoxy(47, 11);
        printf("%.2f", valor_desconto);

        gotoxy(47, 13);
        printf("%.2f", valor_conta_descontado);

        gotoxy(47, 15);
        printf("%u", qntd_pessoas);

        gotoxy(47, 16);
        printf("%.2f", valor_a_pagar_pessoas);

        gotoxy(1, 20);
        printf("\n");

        system("pause");

    } while (1);

    system("cls");

    gotoxy(19, 2);
    printf("<<  Pizzaria Franzinnis  >>");

    gotoxy(15, 4);
    printf("<<  Fechamento do Faturamento  >>");

    
    gotoxy(5,  5); printf("Numero");
    gotoxy(6,  6); printf("Mesa");

    gotoxy(12, 5); printf("<<<           Valor Total Consumido               >>>");
    gotoxy(13, 6); printf("Pizzas");

    gotoxy(23, 6); printf("Coberturas");

    gotoxy(35, 6); printf("Chopps");

    gotoxy(47, 6); printf("Refri");

    gotoxy(58, 6); printf("Agua");

    gotoxy(68, 5); printf("Total");
    gotoxy(67, 6); printf("Pessoas");

    for (indC = 0; indC < 10; indC++)
    {
        if (vet_acumulador_vendas[indC] > 0)
        {
            gotoxy(6,  8 + indC); printf("%2u",     indC + 1);
            gotoxy(12
			, 8 + indC); printf("%8.2f",   mat_consumo[indC][0]);
            gotoxy(23, 8 + indC); printf("%8.2f",   mat_consumo[indC][1]);
            gotoxy(34, 8 + indC); printf("%8.2f",   mat_consumo[indC][2]);
            gotoxy(45, 8 + indC); printf("%8.2f",   mat_consumo[indC][3]);
            gotoxy(55, 8 + indC); printf("%8.2f",   mat_consumo[indC][4]);
            gotoxy(69, 8 + indC); printf("%3u",     vet_acumulador_pessoas[indC]);

            faturamento_dia += vet_acumulador_vendas[indC];
            mesas++;
        }
    }

    if (mesas != 0)
    {
        gotoxy(5, 19); printf("Total do Faturamento do dia.. R$");
        gotoxy(37, 19); printf("%9.2f", faturamento_dia);

        media_faturamento = faturamento_dia / mesas;

        gotoxy(5, 21); printf("Media do Faturamento por Mesa R$");
        gotoxy(37, 21); printf("%9.2f", media_faturamento);
    }
    else
    {
        gotoxy(2, 23); printf("Atencao! NAO houve Faturamento neste dia!");
    }

    printf("\n\n");
    system("pause");

    return 0;
}