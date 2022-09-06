#pragma once
#include<unordered_map>
#include<string>
#include<algorithm>

using namespace std;

class MinWindow
{
	unordered_map<char, int> map;
	unordered_map<char, int> count;
public:

	bool check() {
		for (auto item : map) {
			if (item.second > 0) {
				return false;
			}
		}
		return true;
	}

	string minWindow(string s, string t) {
		int len1 = s.length();
		int len2 = t.length();

		if (len2 > len1) return "";

		for (int i = 0; i < len2; i++) {
			map[t[i]]++;
		}
		int start = s.find_first_of(t);
		
		int end = 0;
		int minLen = INT_MAX;
		int left = 0;		
			
		map[s[start]]--;
		count[s[start]]++;
		if (check()) return s.substr(start, 1);

		for (int j = end + 1; j < len1; j++) {
			if (map.find(s[j]) != map.end()) {
				map[s[j]]--;
				end = j;
				while (start <= end && check()) {
					int curLen = end - start + 1;
					if (curLen < minLen) {
						left = start;
						minLen = curLen;
					}

					if (map.find(s[start]) != map.end()) map[s[start]]++;
					start++;
					while (map.find(s[start]) == map.end()) start++;
				}
			}
		}

		return minLen <= len1? s.substr(left, minLen) : "";
	}
};

class MaxWindow {
public:
	pair<int, int> getmax(vector<int>& nums, int left, int right) {
		int maxNum = nums[left];
		int maxIndex = left;
		for (int i = left + 1; i <= right; i++) {
			if (nums[i] >= maxNum) {
				maxNum = nums[i];
				maxIndex = i;
			}
		}
		return { maxIndex, maxNum };
	}

	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		int n = nums.size();
		if (k == 1) return nums;

		int left = 0;
		int right = 0;

		vector<int> ans(n - k + 1);
		auto first = getmax(nums, 0, k - 1);
		ans[0] = first.second;
		int maxIndex = first.first;
		int maxNum = first.second;

		for (int left = 1; left < n - k + 1; left++) {
			if (left > maxIndex) {
				auto maxPair = getmax(nums, left, left + k - 1);
				maxIndex = maxPair.first;
				maxNum = maxPair.second;
				ans[left] = maxNum;
			}
			else {
				if (nums[left + k - 1] >= maxNum) {
					maxNum = nums[left + k - 1];
					maxIndex = left + k - 1;
				}
				ans[left] = maxNum;	
			}
		}
		return ans;
	}
};