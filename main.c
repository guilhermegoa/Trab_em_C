#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <math.h>


/*-----------------------ESTRUTURA PACIENTES----------------------*/
// struct do paciente
struct Tpacientes
{
    int codigoP, telefoneP;
    int dataN[3];//Dia, Mes, Ano
    char nomeP[30], ruaP[30], bairroP[30], cidadeP[30], estadoP[30] ;

};
typedef struct Tpacientes pacientes;


/*-----------------------ESTRUTURA MEDICO------------------------*/
// struct do m�dico
struct Tmedico
{
    int codigoM, telefoneM;
    char nomeM[30], especialidade[50];
};
typedef struct Tmedico medico;


/*--------------------------ESTRUTURA CONSULTA--------------------*/
// struct da consulta
struct Tconsulta
{
    int codigoC, codigoM, codigoP, status;
    int dataC[3]; //Dia, Mes, Ano
    int horaC[2];//Hora, Minutos
    char nomeP[30], nomeM[30];

};
typedef struct Tconsulta consulta;




/*------------------------DECLARANDO FUNCOES--------------------------*/
void limpaTela();
void pausa();
void limpaBuffer();
void menu();
void criaArquivos();
void cadastrarPaciente(FILE*Fpaciente);
void cadastrarMedico(FILE*Fmedico);
int localizaPaciente(char nomeP[30]);
int localizaMedico(char nomeM[30]);
void cadastraConsulta(FILE*Fconsulta);
void relatorioDia(FILE*Fconsulta);
void relatorioPaciente(FILE*Fconsulta);
void relatorioMedico(FILE*Fconsulta);
void listadeMedicos(FILE*Fmedico);
void cancelaConsulta(FILE*Fconsulta);


/*--------------------------MAIN----------------------------*/
int main()
{
    setlocale(LC_ALL, "portuguese");
    int op;
    FILE *Fexistencia, *Fpaciente, *Fmedico, *Fconsulta;

    //condi��o para criar arquivos
    Fexistencia = fopen("C_existencia.dat","r+b");
    if(Fexistencia == NULL)
    {
        criaArquivos();
    }
    fclose(Fexistencia);

    //entrando no menu em loop
    do
    {
        limpaTela();
        menu();
        fflush(stdin);
        scanf("%i", &op);
        switch(op)
        {
        case 1:
            printf("\t\tCADASTRAR PACIENTE\n");
            cadastrarPaciente(Fpaciente);
            limpaTela();
            break;
        case 2:
            printf("\t\tCADASTRAR MEDICO\n");
            cadastrarMedico(Fmedico);
            limpaTela();
            break;
        case 3:
            printf("\t\tMARCAR CONSULTA\n");
            cadastraConsulta(Fconsulta);
            limpaTela();
            break;
        case 4:
            printf("\t\tRELATORIO DO DIA\n");
            relatorioDia(Fconsulta);
            limpaTela();
            break;
        case 5:
            printf("\t\tRELATORIO DO PACIENTE \n");
            relatorioPaciente(Fconsulta);
            limpaTela();
            break;
        case 6:
            printf("\t\tRELATORIO DO MEDICO\n");
            relatorioMedico(Fconsulta);
            limpaTela();
            break;
        case 7:
            printf("\t\tLISTA MEDICO\n");
            listadeMedicos(Fmedico);
            limpaTela();
            break;
        case 8:
            printf("\t\tCANCELANDO CONSULTA\n");
            cancelaConsulta(Fconsulta);
            limpaTela();
            break;
        case 9:
            op = 9;
            break;
        default:
            printf("CODIGO INVALIDO");
            pausa();
            break;
        }
    }
    while(op!=9);
}



/*---------------------------------FUNCOES---------------------------------*/
//PAUSA
void pausa()
{
    system("pause");
}

//LIMPA TELA
void limpaTela()
{
    system("cls");
}

//LIMPA BUFFER
void limpaBuffer()
{
    fflush(stdin);
}

//CRIA ARQUIVOS
void criaArquivos()
{
    FILE *Fexistencia, *Fpaciente, *Fmedico, *Fconsulta;

    Fexistencia = fopen("C_existencia.dat","w+b");
    if(Fexistencia == NULL)
    {
        printf("Erro\n");
    }
    fclose(Fexistencia);

    Fpaciente = fopen("cadastro-paciente.dat","w+b");
    if(Fpaciente == NULL)
    {
        printf("Erro na abertura\n");
        exit(1);
    }
    fclose(Fpaciente);

    Fmedico = fopen("cadastro-medico.dat", "w+b");
    if(Fmedico == NULL)
    {
        printf("Erro na abertura\n");
        exit(2);
    }
    fclose(Fmedico);

    Fconsulta = fopen("cadastro-consulta.dat","w+b");
    if(Fconsulta == NULL)
    {
        printf("Erro na abertura\n");
        exit(3);
    }
    fclose(Fconsulta);
}

