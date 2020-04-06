#ifndef TADESP_H
#define TADESP_H

#include "listEst.h"
#include "listCirc.h"
#include "consts.h"
#include <iostream>

struct Item{
    const char* nome;       //Nome do item;
    double preco;           //Preço do item;
};

struct Pedido{
    const char* nome;       //Nome do cliente;
    const char* endereco;   //Endereço de entrega;
    const char* hora;       //Horario em que o pedido foi solicitado;
    const char* alimento;   //Alimento escolhido;
    const char* bebida;     //Bebida escolhida;
    double preco;           //Preço total do pedido;
    int tempoEstimado;      //Registro do tempo estimado;
    int tempoPreparo;       //Tempo de preparo do pedido;
};

struct Entregador {
    const char* nome;       //Nome do entregador;
    bool trabalhaHoje;      //Indica se o trabalhador trabalho no dia da simulação;
    int tempoRestante;      //Tempo restante para a entrega sendo executada;
};

void preencheCardapio(TListaEst<Item, 12>& lista){
    insereElementoFinal(lista, {"Pizza", 20.7});
    insereElementoFinal(lista, {"Hamburger", 12.9});
    insereElementoFinal(lista, {"Batata Frita", 12.2});
    insereElementoFinal(lista, {"Lasanha", 18.5});
    insereElementoFinal(lista, {"Cachorro Quente", 5.8});
    insereElementoFinal(lista, {"X Unico", 4.0});
    insereElementoFinal(lista, {"Refri", 4.5});
    insereElementoFinal(lista, {"Suco", 2.9});
    insereElementoFinal(lista, {"Cerveja", 6.4});
    insereElementoFinal(lista, {"Cafe", 3.2});
    insereElementoFinal(lista, {"Agua sem Gas", 2.7});
    insereElementoFinal(lista, {"Agua com Gas", 3.0});
}

void preencheListaEntregadores(TListaC<Entregador> &lista, int tamanho = 5){
    bool trabalhaHoje = true;
    for(int i = 0; i < tamanho; i++){
        if(i > 1 && rand() % 2 == 0){
            trabalhaHoje = false;
        } else {
            trabalhaHoje = true;
        }
        int randIndex = rand() % 1068;
        insereElementoFinal(lista, {nomes[randIndex], trabalhaHoje, 0});
    }
}

void imprimeLista(TListaC<Entregador> &lista){
    if(lista.primeiro == NULL){
        std::cerr << "Lista de Pedidos Vazia.\n";
    } else {
        std::cout << "Imprimindo Lista de Entregadores \n";
        int contador = 0;
        TElementoC<Entregador>* nav = lista.primeiro;
        std::cout << "Entregador[" << contador << "]: " << nav->conteudo.nome << ": addt: " << nav << ", proximo: " << nav->proximo << ", " << nav->conteudo.trabalhaHoje << "\n";
        nav = nav->proximo;
        contador++;
        for(nav; nav != lista.primeiro; nav = nav->proximo){
            std::cout << "Entregador[" << contador << "]: " << nav->conteudo.nome << ": addt: " << nav << ", proximo: " << nav->proximo << ", " << nav->conteudo.trabalhaHoje << "\n";
            contador++;
        }
    }
    std::cout << "\n";
}

void imprimeLista(TListaDE<Pedido> &lista){
    if(lista.primeiro == NULL){
        std::cerr << "Lista de Pedidos Vazia.\n";
    } else {
        std::cout << "Imprimindo Lista de Pedidos \n";
        int contador = 0;
        for(TElementoDE<Pedido>* nav = lista.primeiro; nav != NULL; nav = nav->proximo){
            std::cout << "Elemento[" << contador << "] Alimento: " << nav->conteudo.alimento << " | Bebida: " << nav->conteudo.bebida << " | Preco: " << nav->conteudo.preco << ". Addr: " << nav << ", Proximo: " << nav->proximo << ";\n";
            contador++;
        }
    }
    std::cout << "\n";
}

template <int tamanho>
void inicializaLista(TListaEst<Item, tamanho> &lista){
    lista.tamanho = tamanho;
    for(int i = 0; i < lista.tamanho; i++){
        lista.list[i] = {"", 0};
    }
    lista.contador = 0;
}

template <int tamanho>
Item retornaElemento(TListaEst<Item, tamanho> &lista, int pos){
    for(int i = 0; i < lista.tamanho; i++){
        if(i == pos){
            return lista.list[i];
        }
    }
    return {"", 0};
}

template <int tamanho>
void imprimeLista(TListaEst<Item, tamanho> lista){
    std::cout << "Cardapio:\n";
    for(int i = 0; i < tamanho; i++){
        if(lista.list[i].nome != ""){
            std::cout << lista.list[i].nome << ": R$" << lista.list[i].preco << ";\n";
        }
    }
    std::cout << "\n";
}

#endif