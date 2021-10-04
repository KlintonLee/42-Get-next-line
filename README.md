# Get Next Line
O get_next_line é uma função que irá ler uma quantidade de caracteres de um
arquivo, definido no `BUFFER_SIZE`, procurando por quebra de linha `\n` ou fim
do arquivo.

Caso não seja final de arquivo e não encontre a quebra de linha, faz a leitura
dos próximos `BUFFER_SIZE` caracteres. Novamente, procurando por quebra de linha
ou fim de arquivo.

Esse processo é iterativo, até que uma das duas ocorrências aconteça. Atingindo
a expectativa a função encerra a execução e retorna esse intervalo do texto.

## Funções externas permitidas
- read: recebe 3 parâmetros
  - fd (file descriptor) - quando um arquivo é aberto, ele gera um identificador
    abstrato. E a partir dele é possível acessar o arquivo para leitura no caso
	do método que estamos tratando (read);
  - *buf - região na memória que irá receber o conteúdo do arquivo até o tamanho
    passado como terceiro parâmetro;
  - size - quantos bytes serão lidos e armazenados no *buf;
  - `NOTA`: essa função retorna a quantidade de bytes lidos, se retornar
    negativo, significa que algo deu errado durante a leitura;
- malloc: reserva um espaço na memória heap do tamanho passado como parâmetro;
- free: desaloca o espaço que foi ocupado na memória heap;

## Variáveis estáticas
Elas são inicializadas uma única vez durante todo o ciclo de vida do seu
programa.
### Por que preciso dela?
A função get_next_line efetuará a leitura do conteúdo do arquivo, todavia, o
conteúdo seguinte ao encontrar a quebra de linha será perdido. Em resumo,
significa que ao chamar o get_next_line da próxima vez, todo conteúdo que já
estava alocado no *buffer após a quebra de linha será perdido.

Por exemplo:
```
Este e um texto
simples para exemplo
```
Se o meu buffer realizar a leitura de 20 caracteres, ele terá o seguinte:
- `Este e um texto\nsim\0`
Como o read entende até onde efetuou a leitura no arquivo, na próxima vez que
executar irá devolver
- `ples para exemplo\0`
e o conteúdo `sim` será perdido. Portanto, a variável estática não será zerada
quando a função get_next_line encerrar, e ao chamar a função da próxima vez, o
conteúdo continuará existindo de onde parou.
