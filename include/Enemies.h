#ifndef ENEMIES_H_
#define ENEMIES_H_

#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>  
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Monster.h"
#include "Hero.h"
#include "Board.h"
#include "Item.h"


class Enemies{
  public:
    Enemies();

    ~Enemies();

    /// @brief Getter do numero da horda
    /// @return Retorna qual horda está agindo nesse momento
    int get_horde_number();

    /// @brief Aumenta o contador para a proxima horda ser gerada
    void hordePass();

    /// @brief Checa se todos os monstros de uma horda ja morreram
    bool allEnemiesAreDead();

    /// @brief Cria uma horda de inimigos dependendo do valor da horda atual
    void createHordeEnemies(std::vector<std::unique_ptr<Item>> &itens, Board* my_board, Hero &rogue, Hero &mage, Hero &knight);
    
    /// @brief Modifica as posições de todos os mosntros para ficarem em suas posições
    /// iniciais
    void setAllInStartPosition(std::vector<std::unique_ptr<Item>> &itens, Board* my_board, Hero &rogue, Hero &mage, Hero &knight);

    /// @brief Getter do numero de inimigos
    /// @return tamanho da horda atual 
    int hordeSize();

    /// @brief Acessa as informações de um inimigo especifico da horda
    /// @param enemy_number 
    /// @return Um ponteiro para um monstro específico e suas características
    Monster* enemy(int enemy_number);

    /// @brief Limpa o vetor de inimigos e todos os mosntros dentro dela
    /// para a criação de uma nova horda
    void deleteMonsterPool();

    /// @brief Compara se algum dos monstros possui a posição específicada e retorna um ponteiro para monstro
    /// @return Ponteiro para o  monstro na posição especificada
    /// @param position_x posição x para ser comparada
    /// @param position_y posição y para ser comparada
    Monster* getMonsterInPosition(int position_x, int position_y);

    bool bossIsAlive();

    std::pair<int, int> randomPositionSpawn(Board* my_board);

    void randomEyeSelect();

    void eyeSpawn(Board* my_board);

    void bossTurnIncrement();

  private:
    int horde_number_;
    int enemy_count_;
    std::vector<std::unique_ptr<Monster>> enemies_;
    int boss_turns_;
};


#endif //ENEMIES_H_