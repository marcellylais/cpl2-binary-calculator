#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*LINK PARA O VIDEO https://drive.google.com/file/d/14DkF0O3v4gjvBQufepBzrZKjhMJ3b2rX/view?usp=sharing*/

char* binprahex(int parte) { 
    int i, salva;
    char* hex = malloc(3);
    salva = parte;
    parte = parte / 10000;
    for(i = 0; i < 2; i++)
    {
        switch(parte)
    {
        case 0:
            hex[i] = '0';
            break;
        case 1:
            hex[i] = '1';
            break;
        case 10:
            hex[i] = '2';
            break;
        case 11:
            hex[i] = '3';
            break;
        case 100:
            hex[i] = '4';
            break;
        case 101:
            hex[i] = '5';
            break;
        case 110:
            hex[i] = '6';
            break;
        case 111:
            hex[i] = '7';
            break;
        case 1000:
            hex[i] = '8';
            break;
        case 1001:
            hex[i] = '9';
            break;
        case 1010:
            hex[i] = 'A';
            break;
        case 1011:
            hex[i] = 'B';
            break;
        case 1100:
            hex[i] = 'C';
            break;
        case 1101:
            hex[i] = 'D';
            break;
        case 1110:
            hex[i] = 'E';
            break;
        case 1111:
            hex[i] = 'F';
            break;
    }
        parte = salva % 10000;
    }

    hex[2] = '\0';
    return hex;
}

int binpradec(int bin){
    
    int decimal = 0, num, elevado = 1;
    
    while(bin > 0)
    {
        num = bin % 10;
        bin = bin / 10;

        decimal = decimal + (num * elevado);
        elevado = elevado * 2;
    }

    return decimal;
}

/*função para aplicar complemento a 2*/
int cpl2(int bin)
{
    int inv = 0, complemento = 0, local = 1, p = 0, qntd = 0, i;

    for (i = 0; i < 8; i++)
    {
        qntd = qntd + 1;
        if(bin % 10 == 0 && inv == 0)
        {
            complemento = complemento + (local * (bin % 10));
        }
        else
        {
            inv = 1;
            if(p == 0)
            {
                complemento = complemento + (local * (bin % 10));
                p = 1;
            }
            else
            {
                switch (bin % 10)
                {
                case (1):
                    complemento = complemento + (local * (0));
                    break;
                case (0):
                    complemento = complemento + (local * (1));
                    break;
                }
            }
            
        }
        local = local * 10;
        bin = bin / 10;
    }

    return complemento;
}

int soma(int bin, int bin2)
{
    int carry = 0, resultado = 0, local = 1, bit1, bit2;
    while(bin != 0 || bin2 != 0 || carry == 1)
    {
        
        bit1 = bin % 10;
        bit2 = bin2 % 10;
        switch (bit1 + bit2 + carry)
        {
        case (0):
            resultado = resultado + 0;
            carry = 0;
            break;
        case (1):
            resultado = resultado + (local * 1);
            carry = 0;
            break;
        case (2):
            resultado = resultado + 0;
            carry = 1;
            break;
        case (3):
            resultado = resultado + (local * 1);
            carry = 1;
            break;
        }
        local = local * 10;
        bin = bin / 10;
        bin2 = bin2 / 10;
    }

    return resultado;
}

/*analisa o valor de bin / 10000000 se for 0 é positivo se for 1 é negativo*/
int main()
{
    char *op1, *op2;
    int bin, bin2, bin3, binmeio, binresult, dec1, dec2, dec3, decresult, binaux;

    op1 = (char*) malloc(3 * sizeof(char));
    op2 = (char*) malloc(3 * sizeof(char));

    if(op1 == NULL || op2 == NULL)
    {
        printf("ERRO: não foi possível alocar memória para operadores");
        exit(1);
    }

    scanf("%d", &bin);
    while(bin != -1)
    {
        /*Entrada*/
        char *hbin1, *hbin2, *hbin3, *hexaresult;
        hbin1 = (char*) malloc(4 * sizeof(char));
        hbin2 = (char*) malloc(4 * sizeof(char));
        hbin3 = (char*) malloc(4 * sizeof(char));
        hexaresult = (char*) malloc(4 * sizeof(char));;

        scanf("%s", op1);
        scanf("%d", &bin2);
        scanf("%s", op2);
        scanf("%d", &bin3);

        /*redução dos binários para 8 bits*/
        bin = bin % 100000000;
        bin2 = bin2 % 100000000;
        bin3 = bin3 % 100000000;

        hbin1 = binprahex(bin); 
        hbin2 = binprahex(bin2);
        hbin3 = binprahex(bin3);

        if(strcmp(op1, "+") == 0)
        {
            /*se a primeira operação for soma o sistema apenas soma os binários bit a bit usando a função soma*/
            binmeio = soma(bin, bin2);
        }
        else if (strcmp(op1, "-") == 0)
        {
            /*se a primeira operação for subtração o sistema aplica complemento 2 aos binários bit a bit na função cpl2 e dps os soma usando a função soma*/
            binaux = bin2;
            binaux = cpl2(binaux);
            binmeio = soma(bin, binaux);
        }
        if (strcmp(op2, "+") == 0)
        {
            /*se a segunda operação for soma o sistema apenas soma os binários bit a bit usando a função soma*/
            binresult = soma(binmeio, bin3);
        }
        else if (strcmp(op2, "-") == 0)
        {
            /*se a segunda operação for subtração o sistema aplica complemento 2 aos binários bit a bit na função cpl2 e dps os soma usando a função soma*/
            binaux = bin3;
            binaux = cpl2(bin3);
            binresult= soma(binmeio, binaux);
        }
        
        binresult = binresult % 100000000; /*desprezando carry*/
        hexaresult = binprahex(binresult);

        /*verificação se os binários são negativos e conversão para decimais*/
        if (bin / 10000000 == 1)
        {
            binaux = cpl2(bin);
            dec1 = (binpradec(binaux)) * (- 1);
        }
        else
        {
            dec1 = binpradec(bin);
        }

        if (bin2 / 10000000 == 1)
        {
            binaux = cpl2(bin2);
            dec2 = (binpradec(binaux)) * (- 1);
        }
        else
        {
            dec2 = binpradec(bin2);
        }

        if (bin3 / 10000000 == 1)
        {
            binaux = cpl2(bin3);
            dec3 = (binpradec(binaux)) * (- 1);
        }
        else
        {
            dec3 = binpradec(bin3);
        }

        if (binresult / 10000000 == 1)
        {
            binaux = cpl2(binresult);
            decresult = (binpradec(binaux)) * (- 1);
        }
        else
        {
            decresult = binpradec(binresult);
        }


        printf("%db (%di %sh)\n", bin, dec1, hbin1);
        printf("%s\n", op1);
        printf("%db (%di %sh)\n", bin2, dec2, hbin2);
        printf("%s\n", op2);
        printf("%db (%di %sh)\n", bin3, dec3, hbin3);
        printf("=");
        printf("%db (%di %sh)\n", binresult, decresult, hexaresult);

        free(hbin1);
        free(hbin2);
        free(hbin3);
        free(hexaresult);

        scanf("%d", &bin);

    }

    free(op1);
    free(op2);

    return 0;
}