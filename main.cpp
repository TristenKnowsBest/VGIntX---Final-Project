#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int POTION_HEALTH = 60;
const int MAX_HEALTH = 100;

int maleStats = 1;

class Item{
private:
    string name;
    int price;
    int defense;
    int attack;
public:
    void setAttack(int newAttack){
        attack = newAttack;
    }
    
    int getAttack(){
        return attack;
    }
    
    void setDefense(int newDefense){
        defense = newDefense;
    }
    
    int getDefense(){
        return defense;
    }
    
    void setName(string newName){
        name = newName;
    }
    
    string getName(){
        return name;
    }
    
    void setPrice(int newPrice){
        price = newPrice;
    }
    
    int getPrice(){
        return price;
    }
        
};

class Actor{
private:
    string name;
    int health;
    int damage;
    int armour;
public:
    void setArmour(int newArmour){
        armour = newArmour;
    }
    
    int getArmour(){
        return armour;
    }
    
    void setName (string newName){
        name = newName;
    }
    
    string getName(){
        return name;
    }
    
    void setDamage(int setDamage){
        damage = setDamage;
    }
    
    int getDamage(){
        return damage;
    }
    
    void doHeal(int health, int maxHealth){
        
        health = health + POTION_HEALTH;
        
        if(health + POTION_HEALTH > maxHealth){
            health = maxHealth;
        }
    }
    
    void setHealth(int newHealth){
        health = newHealth;
    }
    
    int getHealth(){
        return health;
    }
    
    void healthDamage(int doDamage){
        health = health - doDamage;
        
        if(health < 0){
            health = 0;
        }
    }
    
};

class Player : public Actor {
public:
    bool death(bool battle) {
        return false;
    }
};

class Enemy : public Actor {
private:
    int gold;
public:
    bool death(bool battle) {
        return false;
    }
    void setGold(int newGold){
        gold = newGold;
    }
    int getGold(){
        return gold;
    }
};



string validChoice(string choice, string option1, string option2);
int options(int damage, Player& player);
int useInventory(Player& player);
float damageRand(float);
void displayPlayerInventory();
void displayMerchantInventory();
void lineBreak();
int engageBattle(Player& player, Enemy enemy, int gold);
bool equipTest(string choice);
int checkInventory(Player& player);
void pitStop(Player& player);

vector<Item> merchantInventory;
vector<Item> playerInventory;