//MENU
void menu()
{
    printf("\t\t----- Clinica Viva Bem -----\n\n");
    printf("1- Cadastro do paciente\n");
    printf("2- Cadastro do medico\n");
    printf("3- Marcar da consulta\n");
    printf("4- Relatorio do dia \\ Mostra todas as consultas do dia\n");
    printf("5- Relatorio do paciente \\ Mostra todas conultas de um determinado paciente\n");
    printf("6- Relatorio do medico \\ Mostra todas consultas de um determinado medico\n");
    printf("7- Lista todos medicos\n");
    printf("8- Cancelamento da consulta\n");
    printf("\n\n9- Sair\n\n");
    printf("\n\nSelecione a opcao: ");
}

//CADASTRO DE PACIENTE
void cadastrarPaciente(FILE*Fpaciente)
{
    int tam=-1,achei=0;
    pacientes p[1000];

    Fpaciente = fopen("cadastro-paciente.dat", "r+b");
    if(Fpaciente == NULL)
    {
        printf("Erro");
        exit(1);
    }

    //conta o tamanho do vetor
    fseek(Fpaciente,0,SEEK_SET);
    if(!feof(Fpaciente))
    {
        tam=0;
    }
    else
    {
        while(!feof(Fpaciente))
        {
            fread(p,sizeof(p),1,Fpaciente);
            tam++;
        }
    }


    printf("Nome do paciente: ");
    limpaBuffer();
    gets(p[tam].nomeP);
    printf("Digite o numero de telefone: ");
    limpaBuffer();
    scanf("%d",&p[tam].telefoneP);
    printf("----------DATA DE NASCIMENTO-------------\n");
    printf("Digite o DIA:  ");
    limpaBuffer();
    scanf("%d",&p[tam].dataN[0]);
    printf("Digite o MES: ");
    limpaBuffer();
    scanf("%d",&p[tam].dataN[1]);
    printf("Digite o ANO: ");
    limpaBuffer();
    scanf("%d",&p[tam].dataN[2]);
    printf("----------ENDERECO-----------\n");
    printf("RUA: ");
    limpaBuffer();
    gets(p[tam].ruaP);
    printf("BAIRRO: ");
    limpaBuffer();
    gets(p[tam].bairroP);
    printf("CIDADE: ");
    limpaBuffer();
    gets(p[tam].cidadeP);
    printf("ESTADO: ");
    limpaBuffer();
    gets(p[tam].estadoP);
    p[tam].codigoP = (rand()%999)+1000;
    fseek(Fpaciente,0,SEEK_SET);
    fseek(Fpaciente,tam,SEEK_END);
    fwrite(p,sizeof(p),1,Fpaciente);
    limpaBuffer();

    fclose(Fpaciente);

}

//CADASTRO DE MEDICO
void cadastrarMedico(FILE*Fmedico)
{

    int tam=-1;
    medico m[90];

    Fmedico = fopen("cadastro-medico.dat", "r+b");
    if(Fmedico == NULL)
    {
        printf("Erro");
        exit(1);
    }

    //conta o tamanho do vetor
    fseek(Fmedico,0,SEEK_SET);
    if(!feof(Fmedico))
    {
        tam=0;
    }
    else
    {
        while(!feof(Fmedico))
        {
            fread(m,sizeof(m),1,Fmedico);
            tam++;
        }
    }

    printf("Nome: ");
    limpaBuffer();
    gets(&m[tam].nomeM);
    printf("Especialidade: ");
    limpaBuffer();
    gets(m[tam].especialidade);
    printf("Telefone: ");
    limpaBuffer();
    scanf("%d",&m[tam].telefoneM);
    m[tam].codigoM = (rand()%89)+10;
    fseek(Fmedico,tam,SEEK_END);
    fwrite(m,sizeof(m),1,Fmedico);
    fseek(Fmedico,0,SEEK_END);
    fclose(Fmedico);
}

//LOCALIZA PACIENTE
int localizaPaciente(char nomeP[30])
{

    int achou=0, posicao=-1;
    pacientes p;

    FILE*Fpaciente;
    Fpaciente = fopen("cadastro-paciente.dat", "r+b");
    if(Fpaciente == NULL)
    {
        printf("Erro");
        exit(1);
    }
    fseek(Fpaciente,0,SEEK_SET);
    fread(&p,sizeof(p),1,Fpaciente);
    while(!feof(Fpaciente) && !achou )
    {
        posicao++;
        if(strcmp(nomeP,p.nomeP)==0)
        {
            achou = 1;
        }
        fread(&p,sizeof(p),1,Fpaciente);
    }
    //printf("%d\n",posicao);
    //pausa();
    if(achou)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
    fclose(Fpaciente);
}

