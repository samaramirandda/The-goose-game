/**
 *
 * * No arranque, o programa deve perguntar se o utilizador pretende jogar ou administrar
 * * o jogo. Se pretender administrar deve pedir uma identificação (user e password). Se
 * * pretender jogar, deve perguntar quantos jogadores vão jogar (mínimo 1 e máximo 4)
 * * e,  em  seguida  deve  pedir  a  identificação (user e  password)  de cada  um. Se  um  user
 * * não existir deve ser acrescentado. As identificações dos jogadores devem ser
 * * guardadas  em  ficheiro.  Sobre  cada  jogador,  além  do  user  e  password,  deve  ser
 * * guardado nome, idade atual, a nacionalidade, a data do último jogo.
 *
 * ! 2. Para o administrador o programa deve:
 * ? o  Permitir  gerir  o  tabuleiro  –  deve  permitir  criar  e alterar  os  vários  tipos  de
 * ? tabuleiro e respetivas ações a tomar em cada casa.
 * * o Permitir  gerir  as  perguntas  do  jogo-  deve  permitir  criar,  alterar  e  eliminar
 * * permutas.  As  perguntas  do  jogo  devem  ser  mantidas  numa  lista  ligada  e
 * * devem ser guardadas em ficheiro binário.
 *
 * ! 3. Para jogar: o programa, depois de receber a identificação dos jogadores e a
 * ? identificação do tipo de tabuleiro (S/M/L) com que pretendem jogar, deve:
 * ? o Mostrar informação sobre os jogadores em jogo (nome do jogador, casa onde
 * ? se  encontra  cada  um,  e  número  de  perguntas  que  respondeu  até  agora).  Os
 * ? jogadores jogam pela ordem pela qual fizeram login.
 * ? o Apresentar  o  nome  do  jogador  que  deve  responder  à  próxima  pergunta  e  o
 * ? número da casa onde este se encontra.
 * ? o Apresenta a pergunta e respetivas opções de resposta (caso existam). Espera
 * ? pela resposta do jogador.
 * ? o Após receber a resposta, o programa deve informar se a resposta está correta,
 * ? ou não, e qual a consequência (avanço ou recuo).
 * ? o Um  jogador  mantém-se  em  jogo  até  responder  erradamente  a  uma  pergunta
 * ? ou  até  terminar  o  jogo.  Quando  responde  erradamente  o  jogo  passa  para  o
 * ? jogador seguinte.
 *
 * ! 4. Ganha o jogo, o jogador que no chegar primeiro ao final do jogo.
 *
 * * 5. O  programa  deverá  guardar  em  ficheiro  a  informação  sobre  os  jogadores  (máximo
100)
 *
 * ! 6. O programa deverá guardar em ficheiro a informação sobre os últimos 30 jogos.
 *
 * * 7. O programa deverá dar a possibilidade de listar os jogadores por ordem alfabética do [- 1/2 | Falta fazer a parte de dentro do jogo -] nome.
 *
 * * 8. O programa deverá dar a possibilidade de listar os jogadores por ordem  decrescente [- 1/2 | Falta fazer a parte de dentro do jogo -] da idade.
 *
 * ! 9. O  programa  deverá  dar  a  possibilidade  de  listar  a  informação  sobre  os  jogos  por ordem decrescente da data do jogo.
 *
 * * 10.  O jogo deve evitar apresentar as mesmas perguntas sempre que um jogo se inicia.
 *
*/