/*
 * d962.cpp
 *
 *  Created on: 2011/12/6
 *      Author: wush
 */

#define HAND_MAX 5000
#define SIDE_MAX 50000

#include <iostream>
#include <vector>
#include <algorithm>

typedef unsigned long long Count;
typedef unsigned long long Location;

struct Spaghetti {
	Location _x;
	Location _y;
	Location _z;

	const Count zero_position() const {
		if (!_x) {
			return 1;
		}
		if (!_y) {
			return 2;
		}
		if (!_z) {
			return 3;
		}
		return 4;
	}
};

class MatchXY {
	const Spaghetti* _ref;
public:
	const bool operator()(const Spaghetti& pred) {
		return _ref->_z == pred._z;
	}
	void set_ref(const Spaghetti& src) {
		_ref = &src;
	}
};

class MatchXZ {
	const Spaghetti* _ref;
public:
	const bool operator()(const Spaghetti& pred) {
		return _ref->_y == pred._y;
	}
	void set_ref(const Spaghetti& src) {
		_ref = &src;
	}

};

class MatchYZ {
	const Spaghetti* _ref;
public:
	const bool operator()(const Spaghetti& pred) {
		return _ref->_x == pred._x;
	}
	void set_ref(const Spaghetti& src) {
		_ref = &src;
	}
};

const bool operator<(const Spaghetti& a, const Spaghetti& b) {
	if (a.zero_position() == b.zero_position()) {
		if (a._x == b._x) {
			if (a._y == b._y) {
				return a._z < b._z;
			} else {
				return a._y < b._y;
			}
		} else {
			return a._x < b._x;
		}
	} else {
		return a.zero_position() < b.zero_position();
	}
}

const bool operator==(const Spaghetti& a, const Spaghetti& b) {
	return a._x == b._x && a._y == b._y && a._z == b._z;
}

int main() {
	Count quiz_size;
	std::cin >> quiz_size;
	std::vector<Count> N(quiz_size, 0), M(quiz_size, 0), H(quiz_size, 0), S(
			quiz_size, 0);
	std::vector<std::vector<Spaghetti> > hand_location;
	hand_location.resize(quiz_size);
	MatchXY matchxy;
	MatchXZ matchxz;
	MatchYZ matchyz;
	for (Count i = 0; i < quiz_size; i++) {
		std::cin >> N[i] >> M[i] >> H[i];
		std::cin >> S[i];
		hand_location[i].resize(S[i]);
		for (Count j = 0; j < S[i]; j++) {
			std::cin >> hand_location[i][j]._x >> hand_location[i][j]._y
					>> hand_location[i][j]._z;
		}
	}

	for (Count i = 0; i < quiz_size; i++) {
#ifdef WUSHDEBUG
		std::vector<Spaghetti> zero_coordinate;
#endif
		std::sort(hand_location[i].begin(), hand_location[i].end());
#ifdef WUSHDEBUG
		for (Count j = 0; j < hand_location[i].size(); j++) {
			std::cout << hand_location[i][j]._x << " " << hand_location[i][j]._y
					<< " " << hand_location[i][j]._z << std::endl;
		}
#endif
		std::vector<Spaghetti>::iterator index(hand_location[i].begin());
		while (index + 1 != hand_location[i].end()) {
			if (*index == *(index + 1)) {
				hand_location[i].erase(index + 1);
			} else {
				index++;
			}
		}
		Count taken_man(0);
		Count X_end(hand_location[i].size()), Y_end(hand_location[i].size());
		for (Count j = 0; j < hand_location[i].size(); j++) {
			if (!hand_location[i][j]._x) {
				taken_man += N[i];
			} else {
				if (X_end == hand_location[i].size()) {
					X_end = j;
				}
				if (!hand_location[i][j]._y) {
					taken_man += M[i];
					std::vector<Spaghetti>::iterator find_result(
							hand_location[i].begin());
					Count same_x(0);
					matchxy.set_ref(hand_location[i][j]);
					while (find_result != hand_location[i].begin() + X_end) {
						find_result = std::find_if(find_result,
								hand_location[i].begin() + X_end, matchxy);
						if (find_result != hand_location[i].begin() + X_end) {
							same_x++;
							find_result++;
						}
					}
					taken_man -= same_x;
				} else {
					if (Y_end == hand_location[i].size()) {
						Y_end = j;
					}
					taken_man += H[i];
					matchxz.set_ref(hand_location[i][j]);
					matchyz.set_ref(hand_location[i][j]);
					Count same_x(0), same_y(0), same_xy(0);
					std::vector<Spaghetti> same_y_list;
					std::vector<Spaghetti>::iterator find_result(
							hand_location[i].begin());
					while (find_result != hand_location[i].begin() + X_end) {
						find_result = std::find_if(find_result,
								hand_location[i].begin() + X_end, matchxz);
						if (find_result != hand_location[i].begin() + X_end) {
							same_y++;
							same_y_list.push_back(*find_result++);
						}
					}
					while (find_result != hand_location[i].begin() + Y_end) {
						find_result = std::find_if(find_result,
								hand_location[i].begin() + Y_end, matchyz);
						if (find_result != hand_location[i].begin() + Y_end) {
							same_x++;
							matchxy.set_ref(*find_result++);
							if (std::find_if(same_y_list.begin(),
									same_y_list.end(), matchxy)
									!= same_y_list.end()) {
								same_xy++;
							}
						}
					}
					taken_man += same_xy;
					taken_man -= same_x;
					taken_man -= same_y;
				}

			}
		}
		std::cout << N[i] * M[i] * H[i] - taken_man << std::endl;
	}
}

