#ifndef TADESP_H
#define TADESP_H

#include "listEnc.h"
#include <iostream>

struct Item{
    const char* nome;
    double preco;
};

struct Pedido{
    const char* alimento;
    const char* bebida;
    double preco;
};

struct Entregador {
    const char* nome;
    bool disponivel;
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

void preencheListaEntregadores(TListaC<Entregador> &lista, int tamanho){
    const char* nomes[10] = {"Marcelo", "Joao", "Rudson", "Marco", "Davi", "Carlos", "Ricardo", "Douglas", "Pedro", "Mauricio"};
    for(int i = 0; i < tamanho; i++){
        insereElementoFinal(lista, {nomes[i % 10], true, 0});
    }
}

void imprimeLista(TListaC<Entregador> &lista){
    if(lista.primeiro == NULL){
        std::cerr << "Lista de Pedidos Vazia.\n";
    } else {
        std::cout << "Imprimindo Lista de Pedidos \n";
        int contador = 0;
        TElementoC<Entregador>* nav = lista.primeiro;
        std::cout << "Entregador[" << contador << "]: " << nav->conteudo.nome << ", " << nav->conteudo.disponivel << "\n";
        nav = nav->proximo;
        contador++;
        for(nav; nav != lista.primeiro; nav = nav->proximo){
            std::cout << "Entregador[" << contador << "]: " << nav->conteudo.nome << ", " << nav->conteudo.disponivel << "\n";
            contador++;
        }
    }
}

void criaPedido(TListaEnc<Item> cardapio, TListaDE<Pedido> &listaPedidos){
    TElemento<Item>* alimento = retornaElemento(cardapio, rand() % 6);
    TElemento<Item>* bebida = retornaElemento(cardapio, (rand() % 6) + 6);
    insereElementoFinal(listaPedidos, {alimento->conteudo.nome, bebida->conteudo.nome, alimento->conteudo.preco + bebida->conteudo.preco});
    std::cout << "Novo Pedido! \n" << "Alimento: " << alimento->conteudo.nome << " | Bebida: " << bebida->conteudo.nome <<  " | Preco: " << alimento->conteudo.preco + bebida->conteudo.preco << ". \n";
}

void imprimeLista(TListaDE<Pedido> &lista){
	if(lista.primeiro == NULL){
		std::cerr << "Lista de Pedidos Vazia.\n";
	} else {
        std::cout << "Imprimindo Lista de Pedidos \n";
		int contador = 0;
        for(TElementoDE<Pedido>* nav = lista.primeiro; nav != NULL; nav = nav->proximo){
            std::cout << "Elemento[" << contador << "] Alimento: " << nav->conteudo.alimento << " | Bebida: " << nav->conteudo.bebida <<  " | Preco: " << nav->conteudo.preco << ". Anterior: " << nav->anterior << ", Addr: " << nav << ", Proximo: " << nav->proximo << ";\n";
            contador++;
        }
    }
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
}

#endif