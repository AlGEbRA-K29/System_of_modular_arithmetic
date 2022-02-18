//
// Created by fail on 2/18/22.
//

#ifndef LAB_MOD_BIGINT_H
#define LAB_MOD_BIGINT_H

#include <vector>
#include <cstdint>
#include <ostream>

class modular_bigint {
public:
    [[nodiscard]] bool is_positive() { return sign; }

    friend std::ostream& operator<<(std::ostream& os, const modular_bigint& d) {
        if(d.data.empty()) {
            os << "0";
            return os;
        }

        if(!d.sign) os << "-";

    }

    friend modular_bigint operator+(const modular_bigint& lhs, const modular_bigint& rhs) {

    }
private:
    void trim() {
        while(!data.empty() && *data.rbegin() == 0) data.pop_back();
    }

    std::vector<std::uint32_t> data;
    bool sign = true;
};

#endif //LAB_MOD_BIGINT_H
