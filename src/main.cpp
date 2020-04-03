#include <iostream>
#include <string>
#include <time.h>
#include "listEnc.h"
#include "listDEnc.h"
#include "listCirc.h"
#include "tadEsp.h"
#include "delivery.h"

int main(){
    srand(time(NULL));
    //Declaração de variáveis, cardapio, lista de pedidos, entregadores, preços, etc...
    TListaEnc<Item> cardapio;
    inicializaLista(cardapio);
    preencheCardapio(cardapio);

    TListaDE<Pedido> pedidosPendentes;
    inicializaLista(pedidosPendentes);

    TListaDE<Pedido> pedidosConcluidos;
    inicializaLista(pedidosConcluidos);

    TListaC<Entregador> listaEntregadores;
    inicializaLista(listaEntregadores);
    preencheListaEntregadores(listaEntregadores, 5);
    imprimeLista(listaEntregadores);

    int numeroDeCozinheiros = 3;
    TElementoC<Entregador>* entregadorAtual = listaEntregadores.primeiro;

    /*
    * O período de atendimento do restaurante é 5 horas.
    */
    for(int tempoAtual = 0; tempoAtual < 300 || retornaTamanho(pedidosPendentes) > 0; tempoAtual++){
        std::string horario = retornaHorario(tempoAtual);
        std::cout << horario << "\n";

        decrementaTempoPedidos(pedidosPendentes, numeroDeCozinheiros);

        //A cada 2 minutos, uma nova compra é efetuada.
        if(tempoAtual % 2 == 0 && tempoAtual <= 300){
            criaPedido(cardapio, pedidosPendentes, horario);
        }

        entregaPedido(pedidosPendentes, pedidosConcluidos, listaEntregadores, entregadorAtual);
        contrataOuDemiteEntregador(listaEntregadores, entregadorAtual);
        decrementaTempoEntregadores(listaEntregadores);
        std::cout << "\n--------------------------------------------------------------\n";
    }
    std::cout << "\n\n\n";
    imprimeLista(listaEntregadores);
    imprimeLista(pedidosPendentes);
    //imprimeLista(pedidosConcluidos);
    fechaCaixa(pedidosConcluidos);
}

//Calculo de caixa, dupla verifiação, etc...