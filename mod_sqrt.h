#ifndef MOD_SQRT_H
#define MOD_SQRT_H

#include "montgomery_form.h"
#include <optional>

bigint pow_mnt(const bigint& n, const bigint& power, const bigint& p);

std::optional<pair<bigint, bigint> > sqrt(const bigint& n, const bigint& p);
#endif // MOD_SQRT_H