//LOCALIZA MEDICO
int localizaMedico(char nomeM[30])
{
    int achou=0, posicao=-1;
    medico m;

    FILE*Fmedico;
    Fmedico = fopen("cadastro-medico.dat", "r+b");
    if(Fmedico == NULL)
    {
        printf("Erro");
        exit(1);
    }
    fseek(Fmedico,0,SEEK_SET);
    fread(&m,sizeof(m),1,Fmedico);
    while(!feof(Fmedico) && !achou )
    {
        posicao++;
        if(strcmp(nomeM, m.nomeM)==0)
        {
            achou = 1;
        }
        fread(&m,sizeof(m),1,Fmedico);
    }
    if(achou)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
    fclose(Fmedico);
}

//CADASTRO DE CONSULTA
void cadastraConsulta(FILE*Fconsulta)
{
    char nomeP[30],nomeM[30];
    int posicaoP, posicaoM, tam=-1,aux=0;
    FILE *Fpaciente, *Fmedico;
    consulta c[10000];
    pacientes p;
    medico m;

    printf("Nome do Paciente: ");
    limpaBuffer();
    gets(nomeP);
    printf("Nome do medico: ");
    limpaBuffer();
    gets(nomeM);
    posicaoP = localizaPaciente(nomeP);
    posicaoM = localizaMedico(nomeM);
    if(posicaoP == -1 || posicaoM == -1  )
    {
        printf("Pessoa ou Medico nao exitem\n");
        pausa();
    }
    else
    {
        Fconsulta = fopen("cadastro-consulta.dat","r+b");
        if(Fconsulta == NULL)
        {
            printf("Erro");
            exit(1);
        }

        //conta o tamnho da consulta
        fseek(Fconsulta,0,SEEK_SET);
        if(!feof(Fconsulta))
        {
            tam=0;
        }
        else
        {
            while(!feof(Fconsulta))
            {
                fread(c,sizeof(c),1,Fconsulta);
                tam++;
            }
        }


        printf("DIA da consulta: ");
        limpaBuffer();
        scanf("%d",&c[tam].dataC[0]);
        printf("MES da consulta: ");
        limpaBuffer();
        scanf("%d",&c[tam].dataC[1]);
        printf("ANO da consulta: ");
        limpaBuffer();
        scanf("%d",&c[tam].dataC[2]);
        printf("Hora marcada de 13h as 18h\n");
        while(!aux)
        {
            printf("HORA da consulta de 13h as 18h: ");
            limpaBuffer();
            scanf("%d",&c[tam].horaC[0]);
            if(c[tam].horaC[0]>= 13 && c[tam].horaC[0]<=18)
            {
                printf("Consulta feita acada 30 minutos\n");
                printf("MINUTOS da consulta: ");
                limpaBuffer();
                scanf("%d",&c[tam].horaC[1]);
                if(c[tam].horaC[1]==0 || c[tam].horaC[1]==30)
                {
                    aux=1;
                }else{
                    printf("Minutos nao valido");
                }
            }else{
                printf("Horario nao valido");
            }
        }
        c[tam].status = 1;
        c[tam].codigoC =(rand() % 9999) + 10000;

        //salvando codigo do paciente
        Fpaciente = fopen("cadastro-paciente.dat","r+b");
        if(Fpaciente == NULL)
        {
            printf("Erro na abertura\n");
            exit(1);
        }

        fseek(Fpaciente,posicaoP,SEEK_SET);
        fread(&p,sizeof(p),1,Fpaciente);
        strcpy(c[tam].nomeP,p.nomeP);
        c[tam].codigoP = p.codigoP;
        fclose(Fpaciente);

        //salvando codigo no medico
        Fmedico = fopen("cadastro-medico.dat","r+b");
        if(Fmedico == NULL)
        {
            printf("Erro na abertura\n");
            exit(1);
        }

        fseek(Fmedico,posicaoM,SEEK_SET);
        fread(&m,sizeof(m),1,Fmedico);
        strcpy(c[tam].nomeM,m.nomeM);
        c[tam].codigoM = m.codigoM;
        fclose(Fmedico);

        fseek(Fconsulta,tam,SEEK_SET);
        fwrite(&c,sizeof(c),1,Fconsulta);
        fclose(Fconsulta);

    }
    pausa();
}

