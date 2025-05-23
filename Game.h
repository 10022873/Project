#ifndef GAMEBROADCAT_H
#define GAMEBROADCAT_H

#include <string>
#include <vector>
#include <map>
#include <memory>

using namespace std;

// Forward declartions
class Player;
class Team;
class StatsOverlay;


class StatsDatabase {

public:

    StatsDatabase();
    ~StatsDatabase();

    map<string, float> fetchPlayerStats(const string& playerName);
    void updateStats(const string& playerNme, const map<string, float>& newStats);
    void connectToLiveFeed();

private:

    map<string, map<string, float>> playerData;
};


class LiveDataFeed {

public:

    LiveDataFeed(StatsDatabase& db);
    ~LiveDataFeed();

    void startFeed();
    void stopFeed();
    void pushUpdate(const string& playerName, const map<string, float>& stats);

private:

    StatsDatabase& database;
    bool isActive;
};


class Player {

public:

    Player(const string& name, const string& team, const string& positon);
    ~Player();

    string getName() const;
    string getTeam() const;
    string getPosition() const;
    map<string, float> getStats() const;
    void updateStats(const map<string, float>& newStats);

private:

    string name, team, positon;
    map<string, float> stats;
};


class Team {

public:

    Team(const string& name);
    ~Team();

    void addPlayer(shared_ptr<Player> player);
    vector<shared_ptr<Player>> getRoster() const;
    shared_ptr<Player> getPlayer(const string& name) const;
    map<string, float> getTeamStats() const;

private:

    string name;
    vector<shared_ptr<Player>> roster;
};


class StatsOverlay {

public:

    StatsOverlay(const shared_ptr<Player>& player, const map<string, float>& stats);
    ~StatsOverlay();

    void render();
    void updateStats(const map<string, float>& newStats);
    void setPosition(int x, int y);
    void setDuration(float seconds);
    void hide();

private:

    shared_ptr<Player> player;
    map<string, float> currentStats;
    int posX, posY;
    float displayDuration;
    bool isVisible;
};


class BroadcastGraphicsEngine {

public:

    BroadcastGraphicsEngine();
    ~BroadcastGraphicsEngine();

    void addOverlay(shared_ptr<StatsOverlay> overlay);
    void removeOverlay(shared_ptr<StatsOverlay> overlay);
    void renderAll();
    void clearAll();

private:

    vector<shared_ptr<StatsOverlay>> activeOverlays;
};


class CommentatorInterface {

public:

    CommentatorInterface(BroadcastGraphicsEngine& graphicsEngine, const vector<shared_ptr<Team>>& teams);
    ~CommentatorInterface();

    void selectPlayer(const string& playerName);
    void requestStats(const string& playerName);
    void showOverlay(const string& playerName);
    void hideOverlay(const string& playerName);

private:

    BroadcastGraphicsEngine& graphicsEngine;
    vector<shared_ptr<Team>> availableTeams;
    shared_ptr<Player> selectedPlayer;
};


class UserInputHandler {

public:

    UserInputHandler(CommentatorInterface& interface);
    ~UserInputHandler();

    void processCommand(const string& command);
    void detectSelection(int x, int y);

private:

    CommentatorInterface& commentatorInterface;
};


class GameBroadcast {

public:

    GameBroadcast(const vector<shared_ptr<Team>>& teams);
    ~GameBroadcast();

    void startBroadcast();
    void stopBroadcast();
    void receiveCommentatorInput(const string& input);
    void updateDisplay();

private:

    vector<shared_ptr<Team>> currentTeams;
    StatsDatabase statsDB;
    LiveDataFeed liveFeed;
    BroadcastGraphicsEngine graphicsEngine;
    CommentatorInterface commentatorInterface;
    UserInputHandler inputHandler;
    bool isBroadasting;
};


#endif
