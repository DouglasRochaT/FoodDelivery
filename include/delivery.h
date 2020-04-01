#ifndef DELIVERYFUNCTIONS_H
#define DELIVERYFUNCTIONS_H

#include <iostream>
#include "listCirc.h"
#include "listDEnc.h"
#include "listEnc.h"
#include "tadEsp.h"

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

void entregaPedido(TListaDE<Pedido> &pedidosPendentes, TListaDE<Pedido> &pedidosConcluidos, TListaC<Entregador> &listaEntregadores, TElementoC<Entregador>* &entregadorAtual){
    if(tamanho(pedidosPendentes) > 0){
        TElementoDE<Pedido>* pedido = retornaElemento(pedidosPendentes, 0);
        if(!pedido->conteudo.tempoPreparo){
            std::cout << "Pedido Finalizado: " << pedido->conteudo.alimento << " + " << pedido->conteudo.bebida << ": ";
            bool enviou = enviaEntregador(listaEntregadores, entregadorAtual);
            if(enviou){
                Pedido temp = retornaElemento(pedidosPendentes, 0)->conteudo;
                insereElementoFinal(pedidosConcluidos, temp);
                removeElementoComeco(pedidosPendentes);
                std::cout << "Entregue a " << entregadorAtual->conteudo.nome << "\n";
            } else {
                std::cout << "Nao ha entregadores disponiveis.\n";
            }
        }
    }
}

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

void criaPedido(TListaEnc<Item> cardapio, TListaDE<Pedido> &pedidosPendentes){
    TElemento<Item>* alimento = retornaElemento(cardapio, rand() % 6);
    TElemento<Item>* bebida = retornaElemento(cardapio, (rand() % 6) + 6);
    insereElementoFinal(pedidosPendentes, {alimento->conteudo.nome, bebida->conteudo.nome, alimento->conteudo.preco + bebida->conteudo.preco, 5});
    std::cout << "Novo Pedido! \n" << "Alimento: " << alimento->conteudo.nome << " | Bebida: " << bebida->conteudo.nome << " | Preco: " << alimento->conteudo.preco + bebida->conteudo.preco << ". \n";
}

void decrementaTempoPedidos(TListaDE<Pedido> &pedidosPendentes, int numeroCozinheiros){
    if(pedidosPendentes.primeiro == NULL){
        return;
    }
    for(TElementoDE<Pedido>* nav = pedidosPendentes.primeiro; nav != NULL; nav = nav->proximo){
        std::cout << nav->conteudo.tempoPreparo << ", ";
        if(nav->conteudo.tempoPreparo){
            nav->conteudo.tempoPreparo--;
            numeroCozinheiros--;
            if(!numeroCozinheiros){
                return;
            }
        }
    }
    std::cout << "Tamanho: " << tamanho(pedidosPendentes);
}

#endif
