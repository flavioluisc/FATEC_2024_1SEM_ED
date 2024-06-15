#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct participante {
    int id;
    string nome;
    int semestre;
    int ingresso;
    int curso;
};

struct node {
    node  *anterior;
    node  *proximo;
    participante item;
};

struct lista {
    int cont;
    node * primeiroItem;
    node * ultimoItem;
};

struct contribuinte {
    int idParticipante;
    int mes;
    int ano;
    float valorContribuicao;
    contribuinte * proximoItem;
};

struct listaContribuinte {
    int cont;
    contribuinte * primeiroItem;
    contribuinte * ultimoItem;
};


participante criarParticipante();
void criarContribuinte(lista *, listaContribuinte * );
int pesquisarParticipante(int , lista *);
void inserirParticipante(lista *, participante);
void listarTudo(lista *);
void editarParticipante(lista *);
void lerGravarArquivo(lista *);
void gravarParticipantes(lista * );
void gravarContribuientes(listaContribuinte *);
 void gravarContribuientesPorCurso(listaContribuinte *, lista *);

int main() {

    lista *listagem = new lista;
    listagem->primeiroItem = NULL;
    listagem->ultimoItem = NULL;
    listagem->cont = 0;

    listaContribuinte * listagemContribuinte = new listaContribuinte;

    listagemContribuinte->primeiroItem = NULL;
    listagemContribuinte->ultimoItem = NULL;
    listagemContribuinte->cont =0;

    int loopMenu = 0;
    while(loopMenu == 0) {
        int opcaoMenu;
        cout << "Digite a opcao desejada" << endl;
        cout << "1 - Cadastrar participante" << endl;
        cout << "2 - listar participantes cadastrados" << endl;
        cout << "3 - Editar participante" << endl;
        cout << "4 - ler Arquivo" << endl;
        cout << "5 - Gravar Arquivo" << endl;
        cout << "6 - Cadastrar contribuinte" << endl;
        cout << "7 - Gravar Contribuintes" << endl;
        cout << "8 - Gerar relacoes de contribuentes" << endl;
        cout << "0 - Sair "<< endl;
        cin >> opcaoMenu;

        switch(opcaoMenu) {
            case 1:
                inserirParticipante(listagem, criarParticipante());
            break;
             case 2:
                listarTudo(listagem);
            break;
            case 3:
                editarParticipante(listagem);
            break;
            case 4:
                lerGravarArquivo(listagem);
            break;
            case 5:
                gravarParticipantes(listagem);
            break;
            case 6:
                criarContribuinte(listagem, listagemContribuinte);
            break;
            case 7:
                gravarContribuientes(listagemContribuinte);
            break;
             case 8:
                gravarContribuientesPorCurso(listagemContribuinte, listagem);
            break;
            case 0:
                return 0;
            break;
        }
    };
    return 0;
};

participante criarParticipante(){
    participante novoParticipante;

    cout << endl;
    cout << "Qual e seu primeiro nome?" << endl;
    cin >> novoParticipante.nome;
    cout << "Qual e seu curso?\nDigite 1 para DSM, 2 para SI ou 3 para GE" << endl;
    cin >> novoParticipante.curso ;
    cout << "Qual e seu ano de ingresso na Fatec?" << endl;
    cin >> novoParticipante.ingresso;
    cout << "Qual e seu semestre?" << endl;
    cin >> novoParticipante.semestre;
    novoParticipante.id = 0;

    return novoParticipante;
}

