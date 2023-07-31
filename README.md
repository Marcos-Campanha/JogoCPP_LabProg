# Trabalho LOTR em C++, LabProg

> ### Aluno Marcos Paulo de Souza Campanha

## Criação dos Exércitos

Os soldados são criados a partir da leitura dos arquivos *data/army_bem.txt* e *data/army_mal.txt*, seguindo o seguinte padrão:

### **Nome da classe/Saúde/Poder/Quantidade**

- Exemplo: **Sauron/100/10/2** cria 2 Saurons com 100 de vida e 10 de poder cada

> **Observação**: Os caminhos de leitura desses arquivos são relativos ao próprio diretório JogoCPP_LabProg (No VisualStudio, por padrão, o caminho é relativo ao arquivo de solução .sln).
> Para evitar problemas relacionados à leitura do arquivo, basta configurar o caminho na IDE ou alterar o caminho na função main(), em *src/main.cpp*

> std::vector<SoldadoBem*> armyBem = builder.buildArmyBem("data/army_bem.txt", printer);
> 
> std::vector<SoldadoMal*> armyMal = builder.buildArmyMal("data/army_mal.txt", printer);

## Tipos de classes (Bem x Mal)

As classes do bem são: ***Elfo***, ***Anão***, ***Humano***, ***Mago*** e ***Druid***

As classes do mal são: ***Sauron***, ***Orc***, ***Jester*** e ***BloodMagician***

## Batalha entre exércitos

Antes de cada luta, os estados de cada exército (soldados vivos, saúde e poder) são apresentados na tela e é anunciado um confronto entre um soldado do bem e um soldado do mal.

Após o fim desse confronto, anuncia-se um novo, priorizando os soldados que ainda não lutaram, até que um dos exércitos seja completamente eliminado.

As batalhas ocorrem por turnos, e a ação realizada em cada turno também é mostrada na tela.

> Todas as ações e informações do confronto são guardadas no arquivo *data/battle_log.txt*
