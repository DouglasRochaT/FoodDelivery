#ifndef LISTEST_H
#define LISTEST_H

#include <iostream>

template <class type, int n>
struct TListaEst {
	type list[n];
	int contador;
	int tamanho;
};

template <class type, int tamanho>
void inicializaLista(TListaEst<type, tamanho> &lista){
	lista.tamanho = tamanho;
	for(int i = 0; i < lista.tamanho; i++){
		lista.list[i] = NULL;
	}
	lista.contador = 0;
}

template<class type, int tamanho>
bool insereElementoFinal(TListaEst<type, tamanho> &lista, type item){
	if(lista.contador >= lista.tamanho){
		return false;
	} else {
		lista.list[lista.contador] = item;
		lista.contador++;
		return true;
	}
}

template <class type, int tamanho>
bool insereElementoPos(TListaEst<type, tamanho> &lista, type item, int pos){
	if(lista.contador < lista.tamanho && pos < lista.contador && pos >= 0){
		for(int i = lista.tamanho - 1; i > pos; i--){
			lista.list[i] = lista.list[i - 1];
		}
		lista.list[pos] = item;
		lista.contador++;
		return true;
	} else {
		return false;
	}
}

template <class type, int tamanho>
bool insereElementoComeco(TListaEst<type, tamanho> &lista, type item){
	return push_in_pos(lista, item, 0);
}

template <class type, int tamanho>
bool removeElementoFinal(TListaEst<type, tamanho> &lista){
	if(lista.list[lista.contador - 1] == NULL){
		return false;
	}
	lista.list[lista.contador - 1] = NULL;
	lista.contador--;
	return true;
}

template <class type, int tamanho>
bool removeElementoPos(TListaEst<type, tamanho> &lista, int pos){
	if(pos >= lista.tamanho || lista.list[pos] == NULL || pos > lista.contador){
		return false;
	} else {
		for(int i = 0; i < lista.contador; i++){
			if(i > pos && i > 0){
				lista.list[i - 1] = lista.list[i];
			}
		}
		if(lista.contador > 0){
			lista.list[lista.contador - 1] = NULL;
		}
		lista.contador--;
		return true;
	}
}

template<class type, int tamanho>
bool removeElementoComeco(TListaEst<type, tamanho> &lista){
	if(lista.list[0] == NULL){
		return false;
	} else {
		for(int i = 0; i < lista.contador; i++){
			lista.list[i] = lista.list[i + 1];
		}
		lista.list[lista.contador] = NULL;
		lista.contador--;
		return true;
	}
}

template <class type, int tamanho>
type retornaElemento(TListaEst<type, tamanho> &lista, int pos){
	for(int i = 0; i < lista.tamanho; i++){
		if(i == pos){
			return lista.list[i];
		}
	}
	return NULL;
}

template <class type, int tamanho>
bool verificaExistencia(TListaEst<type, tamanho> &lista, type item){
	for(int i = 0; i < lista.tamanho; i++){
		if(lista.list[i] == item){
			return true;
		}
	}
	return false;
}

template <typename type, int tamanho>
void imprimeLista(TListaEst<type, tamanho> lista){
	for(int i = 0; i < tamanho; i++){
		if(lista.list[i] != NULL){
			std::cout << lista.list[i] << ", ";
		}
	}
	std::cout << "contador: " << lista.contador << ".\n";
}

#endif