void inserirParticipante(lista *listagem, participante novoParticipante) {
    node *novoNode = new node;
    if( novoNode == NULL) {
        exit(1);
    }

    novoNode->anterior = NULL;
    novoNode->proximo = NULL;
    novoNode->item = novoParticipante;

    if(listagem->primeiroItem == NULL) {
        listagem->cont++;

        if( novoParticipante.id == 0 ) {
            novoNode->item.id=1;
        }

        listagem->primeiroItem = novoNode;
        return;
    }

    if( listagem->cont == 1) {
        listagem->cont++;

        if( novoParticipante.id == 0 ) {
            novoNode->item.id=2;
        }

        listagem->ultimoItem = novoNode;
        listagem->primeiroItem->proximo = listagem->ultimoItem;
        listagem->ultimoItem->anterior = listagem->primeiroItem;
        return;
    } else {

        if( novoParticipante.id == 0 ) {
            novoNode->item.id = listagem->ultimoItem->item.id + 1 ;
        }

        novoNode->anterior = listagem->ultimoItem;
        novoNode->anterior->proximo = novoNode;
        listagem->ultimoItem = novoNode;
        listagem->cont++;
        return;
    }
}

void listarTudo(lista *listagem) {
    if( listagem->cont== 0) {
        cout << endl << "Nenhum aluno registrado!";
        return;
    }

    node * itemTemp = listagem->primeiroItem;
    while( itemTemp != NULL) {
        cout << endl << "ID aluno: " << itemTemp->item.id;
        cout << endl << "Nome: " << itemTemp->item.nome;
        cout << endl << "Curso: " << itemTemp->item.curso;
        cout << endl << "Semestre: " << itemTemp->item.semestre;
        cout << endl << "Ano de Ingreso: " << itemTemp->item.ingresso;
          cout << endl;
        itemTemp = itemTemp->proximo;
    }
}

void editarParticipante(lista * listagem) {
    int idParticipante;
    int opcaoEditar;
    string temp;
    cout << "Informe o ID do participante:" << endl;
    cin >> idParticipante;
    node * participantePesquisado;
    participantePesquisado = NULL;
    node * itemTemp = listagem->primeiroItem;

    while( itemTemp != NULL) {
        if( itemTemp->item.id == idParticipante) {
            participantePesquisado = itemTemp;
            itemTemp = NULL;
        } else {
            itemTemp = itemTemp->proximo;
        }
    }
    if(participantePesquisado == NULL) {
        cout << endl << "Participante não encontrado!" << endl;
        return;
    }

    cout << "Qual informacao voce deseja alterar?\n1 Nome\n2 Curso\n3 Ano de ingresso\n4 Semestre" << endl;
    cin >> opcaoEditar;

    switch(opcaoEditar) {
            case 1:
                cout << "Digite o novo nome" << endl;
                cin >> participantePesquisado->item.nome;

            break;
             case 2:
                cout << "Digite o novo curso" << endl;
                cin >> participantePesquisado->item.curso;
            break;
            case 3:
                cout << "Digite o novo ano de ingresso" << endl;
                cin >> participantePesquisado->item.ingresso;
            break;
            case 4:
                cout << "Digite o novo semestre" << endl;
                cin >> participantePesquisado->item.semestre;
            break;
        }


};

int pesquisarParticipante(int idParticipante, lista * listagem) {
    node * participantePesquisado;
    participantePesquisado = NULL;
    node * itemTemp = listagem->primeiroItem;

    while( itemTemp != NULL) {
        if( itemTemp->item.id == idParticipante) {
            participantePesquisado = itemTemp;
            itemTemp = NULL;
        } else {
            itemTemp = itemTemp->proximo;
        }
    }

    if(participantePesquisado == NULL) {
        return 0;
    } else {
        return participantePesquisado->item.id;
    }

};

void lerGravarArquivo(lista * listagem) {
    ifstream txt("participantes.txt");
    if (!txt.is_open()) {
        cout << "Problemas na abertura do arquivo!" << endl;
        return;
    }
    int vezes = 0;
    string linha;
    participante novoParticipante;

    while (getline(txt, linha)) {
        try {
            novoParticipante.id = stol(linha);
            if (getline(txt, linha))
                novoParticipante.nome = linha;
            if (getline(txt, linha))
                novoParticipante.semestre = stol(linha);
            if (getline(txt, linha))
                novoParticipante.ingresso = stol(linha);
            if (getline(txt, linha))
                novoParticipante.curso = stol(linha);
        } catch (const std::exception& e) {
            cout << "Erro ao ler os dados: " << e.what() << endl;
            continue;
        }

        inserirParticipante(listagem, novoParticipante);
        vezes++;
    }

    if( vezes == 0 ) {
        cout << endl << "Nao foi encontrado nenhum valor!";
    } else {
        cout << endl << "Foi inserido  " << vezes << " Participantes!" << endl;
    }
    txt.close();
}



