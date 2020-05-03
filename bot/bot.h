/**
@file bot.h
*/

#ifndef BOT_H
#define BOT_H
/**
\brief Executa a jogada do bot. Efetua primeiro o que acontece se aplicarmos a estratégia da paridade.
Caso for aplicada e ganharmos o jogo então será essa a jogada escolhida. Caso contrário é executada a estratégia
floodfill. Tal estratégia não é tão complexa como a da paridade, por isso pode deixar pontas soltas , então
aplicamos uma nova jogada(baseada na paridade) após ter aplicada a floodfill. Se com essa nova jogada
for possível ganhar o jogo ou se a floodfill foi aplicada quando não havia hipóteses de chegar até a casa
da vitória (representado pelo falo {3,4}) então quer dizer que não devemos aplicar a floodfill, ou seja,
se tivéssemos aplicado iríamos ter perdido logo depois. Nesse caso aplicamos então a paridade.
@param e Apontador para o estado
*/

void jogar_bot(ESTADO * e);

#endif