int main() {
    srand ((unsigned int) time(0));
    
    cout << "welcome to \"rpg\"" << endl;
    cout << "would you like to play?" << endl <<  "\"yes\" to play, anything else to quit." << endl;
    string testPlay;
    cin >> testPlay;
    
    if(testPlay != "yes"){
        return 0;
    }
    
    unsigned potionLimit = 3;
    unsigned potions = 0;
    
    cout << "All customizations impact your story." << endl;
    cout << "Customization options: " << endl;
    cout << "Male or Female? (f or m)" << endl;
    string maleFemale;
    cin >> maleFemale; cout << endl;
    maleFemale = validChoice(maleFemale, "f", "m");
    cout << "Wizard or Warrior? (wiz or war)" << endl;
    string wizWar;
    cin >> wizWar; cout << endl;
    wizWar = validChoice(wizWar, "wiz", "war");
    cout << "Human or Elf? (h or e)" << endl;
    string humanElf;
    cin >> humanElf; cout << endl;
    humanElf = validChoice(humanElf, "h", "e");
    if(maleFemale == "f"){
        maleFemale = "female";
    }else if(maleFemale == "m"){
        maleFemale = "male";
    }
    if(wizWar == "wiz"){
        wizWar = "wizard";
    }else if(wizWar == "war"){
        wizWar = "warrior";
    }
    if(humanElf == "h"){
        humanElf = "human";
    }else if(humanElf == "e"){
        humanElf = "elf";
    }
    cout << "you have chosen a " << maleFemale << " " << wizWar << " that is a(n) " << humanElf << "." << endl;
    
    
    int gender = 1;
    if(maleFemale == "female"){
        gender = 2;
    }else if(maleFemale == "male"){
        maleStats = 1.25;
    }
    int elfBonus = 0;
    int humanBonus = 0;
    if(humanElf == "elf"){
        elfBonus = 5;
    }else if(humanElf == "human"){
        humanBonus = 3;
    }
    
    
    Player player;
    player.setHealth(100);
    player.setName("Player");
    player.setDamage(10 + elfBonus);
    player.setArmour(0 + humanBonus);
    
    Enemy bandit;
    bandit.setHealth(50);
    bandit.setName("bandit");
    bandit.setDamage(5);
    bandit.setGold(50);
    
    Enemy ogre;
    ogre.setHealth(75);
    ogre.setName("ogre");
    ogre.setDamage(10);
    ogre.setGold(100);
    
    Enemy skeleton;
    skeleton.setHealth(100);
    skeleton.setName("skeleton");
    skeleton.setDamage(15);
    skeleton.setGold(150);
    
    Enemy trollKing;
    trollKing.setHealth(250);
    trollKing.setName("troll king");
    trollKing.setDamage(25);
    trollKing.setGold(300);
    
    int gold = 100;
    Item potn;
    potn.setName("potion");
    potn.setPrice(50);
    
    if(wizWar == "warrior"){
        Item swrd;
        swrd.setName("iron_sword");
        swrd.setPrice(75);
        swrd.setDefense(0);
        swrd.setAttack(20);
        Item shld;
        shld.setName("wood_shield");
        shld.setPrice(50);
        shld.setDefense(1);
        shld.setAttack(0);
        Item armr;
        armr.setName("iron_chestplate");
        armr.setPrice(100);
        armr.setDefense(2);
        armr.setAttack(0);
        playerInventory.push_back(swrd);
        playerInventory.push_back(shld);
        playerInventory.push_back(armr);
        playerInventory.push_back(potn);
    }else if(wizWar == "wizard"){
        Item stff;
        stff.setName("oak_staff");
        stff.setPrice(75);
        stff.setDefense(0);
        stff.setAttack(20);
        Item robe;
        robe.setName("robe");
        robe.setPrice(100);
        robe.setDefense(1);
        robe.setAttack(0);
        Item crys;
        crys.setName("crystal_ball");
        crys.setPrice(50);
        crys.setDefense(1);
        crys.setAttack(5);
        playerInventory.push_back(stff);
        playerInventory.push_back(crys);
        playerInventory.push_back(robe);
        playerInventory.push_back(potn);
    }
    
    if(wizWar == "warrior"){
        Item Mswrd;
        Mswrd.setName("mithril_sword");
        Mswrd.setPrice((250 / gender));
        Mswrd.setDefense(0);
        Mswrd.setAttack(50);
        Item Mshld;
        Mshld.setName("iron_kite_shield");
        Mshld.setPrice((200 / gender));
        Mshld.setDefense(5);
        Mshld.setAttack(0);
        Item Marmr;
        Marmr.setName("mithril_chestplate");
        Marmr.setPrice((300 / gender));
        Marmr.setAttack(0);
        Marmr.setDefense(7);
        Item Mpotn;
        Mpotn.setName("potion");
        Mpotn.setPrice(50 / gender);
        merchantInventory.push_back(Mswrd);
        merchantInventory.push_back(Mshld);
        merchantInventory.push_back(Marmr);
        merchantInventory.push_back(Mpotn);
    }else if(wizWar == "wizard"){
        Item Mstff;
        Mstff.setName("ancient_enchanted_staff");
        Mstff.setPrice(250);
        Mstff.setDefense(0);
        Mstff.setAttack(50);
        Item Mcrys;
        Mcrys.setName("time_etched_orb");
        Mcrys.setPrice(200);
        Mcrys.setDefense(3);
        Mcrys.setAttack(15);
        Item Mrobe;
        Mrobe.setName("soul_sapping_robe");
        Mrobe.setPrice(300);
        Mrobe.setDefense(5);
        Mrobe.setAttack(10);
        merchantInventory.push_back(Mstff);
        merchantInventory.push_back(Mcrys);
        merchantInventory.push_back(Mrobe);
        merchantInventory.push_back(potn);
    }
    
    cout << "you set out on a journey to find the treasure hidden inside a cave on your map." << endl;
    cout << "you first venture through a forest." << endl;
    
    cout << "would you like to check your inventory and/or stats? y/n" << endl;
    pitStop(player);
    
    cout << "you have run into a bandit!" << endl;
    cout << "what do you do?" << endl;

    player.setHealth(engageBattle(player, bandit, gold));
    gold = gold + bandit.getGold();
    if(player.getHealth() == 0){
        return 0;
    }
    cout << "you venture further into the forest" << endl;
    
    cout << "would you like to check your inventory and/or stats? y/n" << endl;
    pitStop(player);
    
    cout << "you run into an ogre!" << endl;
    
    player.setHealth(engageBattle(player, ogre, gold));
    gold = gold + ogre.getGold();
    if(player.getHealth() == 0){
        return 0;
    }
    
    cout << "you've come across a merchant, would you like to trade with this merchant?" << endl;
    cout << "y/n: ";
    string choice;
    string trading;
    cin >> trading;
    while(trading != "y" && trading != "n"){
        cout << "that is not an option, try again." << endl;//making sure y or n is selected
        cout << "y/n: ";
        cin >> trading;
    }
    cout << "\n-------------------" << endl;
    
    //merchant stuff
    while(trading == "y"){
        cout << "would you like to buy, sell, or exit?" << endl;
        cout << "choice: ";
        cin >> choice;
        cout << "\n-------------------" << endl;
        if (choice == "buy"){//------------------------------------------------------------------buying
            cout << "merchant's items:" << endl;
            displayMerchantInventory();
            cout << "your gold: " << gold;
            cout << "choose what you'd like to buy, type anything else to cancel." << endl;
            string purchase;
            cin >> purchase;
            cout << "\n-------------------" << endl;
            for (unsigned i = 0; i < merchantInventory.size(); ++i)    {
                if (purchase == merchantInventory[i].getName() && purchase != "potion" && purchase != "SOLD OUT"){
                    if(gold >= merchantInventory[i].getPrice()){
                        cout << "you've bought a(n) " << merchantInventory[i].getName() << "!" << endl;
                        playerInventory.push_back(merchantInventory[i]);
                        gold = gold - merchantInventory[i].getPrice();
                        break;
                    }else{
                        cout << "you can't afford that." << endl;
                    }
                }else if(purchase == "potion"){
                    if(gold >= potn.getPrice()){
                        if(potions >= potionLimit){
                            cout << "You have too many potions and cannot buy another!" << endl;
                            break;
                        }else{
                            cout << "You've bought a potion!" << endl;
                            gold = gold - potn.getPrice();
                            ++potions;
                            cout << potions << " potions tested to limit" << endl;
                            playerInventory.push_back(potn);
                            break;
                        }
                    }else{
                        cout << "You can't afford that." << endl;
                        cout << "You bought nothing." << endl;
                        break;
                    }
                }else if(i == merchantInventory.size() -1){
                    cout << "You bought nothing." << endl;
                }
            }
            cout << "\n-------------------" << endl;
            cout << "Your inventory:" << endl;
            cout << gold << "g" << endl;
            displayPlayerInventory();
            cout << "\n-------------------" << endl;
            cout << "Would you like to continue trading?" << endl;
            cout << "y/n: ";
            cin >> trading;
            while(trading != "y" && trading != "n"){
                cout << "That is not an option, try again." << endl;
                cin >> trading;
            }
            cout << "\n-------------------" << endl;
        }else if(choice == "sell"){//---------------------------------------------------------------------------selling
            if(playerInventory.size() > 0){
                cout << "Choose what you would like to sell, type anything else to cancel." << endl;
                cout << "Your inventory:" << endl;
                cout << gold << "g" << endl;
                displayPlayerInventory();
                string sold;
                cin >> sold;
                for(unsigned i = 0; i < playerInventory.size(); ++i){
                    if(sold == "potion" && potions >= 1){
                        --potions;
                        cout << "You've sold a potion" << endl;
                        gold = gold + merchantInventory[i].getPrice();
                    }
                    if (sold == playerInventory[i].getName()){
                        cout << "You've sold a(n) " << playerInventory[i].getName() << endl;
                        playerInventory.erase(playerInventory.begin() + i);
                        gold = gold + playerInventory[i].getPrice();
                        break;
                    }else if(i == playerInventory.size() - 1) {
                        cout << "You've sold nothing." << endl;
                    }
                }
                cout << "\n-------------------" << endl;
                cout << "Your inventory:" << endl;
                cout << gold << "g" << endl;
                displayPlayerInventory();
                cout << "\n-------------------" << endl;
                cout << "Would you like to continue trading?" << endl;
                cout << "y/n: ";
                cin >> trading;
                while(trading != "y" && trading != "n"){
                    cout << "That is not an option, try again." << endl;
                    cin >> trading;
                }
                cout << "\n-------------------" << endl;
            }else{
                cout << "You don't have any items to sell!" << endl;
            }
        }else if (choice == "exit"){//--------------------------------------------------------------------exit
            cout << "You exit." << endl;
            break;
        }else{//------------------------------------------------------------------------------------------else
            cout << "That was not an option, try again." << endl;
        }
    }
    cout << "You decide not to." << endl;
    
    
    cout << "you found the cave entrance" << endl;
    cout << "you enter the cave" << endl;
    
    cout << "would you like to check your inventory and/or stats? y/n" << endl;
    pitStop(player);
    
    cout << "you are met with a live skeleton!" << endl;
    
    player.setHealth(engageBattle(player, skeleton, gold));
    gold = gold + skeleton.getGold();
    if(player.getHealth() == 0){
        return 0;
    }
    
    cout << "you are near your destination!" << endl;
    cout << "you venture further into the cave" << endl;
    
    cout << "would you like to check your inventory and/or stats? y/n" << endl;
    pitStop(player);
    
    cout << "you find the treasure laying in a pile behind a massive body" << endl;
    cout << "the troll king spots you!" << endl;
    
    player.setHealth(engageBattle(player, trollKing, gold));
    gold = gold + trollKing.getGold();
    if(player.getHealth() == 0){
        return 0;
    }
    
    cout << "you have found the treasure and claimed it for youself!";
    cout << "you win!" << endl;
    
    cout << "end of program" << endl;
    
    return 0;
    
}