void gravarParticipantes(lista * listagem) {

    if( listagem->cont== 0) {
        cout << endl << "Nenhum aluno registrado!!!";
        return;
    }

    FILE *txt = fopen("participantes.txt", "w");
    if (txt == NULL) {
       cout << "Problemas na abertura do arquivo!" << endl;
       return;
    }


    node * itemTemp = listagem->primeiroItem;
    while( itemTemp != NULL) {
        fprintf(txt, "%d\n", itemTemp->item.id);
        fprintf(txt, "%s\n", itemTemp->item.nome.c_str());
        fprintf(txt, "%d\n", itemTemp->item.semestre);
        fprintf(txt, "%d\n", itemTemp->item.ingresso);
        fprintf(txt, "%d\n", itemTemp->item.curso);
        itemTemp = itemTemp->proximo;
    }

    fclose(txt);
}

void criarContribuinte(lista * listagem, listaContribuinte * listagemContribuinte) {
    contribuinte * novoContribuinte = new contribuinte;

    if( listagem->cont ==0) {
        cout << "Nenhum aluno cadastrado!";
        return;
    }

    cout << endl << "Qual o ID do participante?";
    cin >>  novoContribuinte->idParticipante;


    int auxLoopID=0;
    while( auxLoopID == 0 ) {
        novoContribuinte->idParticipante = pesquisarParticipante(novoContribuinte->idParticipante, listagem);
        if(novoContribuinte->idParticipante == 0 ) {
            cout << endl << "Qual o ID do participante? (Caso queria sair: Digite 0)";
            cin >> novoContribuinte->idParticipante;
            if( novoContribuinte->idParticipante == 0) {
                return;
            }
        } else {
            auxLoopID =1;
        }
    }

    cout << endl << "Qual e o mes? (entre 1 e 12)";
    cin >> novoContribuinte->mes;
    auxLoopID=0;
    while( auxLoopID == 0 ) {
        if(novoContribuinte->mes > 1 && novoContribuinte->mes > 12 ) {
            cout << endl << "Qual e o mes? (Caso queria sair: Digite 0)";
            cin >> novoContribuinte->mes;
            if( novoContribuinte->mes == 0 ) {
                return;
            }
        } else {
            auxLoopID = 1;
        }
    }

    cout << endl << "Qual e o ano? (maior que 2024)";
    cin >> novoContribuinte->ano;
    auxLoopID=0;
    while( auxLoopID == 0 ) {
        if(novoContribuinte->ano <2024 ) {
            cout << endl << "Qual e o ano? (Caso queria sair: Digite 0)";
            cin >> novoContribuinte->ano;
            if( novoContribuinte->ano == 0 ) {
                 return;
            }
        } else {
            auxLoopID = 1;
        }
    }

    cout << endl << "Qual e o valor de contribuicao?";
    cin >> novoContribuinte->valorContribuicao;

    if(listagemContribuinte->cont == 0 ) {
        listagemContribuinte->cont++;
        listagemContribuinte->primeiroItem = novoContribuinte;
        listagemContribuinte->primeiroItem->proximoItem = NULL;
    }

    if( listagemContribuinte->cont == 1) {
        listagemContribuinte->cont++;
        listagemContribuinte->ultimoItem = novoContribuinte;
        listagemContribuinte->primeiroItem->proximoItem = novoContribuinte;
    }

    if( listagemContribuinte->cont > 1) {
        listagemContribuinte->cont++;
        listagemContribuinte->ultimoItem->proximoItem = novoContribuinte;
        listagemContribuinte->ultimoItem = novoContribuinte;
         listagemContribuinte->ultimoItem->proximoItem = NULL;
    }
}

