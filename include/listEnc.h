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
void inicializaLista(TListaEnc<type> &lista){
	lista.primeiro = NULL;
}

template<class type>
int retornaTamanho(TListaEnc<type> &lista){
	int contador = 0;
	TElemento<type>* nav = lista.primeiro;
	if(nav == NULL){
		return contador;
	} else {
		while(nav->proximo != NULL){
			nav = nav->proximo;
			contador++;
		}
	}
	return contador;
}

template<class type>
TElemento<type>* criaElemento(type conteudo, TElemento<type>* ponteiroApos = NULL){
	TElemento<type>* elemento = new TElemento<type>;
	elemento->conteudo = conteudo;
	elemento->proximo = ponteiroApos;
	return elemento;
}

template<class type>
void insereElementoFinal(TListaEnc<type> &lista, type conteudo){
	if(lista.primeiro == NULL){
		lista.primeiro = criaElemento(conteudo);
	} else {
		TElemento<type>* nav = lista.primeiro;
		while(nav->proximo != NULL){
			nav = nav->proximo;
		}
		nav->proximo = criaElemento(conteudo);
	}
}

template<class type>
void insereElementoComeco(TListaEnc<type> &lista, type conteudo){
	if(lista.primeiro == NULL){
		lista.primeiro = criaElemento(lista, conteudo);
	} else {
		TElemento<type>* nav = lista.primeiro;
		lista.primeiro = criaElemento(lista, conteudo, nav);
	}
}

template<class type>
bool insereElementoPos(TListaEnc<type> &lista, type conteudo, int pos){
    if(pos == 0){
        insereListaInicio(lista, conteudo);
		return true;
    }else{
        TElemento<type>* novo = criaElemento(conteudo);
        TElemento<type>* nav = lista.inicio;
		int contador = 0;
        while(contador < pos - 1 && nav != NULL){
            nav = nav->proximo;
            contador++;
        }
        if(nav != NULL){
            novo->proximo = nav->proximo;
            nav->proximo = novo;
			return true;
        }else{
            std::cerr << "Posição passada maior que o tamanho da lista";
			return false;
        }

    }
}

template<class type>
bool removeElementoFinal(TListaEnc<type> &lista){
	if(lista.primeiro == NULL){
		return false;
	} else if(lista.primeiro->proximo == NULL){
		delete lista.primeiro;
		lista.primeiro = NULL;
		return true;
	}
	TElemento<type>* nav = lista.primeiro->proximo;
	TElemento<type>* navPrev = lista.primeiro;
	while(nav->proximo != NULL){
		navPrev = nav;
		nav = navPrev->proximo;
	}
	navPrev->proximo = NULL;
	delete nav;
	return true;
}

template<class type>
bool removeElementoComeco(TListaEnc<type> &lista){
	if(lista.primeiro == NULL){
		std::cerr << "Nao foi possivel deletar, a lista esta vazia.";
		return false;
	} else if(retornaTamanho(lista) == 1){
		delete lista.primeiro;
		lista.primeiro = NULL;
		return true;
	} else {
		TElemento<type>* segundo = lista.primeiro->proximo;
		delete lista.primeiro;
		lista.primeiro = segundo;
		return true;
	}
}

template<class type>
bool removeElementoPos(TListaEnc<type> &lista, int pos){
	if(pos > retornaTamanho(lista) || pos < 0 || lista.primeiro == NULL){
		return false;
	} else if(pos == 0 && retornaTamanho(lista) == 1){
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
bool verificaExistencia(TListaEnc<type> &lista, type elemento){
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
int retornaPosicao(TListaEnc<type> &lista, type elemento){
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
	if(pos < 0 || pos > retornaTamanho(lista)){
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
void imprimeLista(TListaEnc<type> &lista){
	if(lista.primeiro == NULL){
		std::cout << "Lista vazia.\n";
		return;
	}
	TElemento<type>* nav = lista.primeiro;
	int contador = 0;
	while(nav != NULL){
		std::cout << "Elemento " << contador << ": &TElemento: " << nav << ", TElemento->conteudo: " << nav->conteudo << ", TElemento->proximo: " << nav->proximo << ";\n";
		nav = nav->proximo;
		contador++;
	}
}
#endif