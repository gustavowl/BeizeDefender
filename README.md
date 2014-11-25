# README #

#### Nome e Matrícula ####
Gustavo Alvez Bezerra - 2014026460
Hiago Miguel da Silva Rodrigues - 2014000875
Raí Vitor Morais da Silva - 2014000900

#### Compilar ####
g++ -lallegro -lallegro_audio -lallegro_acodec -std=c++11 -g -O0 Victory.cpp Instrucoes.cpp  Waves.cpp BaseDefender.cpp GameOver.cpp TelaInicial.cpp  GameManager.cpp  GameObject.cpp Projetil.cpp Player.cpp Personagem.cpp Inimigo.cpp Horda.cpp Base.cpp Drop.cpp SpriteManip.cpp Creditos.cpp -o  BaseDefender  $(pkg-config --libs allegro-5.0 allegro_font-5.0 allegro_ttf-5.0 allegro_dialog-5.0 allegro_primitives-5.0 allegro_image-5.0 allegro_audio-5.0 allegro_acodec-5.0)

#### Como Executar o programa ####
./BaseDefender

#### Indicações de eventuais limitações ou incompletudes do programa ####
Na geração de inimigos, pode ser que sejam gerados dois inimigos se sobrepondo, e isso vai fazer com que eles não se movam devido ao algoritmo que impede movimentação de inimigos colidindo.
Quando os sprites vão para o canto superior da tela eles desaparecem