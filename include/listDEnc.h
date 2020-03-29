#ifndef LISTDOUBLEENC
#define LISTDOUBLEENC

#include <iostream>

template<class type>
struct TElementoDE {
	type conteudo;
	TElementoDE* anterior;
	TElementoDE* proximo;
};

template<class type>
struct TListaDE {
	TElementoDE<type>* primeiro;
};

template<class type>
int tamanho(TListaDE<type>& lista){
	TElementoDE<type>* nav = lista.primeiro;
	int contador = 0;
	while(nav != NULL){
		nav = nav->proximo;
		contador++;
	}
	return contador;
}

template<class type>
void inicializarLista(TListaDE<type>& lista){
	lista.primeiro = NULL;
}

template<class type>
void insereElementoFinal(TListaDE<type>& lista, type elemento){
	TElementoDE<type>* novo = new TElementoDE<type>;
	novo->conteudo = elemento;
	novo->proximo = NULL;
	if(lista.primeiro == NULL){
		lista.primeiro = novo;
		novo->anterior = NULL;
	} else {
		TElementoDE<type>* nav = lista.primeiro;
		while(nav->proximo != NULL){
			nav = nav->proximo;
		}
		nav->proximo = novo;
		novo->anterior = nav;
	}
}

template<class type>
void inserirElementoComeco(TListaDE<type>& lista, type elemento){
	TElementoDE<type>* novo = new TElementoDE<type>;
	if(tamanho(lista)){
		TElementoDE<type>* segundo = lista.primeiro;
		segundo->anterior = novo;
	}
	novo->conteudo = elemento;
	novo->proximo = lista.primeiro;
	novo->anterior = NULL;
	lista.primeiro = novo;
}

template<class type>
bool inserirElementoPos(TListaDE<type>& lista, type elemento, int pos){
	if(pos < 0 || pos > tamanho(lista)){
		return false;
	} else if(pos == 0){
		inserirElementoComeco(lista, elemento);
		return true;
	} else if(pos == tamanho(lista)){
		insereElementoFinal(lista, elemento);
		return true;
	} else {
		TElementoDE<type>* anterior = lista.primeiro;
		int contador = 0;
		while(contador < pos - 1){
			anterior = anterior->proximo;
			contador++;
		}
		TElementoDE<type>* posterior = anterior->proximo;
		TElementoDE<type>* novo = new TElementoDE<type>;
		novo->conteudo = elemento;
		novo->anterior = anterior;
		novo->proximo = posterior;
		posterior->anterior = novo;
		anterior->proximo = novo;
		return true;
	}
}

template<class type>
bool removerElementoComeco(TListaDE<type> &lista){
	if(lista.primeiro == NULL){
		return false;
	} else if(tamanho(lista) == 1){
		TElementoDE<type>* nav = lista.primeiro;
		delete nav;
		lista.primeiro = NULL;
		return true;
	} else {
		TElementoDE<type>* segundo = lista.primeiro;
		segundo = segundo->proximo;
		segundo->anterior = NULL;
		lista.primeiro = segundo;
		return true;
	}
}

template<class type>
bool removerElementoFinal(TListaDE<type> &lista){
	if(lista.primeiro == NULL){
		return false;
	} else if(tamanho(lista) == 1){
		TElementoDE<type>* nav = lista.primeiro;
		delete nav;
		lista.primeiro = NULL;
		return true;
	} else {
		TElementoDE<type>* navAnt = lista.primeiro;
		TElementoDE<type>* nav = navAnt->proximo;
		while(nav->proximo != NULL){
			navAnt = nav;
			nav = nav->proximo;
		}
		navAnt->proximo = NULL;
		delete nav;
		return true;
	}
}

template<class type>
bool removerElementoPos(TListaDE<type> &lista, int pos){
	if(lista.primeiro == NULL || pos >= tamanho(lista)){
		return false;
	} else if(pos == 0){
		removerElementoComeco(lista);
	} else {
		TElementoDE<type>* nav = lista.primeiro;
		int contador = 0;
		while(contador < pos){
			nav = nav->proximo;
			contador++;
		}
		TElementoDE<type>* navAnt = nav->anterior;
		TElementoDE<type>* navProx = nav->proximo;
		if(navAnt != NULL){
			navAnt->proximo = navProx;
		}
		if(navProx != NULL){
			navProx->anterior = navAnt;
		}
		delete nav;
		return true;
	}
}

template<class type>
TElementoDE<type>* retornaElemento(TListaDE<type> &lista, int pos){
	if(pos >= tamanho(lista)){
		return nullptr;
	} else {
		TElementoDE<type>* nav = lista.primeiro;
		int contador = 0;
		while(contador < pos){
			nav = nav->proximo;
			contador++;
		}
		return nav;
	}
}

template<class type>
int procurar(TListaDE<type> &lista, type elemento){
	TElementoDE<type>* nav = lista.primeiro;
	int contador = 0;
	while(nav != NULL){
		if(nav->conteudo == elemento){
			return contador;
		}
		nav = nav->proximo;
		contador++;
	}
	return -1;
}

template<class type>
bool estaContido(TListaDE<type> &lista, type elemento){
	TElementoDE<type>* nav = lista.primeiro;
	while(nav != NULL){
		if(nav->conteudo == elemento){
			return true;
		}
		nav = nav->proximo;
	}
	return false;
}

template<class type>
void imprimeLista(TListaDE<type> &lista){
	if(lista.primeiro == NULL){
		std::cout << "Lista vazia.\n";
	} else {
		TElementoDE<type>* nav = lista.primeiro;
		int contador = 0;
		while(nav->proximo != NULL){
			std::cout << "lista[" << contador << "] = conteudo: " << nav->conteudo << ", ante: " << nav->anterior << ", addr: " << nav << ", prox: " << nav->proximo << ";\n";
			nav = nav->proximo;
			contador++;
		}
		std::cout << "lista[" << contador << "] = conteudo: " << nav->conteudo << ", ante: " << nav->anterior << ", addr: " << nav << ", prox: " << nav->proximo << ";\n";

		nav = lista.primeiro;
		while(nav->proximo != NULL){
			std::cout << nav->conteudo << ", ";
			nav = nav->proximo;
			contador++;
		}
		std::cout << nav->conteudo << ".\n";
	}
}

#endif