/*
 // Slow version
 #include <cstring>
 #include <bitset>

 int locator(int a, int b, int c)
 {
 return a * 5000 * 5000 + b * 5000 + c;
 }

 int main()
 {
 unsigned char* tower(NULL);
 tower = (unsigned char*) malloc(5000 * 5000 * 5000);
 if (tower == NULL)
 {
 std::cout << "allocate fail" << std::endl;
 return -1;
 }
 Count quiz_size;
 std::cin >> quiz_size;
 std::vector<Count> N(quiz_size,0), M(quiz_size,0), H(quiz_size,0), S(quiz_size,0);
 std::vector<std::vector<Spaghetti> > hand_location;
 hand_location.resize(quiz_size);
 for (Count i = 0;i < quiz_size;i++)
 {
 std::cin >> N[i] >> M[i] >> H[i];
 std::cin >> S[i];
 hand_location[i].resize(S[i]);
 for (Count j = 0;j < S[i];j++)
 {
 std::cin >> hand_location[i][j]._x >> hand_location[i][j]._y >> hand_location[i][j]._z;
 }
 }

 //	std::cout << quiz_size << std::endl;
 for (Count quiz_label = 0;quiz_label < quiz_size;quiz_label++)
 {
 memset(tower, 1, 5000 * 5000 * 5000);
 for (Count i = 0;i < hand_location[quiz_label].size();i++)
 {
 //			std::cout << "test" << std::endl;
 if (!hand_location[quiz_label][i]._x)
 {
 for (Count j = 0;j < N[quiz_label];j++)
 {
 tower[locator(j, hand_location[quiz_label][i]._y - 1,hand_location[quiz_label][i]._z - 1)] = 0;
 }
 continue;
 }
 if (!hand_location[quiz_label][i]._y)
 {
 for (Count j = 0;j < M[quiz_label];j++)
 {
 tower[locator(hand_location[quiz_label][i]._x - 1,j,hand_location[quiz_label][i]._z - 1)] = 0;
 }
 continue;
 }
 if (!hand_location[quiz_label][i]._z)
 {
 for (Count j = 0;j < H[quiz_label];j++)
 {
 tower[locator(hand_location[quiz_label][i]._x - 1,hand_location[quiz_label][i]._y - 1,j)] = 0;
 }
 continue;
 }
 }
 Count retval(0);
 for (Count i = 0;i < 5000 * 5000 * 5000;i++)
 {
 retval += tower[i];
 }
 retval -= (5000 * 5000 * 5000 - N[quiz_label] * M[quiz_label] * H[quiz_label]);
 std::cout << retval << std::endl;
 }

 return 0;

 }
 */
