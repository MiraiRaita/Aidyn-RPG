// Including the requisite libraries
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

class Player{

    private:
        int health = 100;
        int strength = 12;
        int charisma = 4;
        int intelligence = 7;
        int dexterity = 11;
        int skillPoints = 30;
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
        
        enum Stat {
            STRENGTH,
            CHARISMA,
            INTELLIGENCE,
            DEXTERITY
        };

        //Shows Health
        int getHealth(){
            return health; 
        }
        int getStatValue(Stat stat) {
        switch (stat) {
            case STRENGTH:
                return strength;
            case CHARISMA:
                return charisma;
            case INTELLIGENCE:
                return intelligence;
            case DEXTERITY:
                return dexterity;
            default:
                return 0;  // Should never happen
        }
    }
        int getskillPoints(){
            return skillPoints; 
        }

        bool spendskillPoints(int amount){
            if (skillPoints >= amount && amount > 0){
                skillPoints -= amount;
                return true;
            }
            else{
                return false;
            }

        }
        
        void earnskillPoints(int amount){
         if (amount > 0) skillPoints += amount;
        }
        

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

        bool increaseStrength(int points){
            if(points > 0 && strength + points <= 20){
                strength += points;
                return true;
            }
            else{
                return false;
            }
        }

        bool increaseCharisma(int points){
            if(points > 0 && charisma + points <= 20){
                charisma += points;
                return true;
            }
            else{
                return false;
            }
        }

        bool increaseIntelligence(int points){
            if(points > 0 && intelligence + points <= 20){
                intelligence += points;
                return true;
            }
            else{
                return false;
            }
        }

        bool increaseDexterity(int points){
            if(points > 0 && dexterity + points <= 20){
                dexterity += points;
                return true;
            }
            else{
                return false;
            }
        }

        bool isAlive(){
            return health > 0;
        }

        void displayStatus(){
            std::cout<< "~~~~" << name << "~~~~"<< std::endl;
            std::cout << "Health: " << health << "/100" << std::endl;
            std::cout << "Strength: " << strength << std::endl;
            std::cout << "Charisma: " << charisma << std::endl;
            std::cout << "Intelligence: " << intelligence << std::endl;
            std::cout << "Dexterity: " << dexterity << std::endl;
            std::cout << "skillPoints: " << skillPoints << std::endl;
        }

};

//skillPoints Allocation System
void allocateInitialskillPoints(Player& player){
    std::cout << "\n=== CHARACTER CREATION ===" << std::endl;
    std::cout << "You have " << player.getskillPoints() << " skillPoints to spend on stats." << std::endl;
    std::cout << "Each stat point costs 3 skillPoints." << std::endl;

    bool allocating = true;
    while(allocating && player.getskillPoints() >= 3){
        player.displayStatus();
        std::cout << "\nWhich stat to increase?" << std::endl;
        std::cout << "1. Strength  2. Charisma  3. Intelligence  4. Dexterity  5. Done" << std::endl;

        int choice;
        std::cin >> choice;
        while (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(256, '\n'); // Discard the bad input
            std::cin >> choice; // Try again
        }
        
        if (choice >= 1 && choice <= 4) {
            if (player.spendskillPoints(3)) {
                Player::Stat stat = static_cast<Player::Stat>(choice - 1);
                if (player.increaseStats(stat, 1)) {
                    std::cout << "Stat increased!" << std::endl;
                } else {
                    std::cout << "Stat at maximum! Refunding skillPoints." << std::endl;
                    player.earnskillPoints(3);
                }
            }
        } else if (choice == 5) {
            allocating = false;
        }
    }
}

//CreateCharacter
void createCharacter(Player& player){
    std::cin.ignore();
    std::string name;
    std::cout<< "What's your name?";
    getline(std::cin, name);
    player.setName(name);

    allocateInitialskillPoints(player);    
    std::cout<< "Welcome," << name << "!" <<std::endl;
    player.displayStatus();
}

//Difficulties
enum DifficultyLevel {
    TRIVIAL = 5,
    EASY = 8,
    MODERATE = 12,
    HARD = 15,
    VERY_HARD = 18,
    NEARLY_IMPOSSIBLE = 25
}; 
//D20
bool skillCheck(Player& player,Player::Stat stat, DifficultyLevel difficulty){
    int roll = rand()% 20 + 1;
    int statValue = player.getStatValue(stat);
    return (roll + statValue) >= difficulty;
}   
//StatsTraining
bool trainStat(Player& player, std::string statName, int cost = 5) {
    if (!player.spendskillPoints(cost)) return false;
    
    if (statName == "strength") return player.increaseStrength(1);
    else if (statName == "charisma") return player.increaseCharisma(1);
    else if (statName == "intelligence") return player.increaseIntelligence(1);
    else if (statName == "dexterity") return player.increaseDexterity(1);
    
    return false;  // Invalid stat name
}



