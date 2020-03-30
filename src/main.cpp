#include <iostream>
#include "listEnc.h"
#include "listDEnc.h"
#include "listCirc.h"
#include "tadEsp.h"

void decrementaTempoEntregadores(TListaC<Entregador> &lista){
    for(TElementoC<Entregador>* nav = lista.primeiro->proximo; nav != lista.primeiro; nav = nav->proximo){
        if(nav->conteudo.tempoRestante){
            nav->conteudo.tempoRestante--;
        }
        //if(!nav->conteudo.tempoRestante && nav->conteudo.disponivel){
        //    nav->conteudo.tempoRestante
        //}
    }
}

TElementoC<Entregador>* selecionaEntregador(TListaC<Entregador> &lista, int &entregadorAtual){
    TElementoC<Entregador>* ultimo = retornaElemento(lista, entregadorAtual);
    for(TElementoC<Entregador>* nav = ultimo->proximo; nav != ultimo; nav = nav->proximo){
        if(nav->conteudo.disponivel && !nav->conteudo.tempoRestante){
            return nav;
        }
        entregadorAtual = (entregadorAtual + 1) % 6; //TODO: Deixar tamanho variável
    }
    return NULL;
}

bool enviaEntregador(TListaC<Entregador> &lista, int &entregadorAtual){
    TElementoC<Entregador>* entregador = selecionaEntregador(lista, entregadorAtual);
    if(entregador != NULL){
        //entregador->conteudo.disponivel = false;
        entregador->conteudo.tempoRestante = 7;
        return true;
    }
    return false;
}

int main(){
    //Declaração de variáveis, cardapio, lista de pedidos, entregadores, preços, etc...
    TListaEnc<Item> cardapio;
    inicializaLista(cardapio);
    preencheCardapio(cardapio);

    TListaDE<Pedido> listaPedidos;
    inicializaLista(listaPedidos);

    TListaC<Entregador> listaEntregadores;
    inicializaLista(listaEntregadores);
    preencheListaEntregadores(listaEntregadores, 6);

    int tempoPedido = 0, entregadorAtual = 0;

    for(int tempoAtual = 1; tempoAtual <= 300 || tamanho(listaPedidos) > 0; tempoAtual++){ //O período de atendimento do restaurante é 5 horas. 
        std::cout << "Minuto Atual: " << tempoAtual << ".\n";
        if(tempoAtual % 2 == 0 && tempoAtual <= 300){ //A cada 2 minutos, uma nova compra é efetuada.
            criaPedido(cardapio, listaPedidos);
            if(tempoPedido == 0){
                tempoPedido = 5;
            }
        }
        if(tamanho(listaPedidos) > 0 && tempoPedido == 0){
            TElementoDE<Pedido>* pedido = retornaElemento(listaPedidos, 0);
            std::cout << "Pedido Finalizado: " << pedido->conteudo.alimento << " + " << pedido->conteudo.bebida << "\n";
            bool enviou = enviaEntregador(listaEntregadores, entregadorAtual);
            if(enviou){
                removeElementoComeco(listaPedidos);
                TElementoC<Entregador>* entregadorTemp = retornaElemento(listaEntregadores, entregadorAtual);
                std::cout << "Entregue a " << entregadorTemp->conteudo.nome << "\n";
            } else {
                std::cout << "Não há entregadores disponiveis.\n";
            }
        }
        if(tempoPedido > 0){
            tempoPedido--;
        }
        decrementaTempoEntregadores(listaEntregadores);
        std::cout << "\n";
    }
}

//Calculo de caixa, dupla verifiação, etc...