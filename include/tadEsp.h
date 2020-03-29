#ifndef TADESP_H
#define TADESP_H

#include "listDEnc.h"

struct Item{
    const char* nome;
    float preco;
};

void inicializarLista(TListaDE<Item>& lista){
	lista.primeiro = NULL;
}

void preencheCardapio(TListaDE<Item>& lista){
    inserirElementoFinal(lista, {"Pizza", 20.7});
    inserirElementoFinal(lista, {"Hamburger", 12.9});
    inserirElementoFinal(lista, {"Batata Frita", 12.2});
    inserirElementoFinal(lista, {"Lasanha", 18.5});
    inserirElementoFinal(lista, {"Cachorro Quente", 5.8});
    inserirElementoFinal(lista, {"X Unico", 4.0});
    inserirElementoFinal(lista, {"Refri", 4.5});
    inserirElementoFinal(lista, {"Suco", 2.9});
    inserirElementoFinal(lista, {"Cerveja", 6.4});
    inserirElementoFinal(lista, {"Cafe", 3.2});
    inserirElementoFinal(lista, {"Agua sem Gas", 2.7});
    inserirElementoFinal(lista, {"Agua com Gas", 3.0});    
}

void printLista(TListaDE<Item>& lista){
	if(lista.primeiro == NULL){
		std::cout << "Lista vazia.\n";
	} else {
		TElementoDE<Item>* nav = lista.primeiro;
		int contador = 0;
		while(nav->proximo != NULL ){
			std::cout << "lista[" << contador << "] = item: " << nav->conteudo.nome << " |" << " preco: " << nav->conteudo.preco << ", ante: " << nav->anterior << ", addr: " << nav << ", prox: " << nav->proximo << ";\n";
			nav = nav->proximo;
			contador++;
		}
		std::cout << "lista[" << contador << "] = item: " << nav->conteudo.nome << " |" << " preco: " << nav->conteudo.preco << ", ante: " << nav->anterior << ", addr: " << nav << ", prox: " << nav->proximo << ";\n";

		nav = lista.primeiro;
		while(nav->proximo != NULL){
			std::cout << nav->conteudo.nome << " | " << nav->conteudo.preco << ", ";
			nav = nav->proximo;
			contador++;
		}
		std::cout << nav->conteudo.nome << " | " << nav->conteudo.preco << ".\n";
	}
};

#endif