//RELATORIOS DO DIA
void relatorioDia(FILE*Fconsulta)
{

    int dia, mes, ano;
    consulta c;

    printf("DIA: ");
    limpaBuffer();
    scanf("%d",&dia);
    printf("MES: ");
    limpaBuffer();
    scanf("%d",&mes);
    printf("ANO: ");
    limpaBuffer();
    scanf("%d",&ano);

    Fconsulta = fopen("cadastro-consulta.dat","r+b");
    if(Fconsulta == NULL)
    {
        printf("Erro");
        exit(1);
    }

    fseek(Fconsulta,0,SEEK_SET);
    printf("\t\tData: %d/%d/%d\n",dia,mes,ano);
    while(!feof(Fconsulta))
    {
        fread(&c,sizeof(c),1,Fconsulta);
        if(dia == c.dataC[0])
        {
            if(mes == c.dataC[1])
            {
                if(ano == c.dataC[2])
                {
                    if(c.status != 0)
                    {
                        printf("Nome do paciente: %s\tCodigo: %d",c.nomeP,c.codigoP);
                        printf("\tNome do medico: %s\tCodigo: %d",c.nomeM,c.codigoM);
                        printf("\tCodigo da consulta: %d\n\n",c.codigoC);
                    }
                }
            }
        }
    }
    pausa();
    fclose(Fconsulta);


}

//RELATORIO PACIENTE
void relatorioPaciente(FILE*Fconsulta)
{

    char nomeP[30];
    consulta c;

    printf("Nome do paciente: ");
    limpaBuffer();
    gets(nomeP);

    Fconsulta = fopen("cadastro-consulta.dat","r+b");
    if(Fconsulta == NULL)
    {
        printf("Erro");
        exit(1);
    }

    fseek(Fconsulta,0,SEEK_SET);
    printf("Consultas do %s\n",nomeP);
    while(feof(Fconsulta))
    {
        fread(&c,sizeof(c),1,Fconsulta);
        if(strcmp(nomeP,c.nomeP) == 0)
        {
            if(c.status != 0)
            {
                printf("Data: %d/%d/%d",c.dataC[0],c.dataC[2],c.dataC[2]);
                printf("\tCodigo da consulta: %d",c.codigoC);
                printf("\tNome do medico: %s",c.nomeM);
            }
        }
    }
    pausa();
    fclose(Fconsulta);
}

//RELATORIO DO MEDICO
void relatorioMedico(FILE*Fconsulta)
{

    char nomeM[30];
    consulta c;

    printf("Nome do medico: ");
    limpaBuffer();
    gets(nomeM);

    Fconsulta = fopen("cadastro-consulta.dat","r+b");
    if(Fconsulta == NULL)
    {
        printf("Erro");
        exit(1);
    }

    fseek(Fconsulta,0,SEEK_SET);
    while(!feof(Fconsulta))
    {
        fread(&c,sizeof(c),1,Fconsulta);
        if(strcmp(nomeM,c.nomeM) == 0)
        {
            if(c.status != 0)
            {
                printf("Data %d/%d/%d\t",c.dataC[0],c.dataC[1],c.dataC[2]);
                printf("Codigo da cosulta: %d",c.codigoC);
            }
        }
    }
    pausa();
    fclose(Fconsulta);
}

//CANCELA CONSULTA
void cancelaConsulta(FILE*Fconsulta)
{

    int codigo, aux;
    consulta c;

    printf("Digite o codigo da consulta");
    limpaBuffer();
    scanf("%d",&codigo);

    Fconsulta = fopen("cadastro-consulta.dat","r+b");
    if(Fconsulta == NULL)
    {
        printf("Erro");
        exit(1);
    }

    fseek(Fconsulta,0, SEEK_SET);
    while(feof(Fconsulta))
    {
        fread(&c,sizeof(c),1,Fconsulta);
        if(codigo == c.codigoC)
        {
            printf("Para cancelar consulta aperte 0.");
            limpaBuffer();
            scanf("%d",&aux);
            if(aux == 0)
            {
                c.status = 0;
                printf("Consulta cancelada");
            }
        }
        else
        {
            printf("Consulta nao econtrada");
        }
    }
    pausa();
    fclose(Fconsulta);
}

//FUN��O EXTRA
void listadeMedicos(FILE*Fmedico)
{

    medico m;

    Fmedico = fopen("cadastro-medico.dat", "r+b");
    if(Fmedico == NULL)
    {
        printf("Erro");
        exit(1);
    }

    fseek(Fmedico,0,SEEK_SET);
    while(!feof(Fmedico))
    {
        fread(&m,sizeof(m),1,Fmedico);
        printf("\n Nome: %s\t",m.nomeM);
        printf("Codigo: %d\n",m.codigoM);
    }
    pausa();
    fclose(Fmedico);
}
