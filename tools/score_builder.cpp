// Author: Mikhail Ivanov (ivanovmihail99@gmail.com)
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

const string SCORE_STRING = "score.txt";
const string SCORE_OUTPUT_STRING = "total_score.txt";
const string TASKS_STRING = "somefile";
const string REPEATABLE_TASK = "issue";
const string OWNER_SUBTASK = "ok";
const int MAX_POINTS = 30;

pair<string, pair<string, string>> task_subtask_executor(const string& s)
{
	pair<string, pair<string, string>> ans;
	int i = 0;
	while (i < ((int)(s.size())) && s[i] != '.')
		ans.first.push_back(s[i++]);
	if (s[i] != '.')
		return pair<string, pair<string, string>>();
	++i;
	while (i < ((int)(s.size())) && (s[i] != ' ') && (s[i] != '\t'))
		ans.second.first.push_back(s[i++]);
	while ((s[i] == ' ') || (s[i] == '\t'))
		++i;
	while (i < ((int)(s.size())))
		ans.second.second.push_back(s[i++]);
	while (ans.second.second.size() && ((ans.second.second.back() == ' ') || (ans.second.second.back() == '\t')))
		ans.second.second.pop_back();
	return ans;
}

int main(int argc, char* argv[])
{
	string s = ((argc >= 2) ? argv[1] : TASKS_STRING);
	ifstream tasks(s);
	ofstream fout(SCORE_OUTPUT_STRING);
	string task;
	unordered_map<string, pair<int, unordered_set<string>>> people;
	while (getline(tasks, task))
	{
		task += SCORE_STRING;
		ifstream fin(task);
		unordered_map<string, unordered_map<string, string>> projs;
		string three;
		while (getline(fin, three))
		{
			auto s = task_subtask_executor(three);
			if (s.second.second.size())
			{
				if (s.first == REPEATABLE_TASK)
					++people[s.second.second].first;
				else
					projs[s.first][s.second.first] = s.second.second;
			}
		}
		for (auto it = projs.begin(); it != projs.end(); ++it)
		{
			auto looking_for_owner = it->second.find(OWNER_SUBTASK);
			string project_owner = looking_for_owner != it->second.end() ? looking_for_owner->second : "";
			for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
			{
				if (jt->second == project_owner)
					people[jt->second].second.insert(it->first + "." + jt->first);
				else
					people[jt->second].second.insert(jt->first);
			}
		}
	}
	int n = people.size();
	vector<pair<string, int>> ans(n);
	int t = 0;
	for (auto it = people.begin(); it != people.end(); ++it, ++t)
		ans[t] = make_pair(it->first, min(MAX_POINTS, it->second.first + ((int)(it->second.second.size()))));
	sort(ans.begin(), ans.end());
	for (int t = 0; t < n; ++t)
		fout << ans[t].first << ' ' << ans[t].second << '\n';
	return 0;
}
