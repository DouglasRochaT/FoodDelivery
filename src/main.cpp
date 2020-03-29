#include <iostream>
#include "listEnc.h"
#include "listDEnc.h"
#include "listCirc.h"
#include "tadEsp.h"

int main(){
    //Declaração de variáveis, cardapio, entregadores, preços, etc...
    TListaDE<Item> cardapio;
    inicializarLista(cardapio);
    preencheCardapio(cardapio);
    printLista(cardapio);

    for(int tempoAtual = 1; tempoAtual <= 300; tempoAtual++){ //O período de atendimento do restaurante é 5 horas. 
        std::cout << "Minuto Atual: " << tempoAtual << ".\n";

    }
}

//Calculo de caixa, dupla verifiação, etc...