float damageRand(float attack){
    int minAttack = ceil(attack*0.8);
    int maxAttack = ceil(attack*1.2);
    float grossDamage = rand() % (maxAttack - minAttack) + minAttack;
    grossDamage = grossDamage * maleStats;
    int critChance = (rand() % 10) + 1;
    if (critChance <=2){
        grossDamage = grossDamage * 2;
        cout << "CRIT!" << " ";
    }
    return grossDamage;
}

void displayMerchantInventory(){
    for(int i = 0; i < merchantInventory.size(); ++i){
        cout << merchantInventory[i].getName() << " " << merchantInventory[i].getPrice() << endl;
    }
}
void displayPlayerInventory(){
    for(int i = 0; i < playerInventory.size(); ++i){
        cout << playerInventory[i].getName() << " " << playerInventory[i].getPrice() << endl;
    }
}
int options(int damage, Player& player){
    cout << "attack or inventory" << endl;
    string choice;
    cin >> choice;
    choice = validChoice(choice, "attack", "inventory");
    lineBreak();
    if(choice == "attack"){
        damage = damageRand(damage);
        cout << "You deal " << damage << " damage" << endl;
        return damage;
    }else if(choice == "inventory"){
        return useInventory(player);
    }
    return 0;
}
string validChoice(string choice, string option1, string option2){
    while(choice != option1 && choice != option2){
        cout << "invalid choice, try again" << endl;
        cin >> choice;
    }
    return choice;
}
int useInventory(Player& player){
    bool errorTest = true;
    string continueChoice;
    
    while(errorTest){
        cout << "what would you like to equip, unequip or use? exit to leave" << endl;
        displayPlayerInventory();
        string choice;
        cin >> choice;
        cout << "BIG BOI STATS" << " attack: " << player.getDamage() << " defense: " << player.getArmour() << endl;
        for(int i = 0; i < playerInventory.size(); ++i){
            char painTest = choice.at(0);
            if(((painTest == '[') && choice == playerInventory[i].getName()) || choice == (playerInventory[i].getName().erase(playerInventory[i].getName().size() - 1))){
                cout << "you already have " << playerInventory[i].getName() << " equipped!" << endl;
                cout << "would you like to unequip it? y/n" << endl;
                string unequipChoice;
                cin >> unequipChoice;
                continueChoice = validChoice(unequipChoice, "y", "n");
                
                if (unequipChoice == "y"){
                    cout << "you have unequpped a(n) " << playerInventory[i].getName() << endl;
                    playerInventory[i].setName(playerInventory[i].getName().erase(playerInventory[i].getName().size() - playerInventory[i].getName().size(), 1));
                    playerInventory[i].setName(playerInventory[i].getName().erase(playerInventory[i].getName().size() - 1));
                    player.setDamage(player.getDamage() -  playerInventory[i].getAttack());
                    player.setArmour(player.getArmour() - playerInventory[i].getDefense());
                    
                }else if(unequipChoice == "n"){
                    cout << "you decide not to";
                }
                displayPlayerInventory();
                cout << "would you like to equip, unequip or use anything else? y/n" << endl;
               
                cin >> continueChoice;
                continueChoice = validChoice(continueChoice, "y", "n");
                
                if(continueChoice == "n"){
                    choice = "exit";
                }else{
                    continue;
                }
                
            }else if(choice == "potion" && choice == playerInventory[i].getName()){
                cout << "you have used a potion!" << endl;
                vector<Item>::iterator iter;
                iter = (playerInventory.begin() + i);
                playerInventory.erase(iter);
                return -1;
                
            }else if(choice == playerInventory[i].getName()){
                bool test = equipTest(choice);
                if(test == true){
                    playerInventory[i].setName("[" + playerInventory[i].getName() + "]");
                    lineBreak();
                    cout << "you have equipped a(n) " << playerInventory[i].getName() << endl;
                    player.setArmour(player.getArmour() + playerInventory[i].getDefense());
                    player.setDamage(player.getDamage() + playerInventory[i].getAttack());
                }
                
                cout << "would you like to equip, unequip or use anything else? y/n" << endl;
                cin >> continueChoice;
                continueChoice = validChoice(continueChoice, "y", "n");
                
                if(continueChoice == "n"){
                    choice = "exit";
                }else{
                    continue;
                }
            }
            if(choice == "exit"){
                return 1;
            }
        }
       
        if(continueChoice == "y"){
            continue;
        }
        
    }
    return 0;
}
void lineBreak(){
    cout << "-----------------------------" << endl;
}
int engageBattle(Player& player, Enemy enemy, int gold){
    bool battle = true;
    int armour = player.getArmour();
    
    while(battle){
        int playerDamage = options(player.getDamage(), player);
        if (playerDamage == -1){
            player.doHeal(POTION_HEALTH, MAX_HEALTH);
            cout << "your health is now " << player.getHealth() << endl;
        }else{
            enemy.healthDamage(playerDamage);
            cout << "the " << enemy.getName() << " has " << enemy.getHealth() << " health" << endl << endl;
        }
        int enemyDamage = damageRand(enemy.getDamage());
        if(enemyDamage <= 0){
            enemyDamage = 0;
        }
        if(enemy.getHealth() > 0){
            player.healthDamage(enemyDamage - armour);
            cout << "the " << enemy.getName() << " has hit you for " << enemyDamage - player.getArmour() << "!" << endl;
            cout << "you have " << player.getHealth() << " health" << endl;
            cout << endl;
        }
        if(player.getHealth() == 0){
            battle = player.death(battle);
            cout << "you have died" << endl;
            return 0;
        }
        
        if(enemy.getHealth() == 0){
            cout << "you have killed the " << enemy.getName() << "!" << endl;
            battle = enemy.death(battle);
            cout << "the enemy has dropped " << enemy.getGold() << " gold!" << endl << endl;
        }
        
    }
    return player.getHealth();
}

