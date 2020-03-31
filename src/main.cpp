#include <iostream>
#include <time.h>
#include "listEnc.h"
#include "listDEnc.h"
#include "listCirc.h"
#include "tadEsp.h"
#include "delivery.h"

void contrataOuDemiteEntregador(TListaC<Entregador> &listaEntregadores, int &entregadorAtual){
    int checagemNovoEntregador = rand() % 150;
    if(checagemNovoEntregador == 0){
        const char* nomes[5] = {"Carlos", "Ricardo", "Douglas", "Pedro", "Mauricio"};
        int indexNome = rand() % 5;
        insereElementoFinal(listaEntregadores, {nomes[indexNome], 0});
        std::cout << "Novo Entregador: " << nomes[indexNome] << "\n";
    }
    if(checagemNovoEntregador == 1 && tamanho(listaEntregadores) > 1){
        if(entregadorAtual == tamanho(listaEntregadores) - 1){
            entregadorAtual = 0;
        }
        int deletando = rand() % tamanho(listaEntregadores);
        TElementoC<Entregador>* aserdel = retornaElemento(listaEntregadores, deletando);
        std::cout << aserdel->conteudo.nome << " se demitiu!\n";
        removeElementoPos(listaEntregadores, deletando);
        imprimeLista(listaEntregadores);
    }
}

int main(){
    srand(time(NULL));
    //Declaração de variáveis, cardapio, lista de pedidos, entregadores, preços, etc...
    TListaEnc<Item> cardapio;
    inicializaLista(cardapio);
    preencheCardapio(cardapio);

    TListaDE<Pedido> listaPedidos; //"Para estimar o tempo de entrega [...] deve ser percorrida do final até o início"
    inicializaLista(listaPedidos);

    int numeroEntregadores = 5;
    TListaC<Entregador> listaEntregadores;
    inicializaLista(listaEntregadores);
    preencheListaEntregadores(listaEntregadores, numeroEntregadores);
    imprimeLista(listaEntregadores);

    int entregadorAtual = 0;

    for(int tempoAtual = 1; tempoAtual <= 300 || tamanho(listaPedidos) > 0; tempoAtual++){ //O período de atendimento do restaurante é 5 horas. 
        std::cout << "Minuto Atual: " << tempoAtual << ".\n";
        if(tempoAtual % 2 == 0 && tempoAtual <= 300){ //A cada 2 minutos, uma nova compra é efetuada.
            criaPedido(cardapio, listaPedidos);
        }
        if(tamanho(listaPedidos) > 0){
            TElementoDE<Pedido>* pedido = retornaElemento(listaPedidos, 0);
            if(!pedido->conteudo.tempoPreparo){
                std::cout << "Pedido Finalizado: " << pedido->conteudo.alimento << " + " << pedido->conteudo.bebida << ": ";
                bool enviou = enviaEntregador(listaEntregadores, entregadorAtual);
                if(enviou){
                    removeElementoComeco(listaPedidos);
                    TElementoC<Entregador>* entregadorTemp = retornaElemento(listaEntregadores, entregadorAtual);
                    std::cout << "Entregue a " << entregadorTemp->conteudo.nome << "\n";
                } else {
                    std::cout << "Nao ha entregadores disponiveis.\n";
                }
            }
        }
        contrataOuDemiteEntregador(listaEntregadores, entregadorAtual);
        decrementaTempoPedidos(listaPedidos);
        decrementaTempoEntregadores(listaEntregadores);
        std::cout << "\n--------------------------------------------------------------\n";
    }
    imprimeLista(listaEntregadores);
    
}

//Calculo de caixa, dupla verifiação, etc...