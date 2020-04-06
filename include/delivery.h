#ifndef DELIVERYFUNCTIONS_H
#define DELIVERYFUNCTIONS_H

#include <iostream>
#include <string.h>
#include "listCirc.h"
#include "listDEnc.h"
#include "listEst.h"
#include "tadEsp.h"
#include "consts.h"

//Formata o horário com base no tempo atual em minutos.
std::string retornaHorario(int tempoAtual){
    std::string hora = std::to_string(13 + (tempoAtual / 60));
    std::string minuto = std::to_string(tempoAtual % 60);
    if(tempoAtual % 60 < 10){
        return hora + ":0" + minuto;
    } else {
        return hora + ":" + minuto;
    }
}

//Define a probabilidade de uma contratação ou demissão de entregadores.
void contrataOuDemiteEntregador(TListaC<Entregador> &listaEntregadores, TElementoC<Entregador>* &entregadorAtual){
    std::cout << "--------------------------------------------------------------\n";
    int checagemEventoEntregador = rand() % 150;
    if(checagemEventoEntregador == 0){
        int indexNome = rand() % 1068;
        insereElementoFinal(listaEntregadores, {nomes[indexNome], 1, 0});
        std::cout << "Novo Entregador: " << nomes[indexNome] << "\n";
    }
    if(checagemEventoEntregador == 1 && retornaTamanho(listaEntregadores) > 2){
        int deletando = rand() % retornaTamanho(listaEntregadores);
        if(entregadorAtual == retornaElemento(listaEntregadores, deletando)){
            entregadorAtual = entregadorAtual->proximo;
        }
        TElementoC<Entregador>* aSerDeletado = retornaElemento(listaEntregadores, deletando);
        std::cout << aSerDeletado->conteudo.nome << " se demitiu!\n";
        removeElementoPos(listaEntregadores, deletando);
    }
}

//Seleciona o próximo entregador disponível para a entrega.
TElementoC<Entregador>* selecionaEntregador(TListaC<Entregador> &listaEntregadores, TElementoC<Entregador>* &entregadorAtual){
    TElementoC<Entregador>* ultimo = entregadorAtual;
    for(entregadorAtual = entregadorAtual->proximo; entregadorAtual != ultimo; entregadorAtual = entregadorAtual->proximo){
        if(!entregadorAtual->conteudo.tempoRestante && entregadorAtual->conteudo.trabalhaHoje){
            return entregadorAtual;
        }
    }
    if(!ultimo->conteudo.tempoRestante && entregadorAtual->conteudo.trabalhaHoje){
        entregadorAtual = ultimo;
        return entregadorAtual;
    }
    return NULL;
}

//Defíne o tempo de entrega e retorna true caso haja um entregador disponível, caso contrário, false.
bool enviaEntregador(TListaC<Entregador> &listaEntregadores, TElementoC<Entregador>* &entregadorAtual){
    TElementoC<Entregador>* entregador = selecionaEntregador(listaEntregadores, entregadorAtual);
    if(entregador != NULL){
        entregador->conteudo.tempoRestante = 7;
        return true;
    }
    return false;
}

//Direciona um pedido já concluído para a entrega caso haja entregadores disponíveis.
void entregaPedido(TListaDE<Pedido> &pedidosPendentes, TListaDE<Pedido> &pedidosConcluidos, TListaC<Entregador> &listaEntregadores, TElementoC<Entregador>* &entregadorAtual){
    if(retornaTamanho(pedidosPendentes) > 0){
        TElementoDE<Pedido>* pedido = retornaElemento(pedidosPendentes, 0);

        if(!pedido->conteudo.tempoPreparo){
            std::cout << "Pedido Finalizado: " << pedido->conteudo.alimento << " + " << pedido->conteudo.bebida << ": ";
            bool enviou = enviaEntregador(listaEntregadores, entregadorAtual);
            if(enviou){
                insereElementoFinal(pedidosConcluidos, pedido->conteudo);
                removeElementoComeco(pedidosPendentes);
                std::cout << "Entregador(a): " << entregadorAtual->conteudo.nome << "\n";
            } else {
                std::cout << "Nao ha entregadores disponiveis.\n";
            }
        }
    }
}

