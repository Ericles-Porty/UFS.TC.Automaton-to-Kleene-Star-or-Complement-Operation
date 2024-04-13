# Minerador-de-Automatos-jFlap
***
Projeto de teoria da computação ministrado pelo Prof Dr Alcides Benicasa

Desenvolvido pelo estudante Éricles Dos Santos C., do curso de Sistemas da Informação da Universidade Federal de Sergipe campus Itabaiana. 

## **Manual de uso**

1. Edite o arquivo "automato.jff" usando a ferramenta "jFlap.jar", ou copie um automato já criado e cole no mesmo diretorio onde está o executavel, deixe o nome do arquivo como "automato.jff".
2. Após ter criado ou modificado seu automato, abra o executavel chamado "run_minerador.bat".
3. Após abrir o programa você terá que fazer escolhas da opção 0 até a 6, onde:
   * Opção 0 encerra o código.
   * Opção 1 cria um novo arquivo .jff referente ao automato.jff mas realizando a operação de complemento.
   * Opção 2 cria um novo arquivo .jff referente ao automato.jff mas realizando a operação de estrela.
   * Opção 3 Apresenta dados do autômato original.
   * Opção 4 Abre o automato.jff dentro do jFlap automaticamente.
   * Opção 5 Abre o arquivo "automatoComplementado.jff" que recebeu a operação complemento dentro do jFlap automaticamente.
   * Opção 6 Abre o arquivo "automatoEstrelado.jff" que recebeu a operação estrela dentro do jFlap automaticamente.

### **Observações importantes**
* Os arquivos "automatoComplemento.jff" e "automatoEstrela.jff" só serão criados após selecionar a opção 1 e 2 respectivamente 
* Você não precisa selecionar a opção 1 ou a 2 mais de uma vez.
* Você só pode selecionar a opção 5 e 6 após realizar as operações da opção 1 e 2 respectivamente.
* Após selecionar a opção 5 ou 6 você não pode selecionar outra opção até fechar o arquivo jff e o programa jFlap.
* Caso você queira editar seu autômato, feche o executável, edite seu autômato e abra o executável novamente para ser atualizado.

### **Para compilar o código**
* Para compilar o código você deve ter o make instalado em sua máquina.
* Após ter o make instalado, abra o terminal e vá até o diretório onde está a raiz do projeto.
* Digite o comando `make` e pressione enter.
* Após compilar o código, para executar basta abrir o "run_minerador.bat".