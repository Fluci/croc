#ifndef CROC_RANDOM_REAL_H

#include<iostream>

namespace croc {
class random_real{


friend std::ostream& operator<< (std::ostream &out, const random_real &real);

};
} // croc

#endif // CROC_RANDOM_REAL_H
