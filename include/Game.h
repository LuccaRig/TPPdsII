#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Board.h"
#include "Hero.h"
#include "GameState.h"
#include "Enemies.h"
#include "Skill.h"

class Game {

  public:
    
    /// @brief Constructor
    Game();

    /// @brief Destructor
    virtual ~Game();

    //Methods

    /// @brief Enquanto houver eventos ocorrendo na janela
    /// testa se um dos eventos é do tipo Closed(Apertar no x da janela)
    void testIsClosed();

    /// @brief Constrói os nomes e as barras de vida dos heróis
    void herosNameInicialization();

    /// @brief Atualiza a janela para cada evento que deve ocorrer
    void update();

    /// @brief Limpa a tela que foi renderizada e em seguida renderiza novas imagens
    /// @param delta_time = tempo decorrido desde o ultimo clock/renderização
    void render(float delta_time);

    /// @brief Essa função garante que enquanto o jogo estiver aberto ele continue
    /// funcionando como deveria
    void run(sf::Clock clock);

    void putHeroInBoard(int position_y, int position_x, Hero &hero, float delta_time,sf::RectangleShape &tileShape);

    void putMonsterInBoard(int position_y, int position_x, Monster &monster, float delta_time,sf::RectangleShape &tileShape);

    void putItemInBoard(int position_y, int position_x, Item &item, float delta_time,sf::RectangleShape &tileShape);

    /// @brief Muda o tamanho das barras de vida dos heróis
    void set_hero_health_bars(int damaged_hero, int full_hp, int current_hp);

    /// @brief Renderiza o tabuleiro com os personagens nele
    /// @param delta_time = tempo decorrido desde o ultimo clock/renderização
    void boardRender(float delta_time);

    /// @brief Constrói o menu das opções do turno dos heróis
    void setHeroMenu();

    /// @brief Constrói o texto que diz de qual herói é o turno
    void heroNameTurn(std::string hero_type);

    /// @brief Constrói o texto que alerta que o enter já foi pressionado
    /// @param enter_is_pressed 
    void chooseDirection(int enter_is_pressed);

    /// @brief Determina qual ação foi escolhida para o herói
    /// @param delta_time: Tempo decorrido desde o ultimo clock 
    /// @param clock: Um argumento do tipo sf::Clock para atualizar o delta time 
    void loopHeroMenu(float delta_time, sf::Clock clock);

    /// @brief Garante o cotrole dos herois pelo jogador durante seu turno
    /// @param delta_time: Tempo decorrido desde o ultimo clock 
    /// @param clock: Um argumento do tipo sf::Clock para atualizar o delta time 
    void playerTurnControl(float delta_time, sf::Clock clock);

    /// @brief Movimenta os herois no tabuleiro
    /// @param hero: Heroi selecionado para andar no seu devido turno
    /// @param delta_time: Tempo decorrido desde o ultimo clock 
    /// @param clock: Um argumento do tipo sf::Clock para atualizar o delta time 
    void heroWalk(Hero &hero, float delta_time, sf::Clock clock);

    /// @brief Realiza a ação de ataque do heroi
    /// @param hero: Heroi selecionado para atacar no seu devido turno
    /// @param delta_time: Tempo decorrido desde o ultimo clock 
    /// @param clock: Um argumento do tipo sf::Clock para atualizar o delta time 
    void heroAttack(Hero &hero, float delta_time, sf::Clock clock);

    /// @brief Realiza a habilidade de um herói que aumenta o próprio status
    void heroUseBuffSkill(int hero_number, std::string hero_type, Hero &hero);

    /// @brief Realiza a habilidade de um herói que da dano aos monstros
    void heroUseDamageSkill(std::string hero_type, Hero &hero);

    /// @brief Determina a ação de cada monstro 
    /// @param monster: numero de monstros que serão movimentados
    /// @param delta_time: Tempo decorrido desde o ultimo clock 
    /// @param clock: Um argumento do tipo sf::Clock para atualizar o delta time 
    void monsterTakeAction(int number_of_monsters, float delta_time, sf::Clock clock);

    /// @brief Constrói as barras de vida dos monstros
    void initMonstersHealthBars();

    /// @brief Muda o tamanho das barras de vida dos monstros
    void setMonstersHealthBars(int damaged_monster, float full_hp, float current_hp);

    /// @brief função auxiliar a monsterTakeAction, 
    /// @param nearest_hero_number identifica qual herói será atacado
    /// @param monster_number identifica que monstro vai atacar
    void monsterMove(int nearest_hero_number, int monster_number);

    void gameOverRender();

    void gameOverCloseWindow(float delta_time, sf::Clock clock);

  private:
    //Variables
    sf::RenderWindow *game_window_;
    sf::Event SFML_event_;

    sf::Texture background_;
    sf::Sprite background_sprite_;

    sf::Font font_;
    std::vector<sf::Text> heros_;
    std::vector<sf::Vector2f> hero_names_position_;
    std::vector<std::string> hero_names_;

    std::vector<sf::RectangleShape> health_bars_;
    std::vector<sf::Vector2f> health_bars_position_;

    Board *game_board_;
    GameState *current_game_state_;

    //Menu de opções dos jogadores
    int hero_menu_position_, is_hero_turn;
    bool keyboard_pressed_hero_menu_, enter_pressed_hero_menu_;
    std::string selected_choice_;

    sf::RectangleShape background_hero_menu_;

    std::vector<sf::Text> hero_menu_texts_;
    std::vector<std::string> hero_menu_printed_texts_;
    std::vector<sf::Vector2f> hero_menu_texts_position_;
    std::vector<sf::Color> hero_menu_texts_color_;

    sf::Text which_hero_;
    sf::Text which_direction_;

    //Barras de vida dos monstros
    sf::Text monsters_;
    std::vector<sf::RectangleShape> background_monsters_health_bars_;
    std::vector<sf::RectangleShape> monsters_health_bars_;
    std::vector<sf::Vector2f> monsters_health_bars_position_;

    //Personagens dos jogadores:
    Hero mage_;
    Hero knight_;
    Hero rogue_;

    Enemies my_hordes_;

    /// @brief Cria um novo objeto do tipo RenderWindow
    void initWindow();
};

#endif // GAME_H_