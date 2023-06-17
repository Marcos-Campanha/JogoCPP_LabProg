# JogoCPP_LabProg

## Criação dos Exércitos

Os soldados são criados a partir da leitura dos arquivos *data/army_bem.txt* e *data/army_mal.txt*, de acordo com o seguinte padrão:

**Nome da classe**/**Saúde**/**Poder**/**Quantidade**

> **Observação**: Os caminhos são relativos ao diretório JogoCPP_LabProg (No VisualStudio, por padrão, o caminho é relativo ao arquivo de solução .sln).
> Para evitar problemas relacionados à leitura do arquivo, basta configurar o caminho da solução na IDE ou alterar o caminho na função main(), em *src/main.cpp*

> std::vector<SoldadoBem*> armyBem = builder.buildArmyBem("data/army_bem.txt", printer);
> std::vector<SoldadoMal*> armyMal = builder.buildArmyMal("data/army_mal.txt", printer);

## Tipos de classes (Bem x Mal)

As classes do bem são: ***Elfo***, ***Anão***, ***Humano***, ***Mago*** e ***Druida***

As classes do mal são: ***Sauron***, ***Orc***, ***Jester*** e ***BloodMagician***
