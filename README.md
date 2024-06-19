# Flying-Company

## projeto

Uma companhia área deseja informatizar seu sistema de reserva de passagens, e você e sua equipe serão os encarregados do projeto e desenvolvimento. Para esta versão inicial a companhia espera um sistema simplificado, considerando uma única aeronave, que reserve apenas trecho de voo simples (único trecho) e para um único passageiro por vez, como especificado a seguir.

1. **Abertura de Voo:** prepara o sistema para a realização de reservas, efetuando, entre outras coisas, a coleta de informações sobre capacidade da aeronave e preços de classes de reserva. É realizada uma única vez, até o fechamento do voo, independente da quantidade de fechamentos de dia efetuadas
2. **Informações da reserva:** Nome, (último) Sobrenome, CPF, *data da viagem, número do voo (ID)*, número do assento, classe (econômica ou executiva), valor, *aeroporto origem e aeroporto destino*. Obs.1: os dados em itálico serão sempre os mesmos para todos os passageiros. Obs.2: os valores das classes econômica e executiva devem ser informados na abertura do voo.
3. **Capacidade da aeronave (qtd de assentos):** deve ser solicitada pelo sistema na abertura do voo, antes da venda da primeira passagem. Não deve ser requisitada em nenhuma outra oportunidade até o fechamento do voo.
4. **Opções do sistema:**
  a. Realizar reserva.
  b. Consultar reserva (por CPF). Exibe todas as informações da reserva.
  c. Modificar reserva (apenas nome, sobrenome, CPF e/ou assento podem ser modificados).
  d. Cancelar reserva (por CPF). Apaga do sistema todas as informações relativas à reserva do CPF indicado.
5. **Fechamento do voo:** Em caso de fechamento, o sistema deve exibir a lista de passageiros (Nome, Sobrenome, CPF, assento) e o valor total arrecadado com as reservas. Obs.: ao se atingir o limite de reservas possíveis (quantidade de assentos), o fechamento deve ser realizado automaticamente. Um voo fechado não aceita novas reservas ou alterações de qualquer natureza. Se o sistema acessar um voo fechado deve emitir o aviso “Voo Fechado!” e exibir as informações mencionadas no início deste item.
6. . **Fechamento do dia:** exibe a quantidade de reservas efetuadas, o valor total arrecadado até o momento com as reservas e encerra o programa de modo a garantir que mais reservas (e operações) possam ser realizadas no dia seguinte (se o voo não estiver fechado ainda). Pode ser efetuado várias vezes até o fechamento do voo.

## Comandos e Saídas

Assume-se que os comandos sempre serão apresentados de forma correta e que sempre serão fornecidos códigos e valores válidos, portanto não é necessário tratar esse tipo de erro. As funcionalidades do sistema devem ser requisitadas por meio de comandos seguidos dos dados necessários. Os comandos são representados por duas 
letras maiúsculas. Os comandos que o sistema deve reconhecer são especificados a seguir. O símbolo _ denota um espaço em branco.

- 'Abertura do voo': AV_<quantidade assentos>_<valor econômica>_<valor executiva>

Realizar reserva:
RR_<nome >_<sobrenome>_<CPF>_<data viagem>_<número do voo>_<assento>_<classe>_<valor>_<origem>_<destino>

**Consultar reserva**
CR_<CPF>

**Modificar reserva**
MR_<CPF consulta>_<nome>_<sobrenome>_<CPF>_<assento>

**Cancelar reserva**
CA_<CPF>

**Fechamento do dia**
FD

**Fechamento do voo**
FV

Quatro comandos exigem que informações sejam apresentadas na tela: **CR, MR, FV e FD**. As saídas para estes comandos devem ser apresentadas da seguinte maneira:

**CR**
<CPF>
<nome >_<sobrenome>
<data viagem>
Voo:_<número do voo>
Assento:_<assento>
Classe:_<classe>
Trecho:_<origem>_<destino>
Valor:_<valor>
--------------------------------------------------

**MR**
Reserva Modificada:
<CPF>
<nome >_<sobrenome>
<data viagem>
Voo:_<número do voo>
Assento:_<assento>
Classe:_<classe>
Trecho:_<origem>_<destino>
Valor:_<valor>
--------------------------------------------------

**FV**
Voo Fechado!
<CPF>
<nome>_<sobrenome>
<assento>
<CPF>
<nome>_<sobrenome>
<assento>
…
<CPF>
<nome>_<sobrenome>
<assento>
Valor Total:_<valor>
--------------------------------------------------

**FD**
Fechamento do dia:
Quantidade de reservas:_<quantidade>
Posição:_<valor total até o momento>
--------------------------------------------------

Note que cada saída deve ser finalizada com uma linha contendo 50 hífens.
