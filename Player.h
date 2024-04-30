#include <iostream>
#include <string>
#include<vector>
#include <map>
#include<unordered_map>
#include<set>
using namespace std;
class player {
private:
    static int ID;
    int points;
    string UserName;
    string Password;
    double Budget;
    vector<pair<string, float>>Decoration;
public:
    player(string username, string password);
    player();
    void setUserName(string username);
    string getUserName();
    void setPass(string password);
    string getPass();
    //void set_ID();
    int get_id();
    void setPoints(int point);
    int getPoints();
    void set_budget(double budget);
    double get_budget();
    vector<pair<string, float>>getdecoration();
    void setdecoration(vector<pair<string, float>>);
    float SerachProduct(string name, int&);
    ~player();
    float Sellproduct(string s);
    void Buyproduct(string s, float price);
    float Replaceproduct(string s, float price);

};
class PlayerManager {
public:
    PlayerManager();
    ~PlayerManager();
    unordered_map<string, player>players;
    player currentplayer;
    int signUpPlayer(string& username, string& password);
    int signInPlayer(string& username, string& password);
    void signOutPlayer();
    void choise();
    void choiseoperation();

};
