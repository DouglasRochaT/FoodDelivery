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
    }
}

TElementoC<Entregador>* selecionaEntregador(TListaC<Entregador> &listaEntregadores, int &entregadorAtual){
    TElementoC<Entregador>* ultimo = retornaElemento(listaEntregadores, entregadorAtual);
    for(TElementoC<Entregador>* nav = ultimo->proximo; nav != ultimo; nav = nav->proximo){
        if(!nav->conteudo.tempoRestante){
            return nav;
        }
        entregadorAtual = (entregadorAtual + 1) % 6; //TODO: Deixar tamanho variável
    }
    return NULL;
}

bool enviaEntregador(TListaC<Entregador> &listaEntregadores, int &entregadorAtual){
    TElementoC<Entregador>* entregador = selecionaEntregador(listaEntregadores, entregadorAtual);
    if(entregador != NULL){
        entregador->conteudo.tempoRestante = 7;
        return true;
    }
    return false;
}

void criaPedido(TListaEnc<Item> cardapio, TListaDE<Pedido> &listaPedidos){
    TElemento<Item>* alimento = retornaElemento(cardapio, rand() % 6);
    TElemento<Item>* bebida = retornaElemento(cardapio, (rand() % 6) + 6);
    insereElementoFinal(listaPedidos, {alimento->conteudo.nome, bebida->conteudo.nome, alimento->conteudo.preco + bebida->conteudo.preco, 5});
    std::cout << "Novo Pedido! \n" << "Alimento: " << alimento->conteudo.nome << " | Bebida: " << bebida->conteudo.nome <<  " | Preco: " << alimento->conteudo.preco + bebida->conteudo.preco << ". \n";
}

void decrementaTempoPedidos(TListaDE<Pedido> &listaPedidos){
    if(listaPedidos.primeiro == NULL){
		return;
	}
    for(TElementoDE<Pedido>* nav = listaPedidos.primeiro; nav != NULL; nav = nav->proximo){
        if(nav->conteudo.tempoPreparo){
            nav->conteudo.tempoPreparo--;
        }
    }
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

    int entregadorAtual = 0;

    for(int tempoAtual = 1; tempoAtual <= 300 || tamanho(listaPedidos) > 0; tempoAtual++){ //O período de atendimento do restaurante é 5 horas. 
        std::cout << "Minuto Atual: " << tempoAtual << ".\n";
        if(tempoAtual % 2 == 0 && tempoAtual <= 300){ //A cada 2 minutos, uma nova compra é efetuada.
            criaPedido(cardapio, listaPedidos);
        }
        if(tamanho(listaPedidos) > 0){
            TElementoDE<Pedido>* pedido = retornaElemento(listaPedidos, 0);
            if(!pedido->conteudo.tempoPreparo){
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
        }
        decrementaTempoPedidos(listaPedidos);
        decrementaTempoEntregadores(listaEntregadores);
        std::cout << "\n";
    }
}

//Calculo de caixa, dupla verifiação, etc...