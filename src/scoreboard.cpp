// STUDENT CODE: new class for maintaining hightest scores for each player

#include "scoreboard.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Scoreboard::Scoreboard()
  : m_fpath{"../out/scoreboard.txt"}  // assume the game being launched from <proj repo>/build
  , m_user{""}
  , m_score{0}
  , m_board{}
{
  std::cout << "What's your username: ";
  std::cin >> m_user;
  std::replace(m_user.begin(), m_user.end(), ' ', '_');
  LoadFromTxt();
}

std::string Scoreboard::GetUsername() const
{
  return m_user;
}

void Scoreboard::UpdateScore(int score)
{
  if (m_board.find(m_user) == m_board.end()) {
    m_board.emplace(m_user, score);
  }
  else if (m_board.at(m_user) < score) {
    m_board[m_user] = score;
  }
}

void Scoreboard::LoadFromTxt()
{
  std::map<std::string, int> board;
  std::string line;
  std::string key;
  int value;
  std::ifstream filestream(m_fpath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      m_board.emplace(key, value);
    }
    filestream.close();
  }
}

void Scoreboard::WriteToTxt()
{
  std::ofstream filestream(m_fpath);
  if (filestream.is_open()) {
    for (const auto &p : m_board) {
      filestream << p.first << " " << p.second << '\n';
    }
    filestream.close();
  }
}
