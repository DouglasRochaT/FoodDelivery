#ifndef TADESP_H
#define TADESP_H

#include "listEnc.h"
#include "consts.h"
#include <iostream>

struct Item{
    const char* nome;
    double preco;
};

struct Pedido{ //TODO: implementar nome, endereço e tempo estimado
    const char* nome;
    const char* endereco;
    std::string hora;
    const char* alimento;
    const char* bebida;
    double preco;
    int tempoEstimado;
    int tempoPreparo;
};

struct Entregador {
    const char* nome;
    bool trabalhaHoje;
    int tempoRestante;
};

void preencheCardapio(TListaEnc<Item>& lista){
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

void imprimeLista(TListaEnc<Item> &lista){
    if(lista.primeiro == NULL){
        std::cerr << "Cardapio Vazio.\n";
        return;
    }
    std::cout << "Imprimindo Cardapio: \n";
    int index = 0;
    for(TElemento<Item>* nav = lista.primeiro; nav != NULL || index == 0; nav = nav->proximo){
        std::cout << "Elemento[" << index << "] Nome: " << nav->conteudo.nome << " | Preco: " << nav->conteudo.preco << ". Addr: " << nav << ", Proximo: " << nav->proximo << ";\n";
        index++;
    }
    std::cout << "\n";
}

#endif