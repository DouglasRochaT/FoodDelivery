#ifndef LISTENC_H
#define LISTENC_H

template <class type>
struct TElemento {
	type conteudo;
	TElemento* proximo;
};

template <class type>
struct TListaEnc {
	TElemento<type>* primeiro;
};

template<class type>
void inicializarLista(TListaEnc<type> &lista){
	lista.primeiro = NULL;
}

template<class type>
int tamanho(TListaEnc<type> &lista){
	TElemento<type>* nav = lista.primeiro;
	int contador = 1;
	while(nav->proximo != NULL){
		nav = nav->proximo;
		contador++;
	}
	return contador;
}

template<class type>
TElemento<type>* criaElemento(TListaEnc<type> &lista, type conteudo, TElemento<type>* ponteiroApos = NULL){
	TElemento<type>* elemento = new TElemento<type>;
	elemento->conteudo = conteudo;
	elemento->proximo = ponteiroApos;
	return elemento;
}

template<class type>
void insereElementoFinal(TListaEnc<type> &lista, type conteudo){
	if(lista.primeiro == NULL){
		lista.primeiro = criaElemento(lista, conteudo);
	} else {
		TElemento<type>* nav = lista.primeiro;
		while(nav->proximo != NULL){
			nav = nav->proximo;
		}
		nav->proximo = criaElemento(lista, conteudo);
	}
}

template<class type>
void inserirElementoComeco(TListaEnc<type> &lista, type conteudo){
	if(lista.primeiro == NULL){
		lista.primeiro = criaElemento(lista, conteudo);
	} else {
		TElemento<type>* nav = lista.primeiro;
		lista.primeiro = criaElemento(lista, conteudo, nav);
	}
}

template<class type>
bool inserirElementoPos(TListaEnc<type> &lista, type conteudo, int pos){
	if(pos > coletatamanho(lista) || pos < 0){
		return false;
	} else {
		TElemento<type>* nav = lista.primeiro;
		int contador = 0;
		while(contador < pos - 1){
			nav = nav->proximo;
			contador++;
		}
		if(pos == 0){
			if(nav->proximo == NULL){
				lista.primeiro = criaElemento(lista, conteudo);
			} else {
				TElemento<type>* nav2 = lista.primeiro;
				lista.primeiro = criaElemento(lista, conteudo, nav2);
			}
		} else {
			if(nav->proximo == NULL){
				nav->proximo = criaElemento(lista, conteudo);
			} else {
				TElemento<type>* nav2 = nav->proximo;
				nav->proximo = criaElemento(lista, conteudo, nav2);
			}
		}
		return true;
	}
}

template<class type>
bool removerElementoFinal(TListaEnc<type> &lista){
	if(lista.primeiro == NULL){
		return false;
	}
	TElemento<type>* navPrev = lista.primeiro;
	if(navPrev->proximo == NULL){
		delete navPrev;
		lista.primeiro = NULL;
		return true;
	}
	TElemento<type>* nav = navPrev->proximo;
	while(nav->proximo != NULL){
		navPrev = nav;
		nav = navPrev->proximo;
	}
	delete nav;
	navPrev->proximo = NULL;
	return true;
}

template<class type>
bool removerElementoComeco(TListaEnc<type> &lista){
	if(lista.primeiro == NULL){
		throw "Nao foi possivel deletar, a lista esta vazia.";
		return false;
	} else if(tamanho(lista) == 1){
		delete lista.primeiro;
		lista.primeiro = NULL;
		return true;
	} else {
		TElemento<type>* segundo = lista.primeiro;
		segundo = segundo->proximo;
		delete lista.primeiro;
		lista.primeiro = segundo;
		return true;
	}
}

template<class type>
bool removerElementoPos(TListaEnc<type> &lista, int pos){
	if(pos > tamanho(lista) || pos < 0 || lista.primeiro == NULL){
		return false;
	} else if(pos == 0 && tamanho(lista) == 1){
		delete lista.primeiro;
		lista.primeiro = NULL;
	} else {
		TElemento<type>* nav = lista.primeiro;
		TElemento<type>* navAnt = nav;
		int contador = 0;
		while(contador < pos){
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
bool estaContido(TListaEnc<type> &lista, type elemento){
	TElemento<type>* nav = lista.primeiro;
	while(nav != NULL){
		if(nav->conteudo == elemento){
			return true;
		}
		nav = nav->proximo;
	}
	return false;
}

template<class type>
int procurar(TListaEnc<type> &lista, type elemento){
	TElemento<type>* nav = lista.primeiro;
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
TElemento<type>* retornaElemento(TListaEnc<type> &lista, int pos){
	if(pos < 0 || pos >= tamanho(lista)){
		return nullptr;
	} else {
		TElemento<type>* nav = lista.primeiro;
		int contador = 0;
		while(contador < pos){
			nav = nav->proximo;
			contador++;
		}
		return nav;
	}
}

template<class type>
void printLista(TListaEnc<type> &lista){
	if(lista.primeiro == NULL){
		std::cout << "Lista vazia.\n";
		return;
	}
	TElemento<type>* nav = lista.primeiro;
	int index = 0;
	while(nav->proximo != NULL){
		std::cout << "Elemento " << index << ": &TElemento: " << nav << ", TElemento->conteudo: " << nav->conteudo << ", TElemento->proximo: " << nav->proximo << ";\n";
		nav = nav->proximo;
		index++;
	}
	std::cout << "Elemento " << index << ": &TElemento: " << nav << ", TElemento->conteudo: " << nav->conteudo << ", TElemento->proximo: " << nav->proximo << ";\n";

	nav = lista.primeiro;
	while(nav->proximo != NULL){
		std::cout << nav->conteudo << ", ";
		nav = nav->proximo;
	}
	std::cout << nav->conteudo << ".\n";
}

#endif