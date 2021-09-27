class LFUCache {
    struct Node {
        int key;
        int value;
        int freq;
    };
    int _tcap;
    int _ccap;
    vector<list<Node>> _lists;
    map<int, list<Node>::iterator> _map1;
    
    bool isLimitExceeded() {
        if (_ccap == _tcap)
            return true;
        return false;
    }
    
    void removeLFUElement() {
        if (!_lists.size())
            return;
        for (auto& list:_lists) {
            auto n = list.back();
            if (!n.freq)
                continue;
            int key_rem=n.key;
            list.erase(_map1[n.key]);
            if (!list.size()) {
                _lists[n.freq-1].emplace_back(Node{});
            }
            _map1.erase(n.key);
            _ccap--;
            return;
        }
        
    }
public:
    LFUCache(int capacity) : _tcap(capacity), _ccap(0) {
        
    }
    
    int get(int key) {
        
        auto itr = _map1.find(key);
        if (itr == _map1.end())
            return -1;
        auto itr_node = itr->second;
        int value = itr_node->value;
        int freq = itr_node->freq;
        _lists[freq-1].erase(itr_node);
        _map1.erase(key);
        if (!_lists[freq-1].size()) {
            _lists[freq-1].emplace_back(Node{});
        }
        
        if (_lists.size() <= freq) {
            
             Node n = {key, value, freq+1};
            list<Node> list1;
            list1.push_back(n);
            _lists.push_back(list1);
            _map1[key] = _lists[freq].begin();
        } else {
            auto n1 = _lists[freq].front();
            auto itr = _lists[freq].begin();
            bool is_null = false;
            if(!n1.freq) {
                is_null = true;
            }
            _lists[freq].emplace(_lists[freq].begin(), Node{key, value, freq+1});
            _map1[key] = _lists[freq].begin();
            if (is_null)
                _lists[freq].erase(itr);
        }
           
        return value;
    }
    
    void put(int key, int value) {
        if (!_tcap)
            return;
        auto itr = _map1.find(key);
        //element not present in map
        if (itr == _map1.end()) {
           if (!_lists.size()) {
               list<Node> list1;
               Node n = {key, value, 1};
               list1.push_back(n);
               _lists.push_back(list1);
               _map1[key]= _lists[0].begin();
            } else {
                if (isLimitExceeded()) {
                    removeLFUElement();
                }
                auto n1 = _lists[0].front();
                auto itr = _lists[0].begin();
                bool is_null = false;
                if(!n1.freq) {
                    is_null = true;
                }
                _lists[0].emplace(_lists[0].begin(), Node{key, value, 1});
                _map1[key] = _lists[0].begin(); 
                if (is_null)
                    _lists[0].erase(itr);
            }
            _ccap++;
        }
        //element present in map
        else {
    
            auto itr_node = itr->second;
            int freq = itr_node->freq;
            //delete from present list
            _lists[freq-1].erase(itr_node);
            //delete from map
            _map1.erase(key);
            if (!_lists[freq-1].size()) {
                _lists[freq-1].emplace_back(Node{});
            }

            if (_lists.size() < freq+1) {
                
                list<Node> list1;
                Node n = {key, value, freq+1};
                list1.push_back(n);
                _lists.push_back(list1);
                _map1[key] = _lists[freq].begin();
                
            } else {
                auto n1 = _lists[freq].front();
                auto itr = _lists[freq].begin();
                bool is_null = false;
                if(!n1.freq) {
                    is_null = true;
                }
                _lists[freq].emplace(_lists[freq].begin(), Node{key, value, freq+1});
                _map1[key] = _lists[freq].begin();
                if (is_null)
                    _lists[freq].erase(itr);
            }
        }
        
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
