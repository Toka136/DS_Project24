#include"Player.h"
#include <iostream>
#include <string>
#include<vector>
#include <map>
#include<algorithm>
#include<set>
using namespace std;
int player::ID = 1001;
player::player(string username, string password) {
    ID++;
    UserName = username;
    Password = password;
    Budget = 0.00;
}
player::player() {
}
void player::setUserName(string username) {
    UserName = username;
}
string player::getUserName() {
    return UserName;

}
void  player::setPass(std::string password) {
    Password = password;
}
string player::getPass() {
    return Password;
}
int player::get_id() {
    return ID;
}
void player::set_budget(double budget) {
    Budget = budget;
}
double player::get_budget() {
    return Budget;
}

void player::setPoints(int point) {
    points = point;
}
int player::getPoints() {
    return points;
}
void player::setdecoration(vector<pair<string, float>> x) {
    Decoration = x;
}
vector<pair<string, float>> player::getdecoration() {
    return Decoration;
}
float player::SerachProduct(string name, int& ind) {
    vector<pair<string, float>> list = getdecoration();
    for (int i = 0; i < list.size(); i++) {
        if (list[i].first == name) {
            ind = i;
            return list[i].second;
        }
    }
    return  -1;
}
float player::Sellproduct(string s) {
    int ind = -1;
    float price = SerachProduct(s, ind);
    if (ind == -1) {
        cout << "invalid product\n";
    }
    else {
        Decoration.erase(Decoration.begin() + ind);
    }
    for (auto it : Decoration) {
        cout << it.first << " " << it.second << "\n";
    }
    return price;
}
void player::Buyproduct(string s, float price) {
    Decoration.push_back(make_pair(s, price));
    for (auto it : Decoration) {
        cout << it.first << " " << it.second << "\n";
    }
}
float player::Replaceproduct(string s, float price) {
    cout << "Enter Name of old product\n";
    string old_product;
    cin >> old_product;
    int replace_index;
    float old_price = SerachProduct(old_product, replace_index);
    float diff = old_price - price;
    Decoration.erase(Decoration.begin() + replace_index);
    Decoration.push_back(make_pair(s, price));
    for (auto it : Decoration) {
        cout << it.first << " " << it.second << "\n";
    }
    return diff;
}
player::~player() {
    //cout << "end\n";
}

