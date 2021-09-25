struct Data {
    int key;
    int value;
    Data* prev;
    Data* next;
    Data(int k1, int v1) {
        key = k1;
        value = v1;
        prev = nullptr;
        next = nullptr;
    }
};

class LRUCache {
    
    Data *head;
    Data *tail;
    map<int, Data*> map1;
    int _ccap;
    int _tcap;
    
    void bring2Head(Data* data, int key, int value) {
        if (!data)
            return;
        if (data==head) {
            data->value = value;
            return;   
        }
        if (data->prev) {
            data->prev->next= data->next;
        }
        if (data->next) {
            data->next->prev = data->prev;
        }
        if (data==tail) {
            if (!data->next)
                tail = data->prev;
            else
                tail = data->next;
        }
        data->next=head;
        head->prev= data;
        head= data;
        data->value = value;
        data->prev=nullptr;
        
    }
    
    Data* add2cache(int key, int value){
        Data *data = new Data(key, value);
        data->next = head;
        if (!tail) {
            head = data;
            tail = data;
        } else {
            head->prev = data;
            head = data;
        }
        return data;
    }
    
    int removetail(int& key_removed) {
        if (!tail)
            return -1;
        auto data = tail->prev;
        key_removed = tail->key;
        if (!data) {
            
            delete tail;
            tail = nullptr;
            head = nullptr;
            return 0;
        }
        data->next=nullptr;
        delete tail;
        tail = data;
        return 0;
    }
public:
    LRUCache(int capacity) {
        _tcap = capacity;
        _ccap =0;
        head = nullptr;
        tail = nullptr;

    }
    
    int get(int key) {
        if(_tcap == 0)
            return -1;
        auto itr = map1.find(key);
        if (itr == map1.end())
            return -1;
        auto data = itr->second;
        bring2Head(data, key, data->value);
        return data->value;
    }
    
    void put(int key, int value) {
        if(_tcap == 0)
            return;
        auto itr = map1.find(key);
        if ( itr != map1.end()) {
            bring2Head(itr->second, key, value);
        }
        else {
            Data* data = add2cache(key, value);
            map1[key] = data;
            _ccap++;
            if (_ccap>_tcap) {
                int key_removed;
                int ret = removetail(key_removed);
                if (ret==-1)
                    return;
                map1.erase(key_removed);
                _ccap--;
                return;
            }
        }
    }
    

    
};
