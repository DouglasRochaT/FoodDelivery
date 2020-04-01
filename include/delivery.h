#ifndef DELIVERYFUNCTIONS_H
#define DELIVERYFUNCTIONS_H

#include <iostream>
#include "listCirc.h"
#include "listDEnc.h"
#include "listEnc.h"
#include "tadEsp.h"

void decrementaTempoEntregadores(TListaC<Entregador> &lista){
    TElementoC<Entregador>* nav = lista.primeiro;
    if(nav->conteudo.tempoRestante){ nav->conteudo.tempoRestante--; }
    for(nav = lista.primeiro->proximo; nav != lista.primeiro; nav = nav->proximo){
        if(nav->conteudo.tempoRestante){
            nav->conteudo.tempoRestante--;
        }
    }
    std::cout << "\n";
}

TElementoC<Entregador>* selecionaEntregador(TListaC<Entregador> &listaEntregadores, TElementoC<Entregador>* &entregadorAtual){
    TElementoC<Entregador>* ultimo = entregadorAtual;
    for(entregadorAtual = entregadorAtual->proximo; entregadorAtual != ultimo; entregadorAtual = entregadorAtual->proximo){
        if(!entregadorAtual->conteudo.tempoRestante){
            return entregadorAtual;
        }
    }
    if(!ultimo->conteudo.tempoRestante){
        entregadorAtual = ultimo;
        return entregadorAtual;
    }
    return NULL;
}

bool enviaEntregador(TListaC<Entregador> &listaEntregadores, TElementoC<Entregador>* &entregadorAtual){
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
    std::cout << "Novo Pedido! \n" << "Alimento: " << alimento->conteudo.nome << " | Bebida: " << bebida->conteudo.nome << " | Preco: " << alimento->conteudo.preco + bebida->conteudo.preco << ". \n";
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

#endif#pragma once