PlayerManager::PlayerManager() {
    player newplayer("toka", "12345");
    vector<pair<string, float>> d;
    d.push_back(make_pair("bed", 300));
    d.push_back(make_pair("chair", 500));
    newplayer.setdecoration(d);
    players.insert(make_pair(newplayer.getUserName(), newplayer));
}
int PlayerManager::signUpPlayer(string& username, string& password)
{
    // Check if username already exists
    if (players.find(username) != players.end()) {
        return -1;
    }
    unordered_map<string, player>::iterator it = players.begin();
    bool f = 0;
    while (it != players.end()) {
        if (it->second.getPass() == password) {
            f = 1;
            break;
        }
        it++;
    }
    if (f) {
        return -2;
    }
    string newusername = 'P' + username;
    player newPlayer(newusername, password);

    // Add the new user to the map
    players.insert({ username, newPlayer });

    cout << "Player signed up successfully!\n";
    cout << "Your User Name is : " << newPlayer.getUserName() << "\n";
    cout << "Your ID id : " << newPlayer.get_id() << "\n";

    return 1;
}
int PlayerManager::signInPlayer(string& username, string& password) {
    auto it = players.find(username);
    if (it != players.end()) {
        if (it->second.getPass() == password) {
            currentplayer = it->second;
            cout << "User signed in successfully!\n";
            choiseoperation();
            return 1;
        }
        return -2;
    }

    return -1;
}
void PlayerManager::signOutPlayer()
{
    //currentUser = "";
    cout << "Player signed out successfully!\n";
}
void PlayerManager::choise() {
    int press;
    bool f = 0;
    while (true) {
        if (!f) {
            cout << "1. Sign Up\n";
            cout << "2. Sign In\n";
            cout << "3. Sign Out\n";
            cout << "4. Exit\n";
            cin >> press;
            cin.ignore();
        }
        if (press == 1) {
            bool p = 0;
            string username, password;
            while (true) {

                if (!p) {
                    cout << "Enter username: " << '\n';
                    getline(cin, username);
                    cout << "Enter password (Should be greater than or equal 8 charchters): " << '\n';
                    getline(cin, password);

                }
                else if (p) {
                    cout << "Enter password: " << '\n';
                    getline(cin, password);
                }
                if (signUpPlayer(username, password) == 1)
                    break;
                if (signUpPlayer(username, password) == -2) {
                    if (password.size() < 8)
                        cout << "Password Should be greater than or equal 8 charchters\n";
                    else
                        cout << "Password already exists. Please choose a different one.\n";
                    p = 1;
                }
                else
                    if (signUpPlayer(username, password) == -1) {
                        cout << "Username already exists. Please choose a different one.\n";
                    }

            }
            break;
        }
        else if (press == 2) {
            bool x = 0;
            int c = 1;
            string username, password;
            while (true) {
                if (!x) {
                    if (c == 4) {
                        cout << "UserName is Wrong go to Sign Up\n";
                        f = 1;
                        break;
                    }
                    c++;
                    cout << "Enter username: " << '\n';
                    getline(cin, username);
                    cout << "Enter password: " << '\n';
                    getline(cin, password);
                }
                else if (x) {
                    if (c == 4) {
                        cout << "Password is Wrong go to Sign Up\n";
                        f = 1;
                        break;
                    }
                    cout << "Enter password: " << '\n';
                    getline(cin, password);
                    c++;
                }
                if (signInPlayer(username, password) == 1)
                    break;
                else if (signInPlayer(username, password) == -2) {
                    if (c == 4)
                        x = 1;
                    else {
                        cout << "Invalid password . Please try again.\n";
                        x = 1;
                    }
                }
                else {
                    if (c == 4)
                        x = 0;
                    else {
                        cout << "Invalid username  . Please try again.\n";
                    }
                }
            }
            if (f)
                press = 1;
            else
                break;
        }
        else if (press == 3) {
            signOutPlayer();
            break;
        }
        else if (press == 4) {
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }

    }
}
void PlayerManager::choiseoperation() {
    while (true) {
        int press;
        cout << "1. Search product\n";
        cout << "2. Sell product\n";
        cout << "3. Buy product\n";
        cout << "4. Replace product\n";
        cout << "5. Exit\n";
        cin >> press;
        cin.ignore();
        if (press == 1) {
            cout << "Enter Name of Product: \n";
            string product;
            cin >> product;
            transform(product.begin(), product.end(), product.begin(), ::tolower);
            //cout << currentplayer.getUserName();
            int ind;
            cout << currentplayer.SerachProduct(product, ind);
            // break;
        }
        else if (press == 2) {
            cout << "Enter Name of Product: \n";
            string product;
            cin >> product;
            transform(product.begin(), product.end(), product.begin(), ::tolower);
            currentplayer.Sellproduct(product);
            // break;
        }
        else if (press == 3) {
            cout << "Enter Name of Product: \n";
            string product;
            cin >> product;
            float price = 300;
            transform(product.begin(), product.end(), product.begin(), ::tolower);
            currentplayer.Buyproduct(product, price);
            //break;
        }
        else if (press == 4) {
            cout << "Enter Name of Product: \n";
            string product;
            cin >> product;
            transform(product.begin(), product.end(), product.begin(), ::tolower);
            currentplayer.Replaceproduct(product, 300);
            //break;
        }
        else if (press == 5) {
            cout << "Thank You\n";
            break;
        }
        else {
            cout << "Invalid choise please try again\n";
        }
        string ans;
        cout << "Do You Want Make Another Operation (yes/no): \n";
        cin >> ans;
        transform(ans.begin(), ans.end(), ans.begin(), ::tolower);
        if (ans == "no")
            break;
    }

}
PlayerManager::~PlayerManager() {
}