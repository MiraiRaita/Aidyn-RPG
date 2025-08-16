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
        int skillPoints = 15;
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
                case CHARISMA:
                    if(charisma + points <= 20){
                        charisma += points;
                        return true;
                    }
                    return false;
                case INTELLIGENCE:
                    if(intelligence + points <= 20){
                        intelligence += points;
                        return true;
                    }
                    return false;
                case DEXTERITY:
                    if(dexterity + points <= 20){
                        dexterity += points;
                        return true;
                    }
                    return false; 
                default:
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
    std::cout<< "What's your name? ";
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
bool skillCheck(Player& player,Player::Stat stat, int difficulty){
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
//Press Enter to Continue
void pressEnterToContinue() {
    std::cout << "\n... (Press Enter to continue) ...\n";
    std::cin.ignore(10000, '\n'); // Clear any previous input
    std::cin.get(); // Wait for the user to press Enter
}

bool villageSquareCombat (Player& player, bool hasBackup, bool surprise ){
    std::cout << "~~~~~~~~Village Fight Scene~~~~~~~~"<< std::endl;
    std::cout << "The weak, old figure of your father, Kilian is lying on the floor."<<std::endl;

    if(surprise){
        std::cout<< "Your axe went flying towards his head, embedding itself deep in his skull." << std::endl;
        std::cout << "The man's corpse dropped dead beside Kilian with a thud."<< std::endl;
    }
    else{
        std::cout << "Four armed soldiers are standing in front of you- One armed with a spear and the rest on horseback." << std::endl;          
    }
    int enemiesLeft = surprise? 3:4; 
    int playerAdvantage = hasBackup? 2:0;
    
    while(enemiesLeft > 0 && player.getHealth() > 0){
        std::cout << "\n Enemies Remain:" << enemiesLeft << std::endl;
        std::cout << "Your health:" << player.getHealth() << "/100"<< std::endl;
        std::cout << "\nWhat's your next move?" << std::endl;
        std::cout << "1. Direct attack with axe" << std::endl;
        std::cout << "2. Use your surroundings (fallen spear, horses)" << std::endl;
        std::cout << "3. Attempt to intimidate remaining soldiers" << std::endl;
        std::cout << "Choice:" << std::endl;
    
        int choice;
        std::cin >> choice;
        while (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(256, '\n'); // Discard the bad input
            std::cin >> choice; // Try again
        }

        switch(choice){
            case 1:
                if (skillCheck(player, Player::STRENGTH, MODERATE - playerAdvantage )){
                    std::cout<< "You shifted your weight on your left foot and leapt at a horseman lopping his head off"<< std::endl;
                    enemiesLeft--;
                    player.earnskillPoints(3);
                    std::cout<< "You earned 3 skillpoints! You now have "<< player.getskillPoints() <<"skillpoints" <<std::endl;
                }
                else{
                    std::cout<< "You swung wide! The soldier counterattacked"<< std::endl;
                    player.takeDamage(15);
                    std:: cout << "You took 15 damage... Your current health is:"<< player.getHealth() <<" /100" << std::endl;
                }
                break;
            
            case 2:
                if (skillCheck(player, Player::INTELLIGENCE, HARD )){
                    std::cout<< "You grabbed the fallen spear and attacked the horse, ensuing a chaos among the soldiers!" <<std::endl;
                    enemiesLeft -= 2;
                    player.earnskillPoints(5);
                    std::cout<< "You earned 5 skillpoints! You now have "<< player.getskillPoints() <<"skillpoints" <<std::endl;
                }
                else{
                    player.takeDamage(20);
                    std::cout << "You took 20 damage!" << "Your current health is: " << player.getHealth() << "/100"<< std::endl;
                }
                break;
            case 3:
                if (skillCheck(player, Player::CHARISMA, VERY_HARD - playerAdvantage)){
                    std::cout << "You intimidated the remaining soldiers! They started fleeing the battlefield" << std::endl;
                    std::cout << "Your act of heroism has increased your popularity in the village" <<std ::endl;
                    enemiesLeft = 0;
                    player.earnskillPoints(10);
                    player.increaseCharisma(1);
                    std::cout<< "You earned 10 skillpoints! You now have "<< player.getskillPoints() <<"skillpoints" <<std::endl;
                    std::cout<< "Your charisma increased from the gain in popularity! You now have "<< player.getStatValue(Player::CHARISMA) <<"Charisma" <<std::endl;
                }
                else{
                    std::cout<< "The soldiers laughed at your poor act of intimidation"<< std::endl;
                    player.takeDamage(35);
                    std::cout << "You took 35 damage!" << "Your current health is: " << player.getHealth() << "/100"<< std::endl;
                }
                break;
    
            };
        if (enemiesLeft > 0) {
            std::cout << "The soldiers retaliate!" << std::endl;
            int damageDealt = enemiesLeft * 5; 
            player.takeDamage(damageDealt);
            std::cout << "You take " << damageDealt << " damage!" << std::endl;
        }                    
        if (player.getHealth() <= 0) {
            std::cout << "\nYou fall unconscious... GAME OVER" << std::endl;
            return false;
        }

        
    }
    std::cout << "\nVictory! The remaining soldier flees, shouting threats..." << std::endl;
    std::cout << "'This will not be overlooked! The whole village will suffer!'" << std::endl;
    return true;
}

bool chapterOne (Player& player){

    std::cout << "======= A Rebel's Reckoning ======="<< std::endl;
    std::cout << "In the village of Aldea, lived a farmer named Kilian Goodson. Kilian lived with his son, "<< player.getName() <<std::endl;
    
    std::cout << "Kilian owned a small plot where he farmed for a living. He was a well-respected man among the villagers." << std::endl;
    std::cout << "After being infected with the plague, he had become too frail to work in his field, so his son," << player.getName() << "took over the job. "<<std::endl;
    std::cout << "Under the raging sun, You are chopping wood for firewood. Glistening in sweat, you place the pieces of oak logs and split them in half with the help of your trusty iron axe. " << std::endl;
    pressEnterToContinue();
    std::cout << "\nBrother,"<< player.getName() <<"!" << "A boy comes running yelling your name." << std::endl;
    std::cout << "The landlord's men are beating Uncle Killian in the village square!" << std::endl;
    std::cout << "Your blood started boiling... What will you do?" << std::endl;
    std::cout << "1. Grab your axe and rush to help" << std::endl;
    std::cout << "2. Talk to the villagers and convince them to help" << std::endl;
    std::cout << "3. Unleash a sneak attack on them" << std::endl;
    pressEnterToContinue();
    std::cout << "\nChoice:" <<std::endl;

    int choice;
    std::cin >> choice;
    while (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(256, '\n'); // Discard the bad input
            std::cin >> choice; // Try again
    }

    switch(choice){
        case 1:
            std::cout << "You reach the village and attack the men head-on" << std::endl;
            return villageSquareCombat(player, false, false);
        case 2:
            std::cout << "\n You try to rally the other villagers" << std::endl;
            if (skillCheck(player, Player::CHARISMA, HARD)){
                std::cout<< "You managed to convince John the Tanner" <<std::endl;
                return villageSquareCombat(player, true, false);
            }
            else{
                std::cout << "\nThe villagers are too scared"<< std::endl;
                player.takeDamage(5);
                std::cout<< "\nAs father continues to get beaten, you took emotional damage of 5 HP."<< "\n Your current health is, " << player.getHealth()<< "/100" <<std::endl;
                return villageSquareCombat(player, false,false);
            }    
        case 3:
            std::cout<< "\nYou creep closer, staying hidden..." << std::endl;
            if(skillCheck(player,Player::DEXTERITY, MODERATE)){
                std::cout<< "You get close enough for a sneak attack!" << std::endl;
                return villageSquareCombat(player,false,true);
            }
            else{
                std::cout<< "You stepped on a branch... They found out!" <<std::endl;
                return villageSquareCombat(player,false,false);
            }
        default:
            std::cout<< "\n You hesitated too long... " << std::endl;
            player.takeDamage(10);
            std::cout<< "\nYou took 10 damage!" << "Your current health is: " << player.getHealth() << "/100"<< std::endl;    
            return villageSquareCombat(player,false, false);    
    }   

};

bool surrenderPath(Player& player){
    std::cout<< "You accept the consequences of your actions and surrender..." << std::endl;
    std::cout<< "ENDING: THE MARTYR - You sacrificed yourself to save the village..." << std::endl;
    return false;
};

bool rescueMissionPath(Player& player){
    std::cout << "\nWe will sneak into the watchtower and rescue Alicia! You declare..." << std::endl;
    if(skillCheck(player,Player::CHARISMA,MODERATE)){
        std::cout<< "Some villagers including John the Tanner, Jake the Fisherman and Derek the Blacksmith agreed to help" <<std::endl;
        std::cout << "CHAPTER 3: THE RESCUE begins..." << std::endl;
        return true;
    }
    else{
        std::cout<< "The villagers backed out leaving you alone..." << std::endl;
        std::cout<< "CHAPTER 3: THE LONE HERO (coming soon)" << std::endl;
        return false;
    }
};

bool rebellionPath(Player& player){
    std::cout << "\n WE'VE SUFFERED ENOUGH! It's time we fight back! You shout" << std::endl;
    if(skillCheck(player, Player::CHARISMA, VERY_HARD)){
        std::cout<< "Your words lit a fire of rebellion within everyone's heart" << std::endl;
        std::cout<< "CHAPTER 3: THE UPRISING begins..." <<std::endl;
        return true;
    }
    else{
        std::cout<< "The villagers are too scared of your ideas and decided to banish you..." <<std::endl;
        std::cout << "ENDING: THE EXILE- You were kicked out from Aldea" <<std::endl;
        return false;
    }
}

bool chapterTwo (Player& player){
    std::cout << "====== THE AFTERMATH ======" << std::endl;
    std::cout << "You sat beside the boiling pot of vegetable stew, gazing at the bubbling broth. The crackling of the fire and the warmth of the flame weren't enough to make him forget the blood-curdling screams of the men he slaughtered. He raised his palm before his face. The dried bloodstain still lingered after washing countless times. " <<std::endl;
    pressEnterToContinue();
    std::cout<< "You sighed and started pouring the piping-hot stew onto two wooden bowls. You passed the bowl with two pieces of bread to your father. Kilian was sitting near the window, wrapped in a tattered green blanket looking at the moon. After going through such traumatic events, Kilian's body had completely broken down. Now he sat quietly, feverish, gazing at the moonlit night sky."<< std::endl;
    pressEnterToContinue();
    std::cout<< "He slowly turned toward" << player.getName()<< "and reached his arms out to grab the bowl of stew and bread. 'Phew… phew…' Kilian blew on the hot stew to cool it down as he drenched the bread in the stew. He closed his eyes and bit the soggy bread." << std::endl;
    pressEnterToContinue();
    std::cout<< "The moment of silence was broken by a knock on the door" << std::endl;
    std::cout<< "You got up and opened the door and saw Douglas and Collins at the doorstep, followed by what seemed the whole village. You hesitantly welcome them in." << std::endl;
    pressEnterToContinue();
    std::cout << "Look at this! Yelled Douglas as he handed you a letter..." << std::endl;
    pressEnterToContinue();
    std::cout << "You read the letter: Webb Collins, we have abducted your daughter Alicia. If you want your daughter back, hand us "<< player.getName() << " Goodson by dawn, or else my men will do such things you cannot comprehend. We will be at the watchtower near the Black Forest. Chief of Lord Dunn's men, Simon Foreman "<< std::endl;
    pressEnterToContinue();
    std::cout << "The whole village seemed divided... What would you do now?" << std::endl;
    std::cout << "1. Surrender yourself to save Alicia" << std::endl;
    std::cout << "2. Propose a rescue mission" << std::endl;
    std::cout << "3. Convince the village to rebel against the oppression " << std::endl;
    std::cout << "4. Let the villagers decide" << std::endl;
    std::cout << "Choice:" << std::endl;

    int choice;
    std::cin >> choice;
    while (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(256, '\n'); // Discard the bad input
            std::cin >> choice; // Try again
    }

    switch(choice){
        case 1:
            return surrenderPath(player);
        case 2:
            return rescueMissionPath(player);
        case 3:
            return rebellionPath(player);
        default:
            std::cout << "You remain silent, letting others decide..." << std::endl;
            return surrenderPath(player);
    }
}

void runMainStory(Player& player){
    std::cout<< "For eternity, when evil arises, a saviour, a messiah arises to eradicate the evil. \nBut, in these dark ages, even the morally upright fear the wrath of the wicked." <<std::endl;
    pressEnterToContinue();
    std::cout<< "\nThe people of the Kingdom of Adonia pray to the gods for a hero, a saviour to save them from the tyranny of the Devil Emperor Adonis III.\nHe ruled with an iron fist, tolerating no criticism. The man — if you can call him one — waged a series of wars with his neighbouring kingdoms, leading to a ten-year-long war, which resulted in an Adonian victory. " << std::endl;
    pressEnterToContinue();
    std::cout<< "Following the gruelling war, he raised taxes to replenish his depleted treasury. \nHe established a system of landlords, who were tasked with supervising up to seven villages and collecting taxes from them." << std::endl;
    pressEnterToContinue();
    std::cout<< "The landlords, mostly low-ranking nobles, were shrewd and began setting their tax rate unbeknownst to the Devil Emperor, to earn a profit. " << std::endl;
    std::cout<< "\nAs a result of the deceit by the landlords, the poor peasants paid more taxes than they earned or harvested. \nTo pay their taxes, they often took loans from the landlords with exorbitantly high interest rates—dropping deeper into the rabbit hole of debt. " << std::endl;
    pressEnterToContinue();
    std::cout<< "One of the most notorious among the landlords was Dunn Johnson. He controlled five villages in the east, namely Aldea, Altdorf, Mlynitsa, Borovitsa and Dorfbach." << std::endl;
    std::cout << "\nAldea, being the largest and most populous of the five villages, became the center of his tyranny. " <<std::endl;

    chapterOne(player);

    if (player.isAlive()){
        chapterTwo(player);
    }
}
void startNewGame(){
    Player player;

    createCharacter(player);

    runMainStory(player);

}
void showMainMenu(){
    std::cout<< "==== A HALF-ASSED GAME ====" << std::endl;
    std::cout << "1. Start Game"<< std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Choice:" << std::endl;
}

int main(){
    srand(time(0));

    bool running = true;

    while(running){

        showMainMenu();
        int choice;
        std::cin >> choice;
        while (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(256, '\n'); // Discard the bad input
            std::cin >> choice; // Try again
        }

        switch(choice){
            case 1:
                startNewGame();
                break;
            case 2:
                std::cout << "Load game is not implemented yet..." << std::endl;
                break;
            case 3:
                std::cout << "Thanks for Playing!" <<std::endl;
                running = false;
                break;
            default:
                std::cout<< "Invalid choice" <<std::endl;   
        }

    }

    return 0;
}