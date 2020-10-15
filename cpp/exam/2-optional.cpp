template<typename T>
class optional {
    T _value;
    bool _has_value;
public:
    optional() : _has_value(false) {}


    T& value() { 
        if (_has_value) return _value
    }
    constexpr explicit operator bool() const noexcept {
        return _has_value;
    }
    bool has_value(){
        return _has_value;
    }
};