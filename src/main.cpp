#include <iostream>
#include <time.h>
#include "listEnc.h"
#include "listDEnc.h"
#include "listCirc.h"
#include "tadEsp.h"
#include "delivery.h"

void contrataOuDemiteEntregador(TListaC<Entregador> &listaEntregadores, TElementoC<Entregador>* &entregadorAtual){
    int checagemEventoEntregador = rand() % 150;
    if(checagemEventoEntregador == 0){
        const char* nomes[5] = {"Carlos", "Ricardo", "Douglas", "Pedro", "Mauricio"};
        int indexNome = rand() % 5;
        insereElementoFinal(listaEntregadores, {nomes[indexNome], 0});
        std::cout << "Novo Entregador: " << nomes[indexNome] << "\n";
    }
    if(checagemEventoEntregador == 1 && tamanho(listaEntregadores) > 1){
        int deletando = rand() % tamanho(listaEntregadores);
        if(entregadorAtual == retornaElemento(listaEntregadores, deletando)){
            entregadorAtual = entregadorAtual->proximo;
        }
        TElementoC<Entregador>* aSerDeletado = retornaElemento(listaEntregadores, deletando);
        std::cout << aSerDeletado->conteudo.nome << " se demitiu!\n";
        removeElementoPos(listaEntregadores, deletando);
        imprimeLista(listaEntregadores);
    }
}

void entregaPedido(TListaDE<Pedido> &listaPedidos, TListaC<Entregador> &listaEntregadores, TElementoC<Entregador>* &entregadorAtual){
    if(tamanho(listaPedidos) > 0){
        TElementoDE<Pedido>* pedido = retornaElemento(listaPedidos, 0);
        if(!pedido->conteudo.tempoPreparo){
            std::cout << "Pedido Finalizado: " << pedido->conteudo.alimento << " + " << pedido->conteudo.bebida << ": ";
            bool enviou = enviaEntregador(listaEntregadores, entregadorAtual);
            if(enviou){
                removeElementoComeco(listaPedidos);
                std::cout << "Entregue a " << entregadorAtual->conteudo.nome << "\n";
            } else {
                std::cout << "Nao ha entregadores disponiveis.\n";
            }
        }
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
    
    //int entregadorAtual = 0;
    TElementoC<Entregador>* entregadorAtual = listaEntregadores.primeiro;

    for(int tempoAtual = 1; tempoAtual <= 300 || tamanho(listaPedidos) > 0; tempoAtual++){ //O período de atendimento do restaurante é 5 horas. 
        std::cout << "Minuto Atual: " << tempoAtual << ".\n";
        if(tempoAtual % 2 == 0 && tempoAtual <= 300){ //A cada 2 minutos, uma nova compra é efetuada.
            criaPedido(cardapio, listaPedidos);
        }
        entregaPedido(listaPedidos, listaEntregadores, entregadorAtual);
        contrataOuDemiteEntregador(listaEntregadores, entregadorAtual);
        decrementaTempoPedidos(listaPedidos);
        decrementaTempoEntregadores(listaEntregadores);
        std::cout << "\n--------------------------------------------------------------\n";
    }
    imprimeLista(listaEntregadores);
    
}

//Calculo de caixa, dupla verifiação, etc...