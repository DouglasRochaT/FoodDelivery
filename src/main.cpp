#include <iostream>
#include <string>
#include <time.h>
#include "listEst.h"
#include "listDEnc.h"
#include "listCirc.h"
#include "tadEsp.h"
#include "delivery.h"

int main(){
    srand(time(NULL));
    //Declaração de variáveis, cardapio, lista de pedidos, entregadores, etc...
    //Cardápio
    TListaEst<Item, 12> cardapio;
    inicializaLista(cardapio);
    preencheCardapio(cardapio);
    imprimeLista(cardapio);

    //Pedidos Pendentes
    TListaDE<Pedido> pedidosPendentes;
    inicializaLista(pedidosPendentes);

    //Pedidos Concluídos
    TListaDE<Pedido> pedidosConcluidos;
    inicializaLista(pedidosConcluidos);

    //Entregadores
    TListaC<Entregador> listaEntregadores;
    inicializaLista(listaEntregadores);
    preencheListaEntregadores(listaEntregadores, 5);
    imprimeLista(listaEntregadores);

    int numeroDeCozinheiros = 3;
    TElementoC<Entregador>* entregadorAtual = listaEntregadores.primeiro;

    //O período de atendimento do restaurante é 5 horas (300 minutos),
    //Você pode fazer o fechamento do caixa após a conclusão/entrega de todos pedidos. 
    for(int tempoAtual = 0; tempoAtual < 300 || retornaTamanho(pedidosPendentes) > 0; tempoAtual++){
        const char* horario = &retornaHorario(tempoAtual)[0];
        std::cout << horario << "\n";

        //A cada 2 minutos, uma nova compra é efetuada,
        //Após o período de antendimento, nenhum pedido pode ser registrado no aplicativo.
        if(tempoAtual % 2 == 0 && tempoAtual <= 300){
            criaPedido(cardapio, pedidosPendentes, horario);
        }

        entregaPedido(pedidosPendentes, pedidosConcluidos, listaEntregadores, entregadorAtual);
        contrataOuDemiteEntregador(listaEntregadores, entregadorAtual);
        decrementaTempoPedidos(pedidosPendentes, numeroDeCozinheiros);
        decrementaTempoEntregadores(listaEntregadores);
        std::cout << "--------------------------------------------------------------\n";
    }
    std::cout << "\n";
    imprimeLista(listaEntregadores);
    imprimeLista(pedidosPendentes);
    imprimeLista(pedidosConcluidos);
    fechaCaixa(pedidosConcluidos);
}
