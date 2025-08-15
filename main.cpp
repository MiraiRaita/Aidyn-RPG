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
        int credits = 30;
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
        int getCharisma(){
            return charisma; 
        }
        int getIntelligence(){
            return intelligence; 
        }
        int getDexterity(){
            return dexterity;
        }
        int getCredits(){
            return credits; 
        }

        bool spendCredits(int amount){
            if (credits >= amount && amount > 0){
                credits -= amount;
                return true;
            }
            else{
                return false;
            }

        }
        
        void earnCredits(int amount){
         if (amount > 0) credits += amount;
        }
        
        enum Stat {
            STRENGTH,
            CHARISMA,
            INTELLIGENCE,
            DEXTERITY
        };

        bool increaseStats(Stat statToIncrease, int points){
            if (points <= 0) return false;

            switch (statToIncrease)
            {
            case STRENGTH:
                if(strength + points <= 20){
                    strength += points;
                    return true;
                }
                return false;
                break;
            case CHARISMA:
                if(charisma + points <= 20){
                    charisma += points;
                    return true;
                }
                return false;
                break;
            case INTELLIGENCE:
                if(intelligence + points <= 20){
                    intelligence += points;
                    return true;
                }
                return false; 
                break;
            case DEXTERITY:
                if(dexterity + points <= 20){
                    dexterity += points;
                    return true;
                }
                return false;
                break; 
            default:
                break;
            }
        }

        void displayStatus(){
            std::cout<< "~~~~" << name << "~~~~"<< std::endl;
            std::cout << "Health: " << health << "/100" << std::endl;
            std::cout << "Strength: " << strength << std::endl;
            std::cout << "Charisma: " << charisma << std::endl;
            std::cout << "Intelligence: " << intelligence << std::endl;
            std::cout << "Dexterity: " << dexterity << std::endl;
            std::cout << "Credits: " << credits << std::endl;
        }

};

