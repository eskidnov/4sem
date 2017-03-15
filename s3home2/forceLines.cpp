#include "forceLines.h"

Vector2 ElectricField::findForce(const Charge& q) const {
	Vector2 R(0, 0);	// R = F1 + F2 + ...
	Vector2 r(0, 0);	// Fi = q * qi / r ^ 3 * r
	for (int i = 0; i < charges.size(); ++i) {
		r = q.pos - charges[i].pos;
		R += q.value * charges[i].value / r.squareLen() / r.len() * r;
	}
	return R;
}