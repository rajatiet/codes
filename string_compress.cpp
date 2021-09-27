class StringIterator {
    string _str;
    int _next_offset;
    int _tchar_cnt;
    int _cchar_cnt;
    vector<char> _chars;
    vector<int> _ccnts;
    int _accumulated_char_cnt;
    
public:
    StringIterator(string compressedString) {
        _str =  compressedString;
        _next_offset = 0;
        stringstream ss (_str);
        char ch;
        int cnt;
        _tchar_cnt = 0;
        _cchar_cnt = 0;
        _accumulated_char_cnt = 0;
        //parse the input string
        while (ss.good()) {
            ss >> ch >> cnt;
            _chars.push_back(ch);
            _ccnts.push_back(_accumulated_char_cnt+cnt);
            _accumulated_char_cnt = _accumulated_char_cnt+cnt;
            _tchar_cnt++;
        }
    }
    
    char next() {
        if (!hasNext())
            return ' ';

        if (_ccnts[_cchar_cnt] <= _next_offset) {
            _cchar_cnt++; 
        }
        
        if (_accumulated_char_cnt == _next_offset)
            return ' ';

        char ch = _chars[_cchar_cnt];
        _next_offset++;

        return ch;
    }
    
    bool hasNext() {
        if (!_chars.size())
            return false;
        if (_accumulated_char_cnt <= _next_offset)
            return false;

        return true;
    }
};

/**
 * Your StringIterator object will be instantiated and called as such:
 * StringIterator* obj = new StringIterator(compressedString);
 * char param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
