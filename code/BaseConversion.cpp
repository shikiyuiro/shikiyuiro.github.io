class BaseConversion{
public:
    string symbol = "0123456789ABCDEF";
    int64_t to_num[128];
    BaseConversion(){
        for(int64_t i = 0; i < symbol.length(); i++) to_num[symbol[i]] = i;
    }
    string from10(int64_t num, int64_t base) {
        if(num == 0) return "0";
        string res = "";
        for(;num > 0; num /= base) res += symbol[num % base];
        reverse(res.begin(), res.end());
        return res;
    }
    int64_t to10(string num, int64_t base) {
        int64_t res = 0;
        for(int64_t i = 0; i < num.length(); ++i) res = res * base + to_num[num[i]];
        return res;
    }
};
