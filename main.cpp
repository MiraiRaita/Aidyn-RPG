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
        //Shows Name
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
        //Shows Health
        int getHealth(){
            return health; 
        }

        int getStrength(){
            return strength; 
        }

        bool spendCredits(int amount){
            if (credits > amount && amount > 0){
                credits -= amount;
                return true;
            }
            else{
                return false;
            }

        }

        bool increaseStrength(int points){
            if(points > 0 && strength + points <= 20){
                strength += points;
                return true;
            }
            else{
                return false;
            }
        }


};

int main(){
    Player player;
    std::string playerName;
    std::cout << "Hi fellow player... What's your name. \n";
    std::cout << "Enter a name:";
    getline(std::cin, playerName);
    std::cout << "Welcome, " << playerName << "!" << std::endl;
    

}