class Solution {
public:
    int nthUglyNumber(int n) {

        
        if (n<=6)
            return n;
               
        set<long long int> s1;
        s1.insert(1);
        int cnt=0;
        long long int x;
        while(!s1.empty()) {
            x = *s1.begin();
            s1.erase(s1.begin());
            cnt++;
            if (cnt==n)
                return x;
            s1.insert(x*2);
            s1.insert(x*3);
            s1.insert(x*5);
        }
        return x;
    }
};
