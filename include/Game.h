#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Item.h"
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

    /// @brief Constrói o texto do primeiro nível dos heróis
    void heroFirstLevel();

    /// @brief Indica o lvl dos heróis na frente do nome
    void heroLevel(Hero &hero, int hero_type);

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

    /// @brief testa se há um item não vazio na coordenada dos parâmetros e, se sim, ajusta as proporções
    /// do sprite do item e o desenha tile
    void putItemInBoard(int position_y, int position_x, Item &item, sf::RectangleShape &tileShape);

    /// @brief Muda o tamanho das barras de vida dos heróis
    void set_hero_health_bars(int damaged_hero, float full_hp, float current_hp);

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

    /// @brief Diminui o cooldown da habilidade dos heróis
    void heroSkillCooldownDecreases(Hero &hero);

    /// @brief decide a movimentação em uma direção específica, função auxiliar a monsterTakeAction
    /// @param enemy_number número do inimigo que vai se movimentar
    /// @param distance_ distância do inimigo ao herói mais próximo em uma direção específica
    /// @param recursion a função poderá ser recursiva somente se recursion for true
    void monsterMove(int enemy_number, int distance_x, int distance_y, int pos_x, int pos_y, std::string direction, bool rescursion);

    /// @brief Determina a ação de cada monstro 
    /// @param number_of_monsters: numero de monstros que serão movimentados
    /// @param delta_time: Tempo decorrido desde o ultimo clock 
    /// @param clock: Um argumento do tipo sf::Clock para atualizar o delta time 
    void monsterTakeAction(int number_of_monsters, float delta_time, sf::Clock clock);
 
    /// @return Retorna se a habilidade do herói atual está em cooldown
    bool isSkillOnCooldown();

    bool isNextSkillOnCooldown();

    /// @brief Escreve que a habilidade está em cooldown
    void writeCooldown(int is_on_cooldown);

    /// @brief Constrói as barras de vida dos monstros
    void initMonstersHealthBars();

    /// @brief Muda o tamanho das barras de vida dos monstros
    void setMonstersHealthBars(int damaged_monster, float full_hp, float current_hp);

    void gameOverRender();
    
    void playerWinRender();

    void gameOverCloseWindow(float delta_time, sf::Clock clock);
    
    /// @brief aplica efeito do item no herói
    /// PRECONDIÇÃO: herói se movimentou para a coordenada de um item que não foi usado
    void applyItemEffect(int pos_x, int pos_y, Hero& hero);

    void paleyrWinCloseWindow(float delta_time, sf::Clock clock);

  private:
    //Variables
    sf::RenderWindow *game_window_;
    sf::Event SFML_event_;

    sf::Texture background_;
    sf::Sprite background_sprite_;

    Board *game_board_;
    GameState *current_game_state_;

    //Nomes e barras de vida dos heróis
    sf::Font font_;
    std::vector<sf::Text> heros_;
    std::vector<sf::Vector2f> hero_names_position_;
    std::vector<std::string> hero_names_;

    std::vector<sf::RectangleShape> health_bars_;
    std::vector<sf::Vector2f> health_bars_position_;

    std::vector<sf::Text> hero_lvl_;
    std::vector<sf::Vector2f> hero_lvl_position_;
    std::vector<std::string> hero_lvl_printed_;
    int init_hero_lvl_;

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

    sf::Text skill_on_cooldown_;

    //Barras de vida dos monstros
    sf::Text monsters_;
    std::vector<sf::RectangleShape> background_monsters_health_bars_;
    std::vector<sf::RectangleShape> monsters_health_bars_;
    std::vector<sf::Vector2f> monsters_health_bars_position_;

    //Barra de vida do boss
    sf::Text boss_;
    sf::RectangleShape background_boss_health_bar_;
    sf::RectangleShape boss_health_bar_;

    //Personagens dos jogadores:
    Hero mage_;
    Hero knight_;
    Hero rogue_;

    Enemies my_hordes_;
    std::vector<std::unique_ptr<Item>> items_;

    /// @brief Cria um novo objeto do tipo RenderWindow
    void initWindow();
};

#endif // GAME_H_