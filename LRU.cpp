class LRUCache {
public:
    LRUCache(int capacity) {
        _capacity=capacity;
    }
    
    int get(int key) {
        auto umit=_hashMap.find(key);
        if(umit!=_hashMap.end()){
            LRU_LST_IT listIt=umit->second;
            int value=listIt->second;
            _listCache.splice(_listCache.end(),_listCache,listIt);
            //连接左右，取出值放在后面
            //_listCache.erase(listIt);
            //_hashMap.erase(key);
            //_listCache.push_back(make_pair(key,value));
            //_hashMap[key]=--_listCache.end();
            return value; 
        }else{
            return -1;
        }

    }
    
    void put(int key, int value) {
        auto umit=_hashMap.find(key);
        if(umit!=_hashMap.end()){
            //auto endit=_listCache.end();
            LRU_LST_IT ltIt=umit->second;
            ltIt->second=value;
            _listCache.splice(_listCache.end(),_listCache,umit->second);
            
        }else{
            if(_listCache.size()==_capacity){
                _hashMap.erase(_listCache.front().first);
                _listCache.pop_front();
            }

            _listCache.push_back(make_pair(key,value));

            _hashMap[key]=--_listCache.end();    
        }
    }
private:
    typedef list<std::pair<int,int>>::iterator  LRU_LST_IT;
    typedef std::pair<int,int> LRU_LST; 

    list<LRU_LST> _listCache;
    unordered_map<int,LRU_LST_IT> _hashMap; 
    int _capacity;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
