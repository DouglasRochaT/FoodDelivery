#include <iostream>
#include "listEnc.h"
#include "listDEnc.h"
#include "listCirc.h"
#include "tadEsp.h"

int main(){
    //Declaração de variáveis, cardapio, lista de pedidos, entregadores, preços, etc...
    TListaEnc<Item> cardapio;
    inicializarLista(cardapio);
    preencheCardapio(cardapio);
    imprimeLista(cardapio);

    TListaDE<Pedido> listaPedidos;
    inicializarLista(listaPedidos);
    imprimeLista(listaPedidos);

    for(int tempoAtual = 1; tempoAtual <= 300; tempoAtual++){ //O período de atendimento do restaurante é 5 horas. 
        std::cout << "Minuto Atual: " << tempoAtual << ".\n";
        if(tempoAtual %2 == 0){ //A cada 2 minutos, uma nova compra é efetuada.
            criaPedido(cardapio, listaPedidos);
        }
    }
}

//Calculo de caixa, dupla verifiação, etc...