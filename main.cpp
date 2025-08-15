// Including the requisite libraries
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

class Player{

    private:
        int health = 100;
        int strength = 7;
        int charisma = 7;
        int intelligence = 7;
        int dexterity = 7;
        int credits = 20;
        std::string name;
    
    public:
        void setName(std::string playerName){
            name = playerName;
        }

        std::string getName(){
            return name;
        }

        void takeDamage(int damage){
            health -= damage;
            if (health < 0){
                health = 0;
            }
        }

        void heal (int hp){
            health += hp;
            const int maxHealth = 100;
            if (health > maxHealth){
                health = maxHealth;
            }
        }
};