//Decrementa o tempo de entrega dos entregadores em operação.
void decrementaTempoEntregadores(TListaC<Entregador> &lista){
    TElementoC<Entregador>* nav = lista.primeiro;
    if(nav->conteudo.tempoRestante){ nav->conteudo.tempoRestante--; }
    for(nav = lista.primeiro->proximo; nav != lista.primeiro; nav = nav->proximo){
        if(nav->conteudo.tempoRestante){
            nav->conteudo.tempoRestante--;
        }
    }
}

//Estima o tempo de conclusão para um novo pedido.
int estimaTempo(TListaDE<Pedido> &pedidosPendentes){
    TElementoDE<Pedido>* nav = retornaElemento(pedidosPendentes, retornaTamanho(pedidosPendentes) - 1);
    int tempoEstimado = 5;
    for(nav; nav != NULL; nav = nav->anterior){
        tempoEstimado += nav->conteudo.tempoPreparo;
    }
    return tempoEstimado;
}

//Cria um novo pedido e o adiciona na lista de pedidos pendentes.
void criaPedido(TListaEst<Item, 12> cardapio, TListaDE<Pedido> &pedidosPendentes, const char* horario){
    const char* nomeDeEntrega = nomes[rand() % 1068];
    const char* enderecoDeEntrega = ruas[rand() % 135];
    Item alimento = retornaElemento(cardapio, rand() % 6);
    Item bebida = retornaElemento(cardapio, (rand() % 6) + 6);
    int tempoEstimado = estimaTempo(pedidosPendentes);
    insereElementoFinal(pedidosPendentes,
        {
            nomeDeEntrega,
            enderecoDeEntrega,
            horario,
            alimento.nome,
            bebida.nome,
            alimento.preco + bebida.preco,
            tempoEstimado,
            5
        });
    std::cout << "Novo Pedido! \n" << "Alimento: " << alimento.nome << " | Bebida: " << bebida.nome << " | Preco: " << alimento.preco + bebida.preco << ". \n";
    std::cout << "Encomendado em " << horario << ", Previsao de preparo: " << tempoEstimado << " minutos.\n";
    std::cout << "Entrega em " << enderecoDeEntrega << " para " << nomeDeEntrega << "\n";
}

//Reduz o tempo de todos os pedidos pendentes na cozinha.
void decrementaTempoPedidos(TListaDE<Pedido> &pedidosPendentes, int numeroCozinheiros){
    if(pedidosPendentes.primeiro == NULL){
        return;
    }
    for(TElementoDE<Pedido>* nav = pedidosPendentes.primeiro; nav != NULL; nav = nav->proximo){
        if(nav->conteudo.tempoPreparo){
            nav->conteudo.tempoPreparo--;
            numeroCozinheiros--;
            if(!numeroCozinheiros){
                return;
            }
        }
    }
}

//Dupla verificação, percorre-se a lista do início ao fim e após do fim ao começo. 
void fechaCaixa(TListaDE<Pedido> pedidosConcluidos){
    TElementoDE<Pedido>* nav = pedidosConcluidos.primeiro;
    TElementoDE<Pedido>* nav2 = pedidosConcluidos.primeiro;
    double primeiraContagem, segundaContagem;
    for(primeiraContagem = 0; nav != NULL; nav = nav->proximo){
        primeiraContagem += nav->conteudo.preco;
        nav2 = nav->anterior;
    }
    nav2 = nav2->proximo;
    for(segundaContagem = 0; nav2 != NULL; nav2 = nav2->anterior){
        segundaContagem += nav2->conteudo.preco;
    }
    if(abs(primeiraContagem - segundaContagem) < 0.001){
        std::cout << "O caixa foi fechado corretamente,\n";
        std::cout << "Foi arrecadado o valor de " << primeiraContagem << " reais. \n";
        std::cout << "Foram realizados " << retornaTamanho(pedidosConcluidos) << " pedidos.\n";
    } else {
        std::cerr << " Foi encontrada uma divegencia de " << primeiraContagem - segundaContagem << " reais no fechamento de caixa!";
    }
}

#endif