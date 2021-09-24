class Solution {
    map<string, vector<int>> map1;
    
    void dictUpdate(vector<string>& wordsDict) {
        for (int i = 0; i < wordsDict.size(); i++) {
            auto itr = map1.find(wordsDict[i]);
            if (itr == map1.end()) {
                vector<int> locs;
                locs.push_back(i+1);
                map1[wordsDict[i]] = locs;
            } else {
                auto& locs = itr->second;
                locs.push_back(i+1);
            }
        }
    }
    
    int diffWordsDistance(string& word1, string& word2) {
        
        auto itr1 = map1.find(word1);
        auto itr2 = map1.find(word2);
        if (itr1 == map1.end()) {
            auto locs2 = itr2->second;
            return locs2[0];
        }
        if (itr2 == map1.end()) {
            auto locs1 = itr1->second;
            return locs1[0];
        }
        
        auto& locs1 = itr1->second;
        auto& locs2 = itr2->second;
        
        int min_dist = INT_MAX;
        
        int i = 0;
        int j = 0;
        while ( i < locs1.size() && j < locs2.size()) {
            min_dist = min(min_dist, abs(locs1[i]-locs2[j]));
            if (!min_dist)
                return 0;
            if (locs1[i] < locs2[j])
                i++;
            else
                j++;
        }
        return min_dist;
    }

    int sameWordsDistance (string& word1) {
        auto itr1 = map1.find(word1);
        if (itr1 == map1.end()) {
            return 0;
        }
        
        auto& locs1 = itr1->second;
        if (locs1.size()==1)
            return 0;
        
        int min_dist = INT_MAX;
        
        int i = 0;
        
        while ( i < locs1.size()-1) {
            int j = i+1;
            min_dist = min(min_dist, abs(locs1[i]-locs1[j]));
            i++;
        }
        return min_dist;
    }
public:
    int shortestWordDistance(vector<string>& wordsDict, string word1, string word2) {
        dictUpdate(wordsDict);
        if (word1 == word2) 
            return sameWordsDistance(word1);
       return diffWordsDistance(word1, word2);
    }
};
