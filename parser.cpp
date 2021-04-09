#include <bits/stdc++.h>

using namespace std;

map <string, map <int, int>> solveds;
map <string, map <int, int>> penalties;

int main() {
  ifstream in;
  ofstream out("out.txt");
  int contestCount = 20;
  for (int id = 1; id <= contestCount; ++id) {
    string input = "contest-" + to_string(id) + ".txt";
    in.open(input);
    string bloodyHTML = "", line;
    while (getline(in, line)) bloodyHTML += line;
    string pattern = "<td class=\"team meta\"";
    for (int i = 0; i + pattern.size() <= bloodyHTML.size(); ++i) {
      if (bloodyHTML.substr(i, pattern.size()) == pattern) {
        int j = i;
        string div = "<div>";
        while (bloodyHTML.substr(j, div.size()) != div) ++j;
        string title = "title=\"";
        while (bloodyHTML.substr(j, title.size()) != title) ++j;
        j += title.size();
        string handle = "", nick = "";
        while (bloodyHTML[j] != ' ' and bloodyHTML[j] != '\"') handle += bloodyHTML[j++];
        if (bloodyHTML[j] == ' ') {
          ++j; while (bloodyHTML[j] != '\"') nick += bloodyHTML[j++];
        }
        string solvedPattern = "<a href=\"#status/" + handle + "/-/0/\">";
        while (bloodyHTML.substr(j, solvedPattern.size()) != solvedPattern) ++j;
        j += solvedPattern.size();
        string solvedString = "";
        while (isdigit(bloodyHTML[j])) solvedString += bloodyHTML[j++];
        string penaltyPattern = "<span class=\"minute\">";
        while (bloodyHTML.substr(j, penaltyPattern.size()) != penaltyPattern) ++j;
        j += penaltyPattern.size();
        int solved = stoi(solvedString);
        string penaltyString = "";
        while (isdigit(bloodyHTML[j])) penaltyString += bloodyHTML[j++];
        int penalty = stoi(penaltyString);
        string identifier = handle;
        if (!nick.empty()) identifier += " (" + nick + ")";
        solveds[identifier][id] = solved;
        penalties[identifier][id] = penalty;
        i = j;
      }
    }
    in.close();
  }
  for (auto it : solveds) {
    string id = it.first;
    cout << id << " --> ";
    for (int i = 1; i <= contestCount; ++i) cout << "(" << solveds[id][i] << ", " << penalties[id][i] << ") ";
    cout << '\n';
  }
  vector <tuple <int, int, string>> vec;
  for (auto [id, sth] : solveds) {
    int totalSolvedNeg = 0, totalPenalty = 0;
    for (int i = 1; i <= contestCount; ++i) totalSolvedNeg -= solveds[id][i], totalPenalty += penalties[id][i];
    vec.emplace_back(totalSolvedNeg, totalPenalty, id);
  }
  sort(vec.begin(), vec.end());
  out << "Sorted Names\n=========================\n";
  for (auto [sth, sthElse, id] : vec) {
    out << id << '\n';
  }
  out << '\n';
  for (int i = 1; i <= contestCount; ++i) {
    out << "Contest " << i << "\n======================\n";
    out << "Solved\n----------\n";
    for (auto [sth, sthElse, id] : vec) {
      out << solveds[id][i] << '\n';
    }
    out << '\n';
    out << "Penalty\n----------\n";
    for (auto [sth, sthElse, id] : vec) {
      out << penalties[id][i] << '\n';
    }
    out << '\n' << '\n';
  }
  out << "Total Solved\n========================\n";
  for (auto [sth, sthElse, id] : vec) {
    int tot = 0;
    for (int i = 1; i <= contestCount; ++i) tot += solveds[id][i];
    out << tot << '\n';
  }
  out << '\n';
  out << "Total Penalty\n=========================\n";
  for (auto [sth, sthElse, id] : vec) {
    int tot = 0;
    for (int i = 1; i <= contestCount; ++i) tot += penalties[id][i];
    out << tot << '\n';
  }
  out << '\n';
  return 0;
}

