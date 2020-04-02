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
void inicializaLista(TListaC<type> &lista){
	lista.primeiro = NULL;
}

template<class type>
int retornaTamanho(TListaC<type> &lista){
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
bool insereElementoComeco(TListaC<type> &lista, type novoElemento){
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
bool insereElementoPos(TListaC<type>& lista, type novoElemento, int pos){
	if(pos > retornaTamanho(lista) || pos < 0){
		return false;
	} else if(pos == 0){
		return insereElementoComeco(lista, novoElemento);
	} else {
		TElementoC<type>* nav = lista.primeiro;
		int contador = 0;
		while(contador < pos){
			nav = nav->proximo;
			contador++;
		}
		TElementoC<type>* novo = new TElementoC<type>;
		novo->conteudo = novoElemento;
		novo->proximo = nav->proximo;
		novo->proximo = nav;
		return true;
	}
}

template<class type>
bool insereElementoFinal(TListaC<type> &lista, type novoElemento){
	return insereElementoPos(lista, novoElemento, retornaTamanho(lista));
}

template<class type>
bool removeElementoPos(TListaC<type> &lista, int pos){
	if(lista.primeiro == NULL || pos >= retornaTamanho(lista)){
		return false;
	} else if(pos == 0 && lista.primeiro->proximo == lista.primeiro){
		TElementoC<type>* nav = lista.primeiro;
		delete nav;
		lista.primeiro = NULL;
		return true;
	} else if(pos == 0){
		removeElementoComeco(lista);
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
bool removeElementoFinal(TListaC<type> &lista){
	return removeElementoPos(lista, retornaTamanho(lista) - 1);
}

template<class type>
bool removeElementoComeco(TListaC<type> &lista){
	if(lista.primeiro == NULL){
		return false;
	} else if(retornaTamanho(lista) == 1){
		delete lista.primeiro;
		lista.primeiro = NULL;
		return true;
	} else {
		TElementoC<type>* ultimo = lista.primeiro;
		while(ultimo->proximo != lista.primeiro){
			ultimo = ultimo->proximo;
		}
		TElementoC<type>* segundo = lista.primeiro->proximo;
		delete lista.primeiro;
		ultimo->proximo = segundo;
		lista.primeiro = segundo;
		return true;
	}
}

template<class type>
int retornaPosicao(TListaC<type> &lista, int elemento){
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
bool verificaExistencia(TListaC<type> &lista, type elemento){
	return retornaPosicao(lista, elemento) >= 0;
}

template<class type>
TElementoC<type>* retornaElemento(TListaC<type> &lista, int pos){
	if(pos >= retornaTamanho(lista)){
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
	return nullptr;
}

template<class type>
void imprimeLista(TListaC<type> &lista){
	if(lista.primeiro == NULL){
		std::cerr << "Lista vazia.\n";
	} else {
		TElementoC<type>* nav = lista.primeiro;
		int contador = 0;
		while(nav != lista.primeiro || contador == 0){
			std::cout << "Lista[" << contador << "](valor: " << nav->conteudo << ", endereco: " << nav << ", proximo: " << nav->proximo << ";\n";
			contador++;
			nav = nav->proximo;
		}
	}
}
#endif
