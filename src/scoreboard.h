// STUDENT CODE: new class for maintaining hightest scores for each player

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <map>
#include <string>

// This class maintains the scoreboard
// 1. read historical scores from <proj repo>/out/scoreboard.csv
// 2. ask for user name of the current player
// 3. if the current player achieves a higher score than before, then update the scoreboard
// 4. write m_board to scoreboard.txt after the game ends
class Scoreboard
{
public:
  Scoreboard();
  ~Scoreboard() = default;

  Scoreboard(const Scoreboard& other) = delete;
  Scoreboard(Scoreboard&& source) = delete;
  Scoreboard& operator=(const Scoreboard& other) = delete;
  Scoreboard& operator=(Scoreboard&& source) = delete;

  std::string GetUsername() const;

  void UpdateScore(int score);  // update score for m_user if it's higher
  void WriteToTxt();            // write m_board to scoreboard.txt

private:
  void LoadFromTxt();           // populate m_board by parsing scoreboard.txt (space separated)

private:
  std::string m_fpath;
  std::string m_user;
  int m_score;
  std::map<std::string, int> m_board;
};

#endif