void gravarContribuientes(listaContribuinte * listagemContribuinte) {
    if( listagemContribuinte->cont == 0) {
        cout << endl << "Nenhum aluno registrado!" << endl;
        return;
    }

    FILE *txt = fopen("contribuintes.txt", "w");
    if (txt == NULL) {
       cout << "Problemas na abertura do arquivo!" << endl;
    }


    contribuinte * itemTemp = listagemContribuinte->primeiroItem;
    while( itemTemp != NULL) {
        fprintf(txt, "%d\n", itemTemp->idParticipante);
        fprintf(txt, "%d\n", itemTemp->mes);
        fprintf(txt, "%d\n", itemTemp->ano);
        fprintf(txt, "%f\n", itemTemp->valorContribuicao);
        itemTemp = itemTemp->proximoItem;
    }
    fclose(txt);

    if( listagemContribuinte->cont == 0) return;

    itemTemp = listagemContribuinte->primeiroItem;
    cout << itemTemp->proximoItem;
    while( itemTemp != NULL) {
        cout << endl << "ID participante: " << itemTemp->idParticipante;
        cout << endl << "mes: " << itemTemp->mes;
        cout << endl << "ano: " << itemTemp->ano;
        cout << endl << "contribuicao: " << itemTemp->valorContribuicao;
        cout << endl;
        itemTemp = itemTemp->proximoItem;
    }
}

void gravarContribuientesPorCurso(listaContribuinte * listagemContribuinte, lista * listagem) {
    if(listagemContribuinte->cont == 0) {
        cout << endl <<"Sem contribuicoes!";
        return;
    }

     if( listagemContribuinte->cont== 0) {
        cout << endl << "Nenhum aluno registrado!";
        return;
    }

    FILE *txtDSM = fopen("contribuintes_DSM.txt", "w");
    FILE *txtSI = fopen("contribuintes_SI.txt", "w");
    FILE *txtGE = fopen("contribuintes_GE.txt", "w");
    if (txtDSM == NULL || txtSI == NULL || txtGE == NULL) {
       cout << "Problemas na abertura do arquivo!" << endl;
       return;
    }

    contribuinte * itemTempContribuente = listagemContribuinte->primeiroItem;
    cout << itemTempContribuente->proximoItem;
    while( itemTempContribuente != NULL) {
        string auxCurso;

        node * itemTempParticipante = listagem->primeiroItem;

        while( itemTempParticipante != NULL) {
            if( itemTempParticipante->item.id == itemTempContribuente->idParticipante) {

                if(itemTempParticipante->item.curso ==1) {
                    fprintf(txtDSM, "%d\n", itemTempContribuente->idParticipante);
                    fprintf(txtDSM, "%d\n", itemTempContribuente->mes);
                    fprintf(txtDSM, "%d\n", itemTempContribuente->ano);
                    fprintf(txtDSM, "%f\n", itemTempContribuente->valorContribuicao);
                }

                if(itemTempParticipante->item.curso ==2) {
                    fprintf(txtSI, "%d\n", itemTempContribuente->idParticipante);
                    fprintf(txtSI, "%d\n", itemTempContribuente->mes);
                    fprintf(txtSI, "%d\n", itemTempContribuente->ano);
                    fprintf(txtSI, "%f\n", itemTempContribuente->valorContribuicao);
                }

                if(itemTempParticipante->item.curso ==3) {
                    fprintf(txtGE, "%d\n", itemTempContribuente->idParticipante);
                    fprintf(txtGE, "%d\n", itemTempContribuente->mes);
                    fprintf(txtGE, "%d\n", itemTempContribuente->ano);
                    fprintf(txtGE, "%f\n", itemTempContribuente->valorContribuicao);
                }
            }

            itemTempParticipante = itemTempParticipante->proximo;
        }

        itemTempContribuente = itemTempContribuente->proximoItem;
    }

    fclose(txtDSM);
    fclose(txtGE);
    fclose(txtSI);
}