bool equipTest(string choice){
    for(int i = 0; i < playerInventory.size(); ++i){
        if(choice == playerInventory[i].getName()){
            if(choice == "wood_shield"){
                for(int i = 0; i < playerInventory.size(); ++i){
                    if(playerInventory[i].getName() == "[iron_kite_shield]"){
                        cout << "you cannot have more than one shield equipped!" << endl;
                        return false;
                    }
                }
            }else if(choice == "iron_kite_shield"){
                for(int i = 0; i < playerInventory.size(); ++i){
                    if(playerInventory[i].getName() == "[wood_shield]"){
                        cout << "you cannot have more than one shield equipped!" << endl;
                        return false;
                    }
                }
            }else if(choice == "iron_sword"){
                for(int i = 0; i < playerInventory.size(); ++i){
                    if(playerInventory[i].getName() == "[mithril_sword]"){
                        cout << "you cannot have more than one weapon equipped!" << endl;
                        return false;
                    }
                }
            }else if(choice == "mithril_sword"){
                for(int i = 0; i < playerInventory.size(); ++i){
                    if(playerInventory[i].getName() == "[iron_sword]"){
                        cout << "you cannot have more than one weapon equipped!" << endl;
                        return false;
                    }
                }
            }else if(choice == "iron_chestplate"){
                for(int i = 0; i < playerInventory.size(); ++i){
                    if(playerInventory[i].getName() == "[mithril_chestplate]"){
                        cout << "you cannot have more than one armour equipped!" << endl;
                        return false;
                    }
                }
            }else if(choice == "mithil_chestplate"){
                for(int i = 0; i < playerInventory.size(); ++i){
                    if(playerInventory[i].getName() == "[mithril_sword]"){
                        cout << "you cannot have more than one armour equipped!" << endl;
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int checkInventory(Player& player){
    cout << "Health: " << player.getHealth() << endl;
    cout << "damage: " << player.getDamage() << endl;
    cout << "defense: " << player.getArmour();
    if(maleStats > 1){
        cout << " (x1.25 male bonus)" << endl;
    }else{
        cout << endl;
    }
    if(useInventory(player) == -1){
        return -1;
    }
    return 0;
}
void pitStop(Player& player){
    string inventoryCheckChoice;
    cin >> inventoryCheckChoice;
    validChoice(inventoryCheckChoice, "y", "n");
    if(inventoryCheckChoice == "y"){
        if (checkInventory(player) == -1){
            player.doHeal(POTION_HEALTH, MAX_HEALTH);
            cout << "your health is now " << player.getHealth() << endl;
        }
    }
}
