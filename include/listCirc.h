#ifndef TLISTACIRC
#define TLISTACIRC

#include <iostream>

template<class type>
struct TElementoC {
	type conteudo;
	TElementoC* proximo;
};

template<class type>
struct TListaC {
	TElementoC<type>* primeiro;
};

template<class type>
void inicializarLista(TListaC<type> &lista){
	lista.primeiro = NULL;
}

template<class type>
int tamanho(TListaC<type> &lista){
	if(lista.primeiro == NULL){
		return 0;
	} else {
		TElementoC<type>* nav = lista.primeiro;
		int contador = 1;
		while(nav->proximo != lista.primeiro){
			contador++;
			nav = nav->proximo;
		}
		return contador;
	}
}

template<class type>
bool inserirElementoComeco(TListaC<type> &lista, type novoElemento){
	if(lista.primeiro == NULL){
		TElementoC<type>* novo = new TElementoC<type>;
		lista.primeiro = novo;
		novo->proximo = novo;
		novo->conteudo = novoElemento;
	} else {
		TElementoC<type>* ultimo = lista.primeiro;
		while(ultimo->proximo != lista.primeiro){
			ultimo = ultimo->proximo;
		}
		TElementoC<type>* novo = new TElementoC<type>;
		novo->conteudo = novoElemento;
		novo->proximo = lista.primeiro;
		lista.primeiro = novo;
		ultimo->proximo = novo;
	}
	return true;
}

template<class type>
bool inserirElementoPos(TListaC<type>& lista, int novoElemento, int pos){
	if(pos > tamanho(lista) || pos < 0){
		return false;
	} else if(pos == 0) {
		return inserirElementoComeco(lista, novoElemento);
	} else {
		TElementoC<type>* nav = lista.primeiro;
		TElementoC<type>* navAnt = lista.primeiro;
		int contador = 0;
		while(contador < pos){
			navAnt = nav;
			nav = nav->proximo;
			contador++;
		}
		TElementoC<type>* novo = new TElementoC<type>;
		novo->conteudo = novoElemento;
		navAnt->proximo = novo;
		novo->proximo = nav;
		return true;
	}
}

template<class type>
bool insereElementoFinal(TListaC<type> &lista, int novoElemento){
	return inserirElementoPos(lista, novoElemento, tamanho(lista));
}

template<class type>
bool removerElementoPos(TListaC<type> &lista, int pos){
	if(lista.primeiro == NULL || pos >= tamanho(lista)){
		return false;
	} else if(pos == 0 && lista.primeiro->proximo == lista.primeiro){
		TElementoC<type>* nav = lista.primeiro;
		delete nav;
		lista.primeiro = NULL;
		return true;
	} else {
		TElementoC<type>* nav = lista.primeiro;
		TElementoC<type>* navAnt = nav;
		int contador = 1;
		while(contador <= pos){
			navAnt = nav;
			nav = nav->proximo;
			contador++;
		}
		navAnt->proximo = nav->proximo;
		delete nav;
		return true;
	}
}

template<class type>
bool removerElementoFinal(TListaC<type> &lista){
	return removerElementoPos(lista, tamanho(lista) - 1);
}

template<class type>
bool removerElementoComeco(TListaC<type> &lista){
	if(lista.primeiro == NULL){
		return false;
	} else if(tamanho(lista) == 1){
		delete lista.primeiro;
		lista.primeiro = NULL;
		return true;
	} else {
		TElementoC<type>* ultimo = lista.primeiro;
		while(ultimo->proximo != lista.primeiro){
			ultimo = ultimo->proximo;
		}
		TElementoC<type>* segundo = lista.primeiro;
		segundo = segundo->proximo;
		delete lista.primeiro;
		ultimo->proximo = segundo;
		lista.primeiro = segundo;
		return true;
	}
}

template<class type>
int procurar(TListaC<type> &lista, int elemento){
	TElementoC<type>* nav = lista.primeiro;
	int contador = 0;
	while(nav->proximo != lista.primeiro){
		if(nav->conteudo == elemento){
			return contador;
		} else {
			contador++;
			nav = nav->proximo;
		}
	}
	if(nav->conteudo == elemento){
		return contador;
	}
	return -1;
}

template<class type>
bool estaContido(TListaC<type> &lista, type elemento){
	return procurar(lista, elemento) >= 0;
}

template<class type>
TElementoC<type>* retornaElemento(TListaC<type> &lista, int pos){
	if(pos >= tamanho(lista)){
		//throw "Index out of range";
		return nullptr;
	} else {
		TElementoC<type>* nav = lista.primeiro;
		int contador = 0;
		while(nav->proximo != lista.primeiro){
			if(contador == pos){
				return nav;
			}
			nav = nav->proximo;
			contador++;
		}
		if(contador == pos){
			return nav;
		}
	}
}

template<class type>
void imprimeLista(TListaC<type> &lista){
	if(lista.primeiro == NULL){
		std::cout << "Lista vazia.\n";
	} else {
		//print detalhado de cada item
		TElementoC<type>* nav = lista.primeiro;
		int contador = 0;
		while(nav->proximo != lista.primeiro){
			std::cout << "lista[" << contador << "](valor: " << nav->conteudo << ", endereco: " << nav << ", proximo: " << nav->proximo << ";\n";
			contador++;
			nav = nav->proximo;
		}
		std::cout << "lista[" << contador << "](valor: " << nav->conteudo << ", endereco: " << nav << ", proximo: " << nav->proximo << ";\n";
		//print dos conteudos de cada item
		nav = lista.primeiro;
		while(nav->proximo != lista.primeiro){
			std::cout << nav->conteudo << ", ";
			nav = nav->proximo;
		}
		std::cout << nav->conteudo << ".\n";
	}
}
#endif
