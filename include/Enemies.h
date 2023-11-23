#ifndef ENEMIES_H_
#define ENEMIES_H_

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Monster.h"


class Enemies{
  public:
    Enemies();

    ~Enemies();

    /// @brief Getter do numero da horda
    /// @return Retorna qual horda está agindo nesse momento
    int get_horde_number();

    /// @brief Aumenta o contador para a proxima horda ser gerada
    void hordePass();

    /// @brief Cria uma horda de inimigos dependendo do valor da horda atual
    void createHordeEnemies();
    
    /// @brief Modifica as posições de todos os mosntros para ficarem em suas posições
    /// iniciais
    void putAllMonsterInStartPosition();

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

  private:
    int horde_number_;
    int enemy_count_;
    std::vector<std::unique_ptr<Monster>> enemies_;
};


#endif //ENEMIES_H_