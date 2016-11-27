// Created by Felice Serena 2016

#ifndef CROC_RANDOM_REAL_H
#define CROC_RANDOM_REAL_H

#include <bitset>
#include <iostream>
#include <random>
#include <vector>

namespace croc {

/**
* Represents a random real number in `integer + [0, 1)` 
* where `integer` is a signed integer fixed at construction. 
* So-called blocks can be accessed by operator[](), 
* they represent the bits at positions 
* [i*sizeof(block), (i+1)*sizeof(block)-1].
* If a block i is read but didn't exist before,
* it will be generated randomly. 
* Every block up to i will also be generated.
*
* Motivation: This class is written to be 
* used in an implementation of a treap as key values.
* This way, random search trees can easily be created.
*
* THIS CLASS IS NOT INTENDED FOR MATHEMATICAL USE.
*
* Because of that, this class doesn't support any arithmetic operations
* and hence the strange definition of `integer + [0, 1)` (strange for negative integers).
*
* Equality
* If and only if they are the same object
* (pointer comparison: `&real1 == &real2`).
*/
template <class random_engine = std::mt19937>
class random_real{

public:
	/// Signed integer/characteristic: everything in front of the dot is fixed at construction.
	typedef const int integer_type;
	/// Fractional-part/mantissa: the single bits are stored in blocks, they have type `block_type`.
	typedef uint32_t block_type;
	/// Type of index that is used to access blocks.
	typedef size_t index_type;
	
	/**
	* All random reals use the same random number generator to get their 
	* random bits. Use this function to set a new one. A random number
	* generator needs to support `operator()`.
	* 
	* @param re The new random engine to use.
	*/
	static void set_random_engine(const random_engine re) noexcept {
		r_engine = re;
	}

private:
	thread_local static random_engine r_engine;
	std::vector<block_type> blocks;
	integer_type integer;

public:
	/**
	* Create a `random_real` with a characteristic of value `int_part`.
	* The integer part remains fixed.
	*
	* @param int_part The constructed random real will start with `int_part`
	* followed by a dot (.) and the random fraction bits
	**/
	explicit random_real(integer_type int_part = 0) noexcept : integer(int_part) {
		// empty
	}

	/**
	* Integer part of random real.
	*
	* @return integer part set at construction
	**/
	integer_type get_integer() const noexcept {
		return integer;
	}
	/**
	* Creates all blocks with `random_engine` until block at `i` exists.
	*
	* @param i requested block index
	* @return block at index `i`
	*/
	block_type operator[](const index_type i) noexcept {
		for(auto j = blocks.size(); j <= i; j += 1) {
			blocks.push_back(r_engine());
		}
		return blocks[i];
	}

	/**
	* @return How many blocks are already computed and stored.
	*/
	index_type size() const noexcept {
		return blocks.size();
	}

	/**
	* Checks if object is passed to itself, if not, new blocks are generated
	* until `operator<()` or `operator>()` is true.
	* 
	* @param other The `random_real` this `random_real` should be compared to.
	* @return
	* -1: `(*this) < other`\n
	* 0: `this == &other`\n
	* 1: `(*this) > other`
	*/

	int compareTo(random_real& other) noexcept;

	/**
	 * Print all available bits as `<integer>.01010101`.
	 *
	 * Careful: `-1.101` has to be interpreted as `-1 + 0.101`
	 *
	 * @param out output stream to write to
	 * @param real random_real to write
	 * @return the output stream
	 */
	friend std::ostream& operator<< (std::ostream& out, const random_real& real) noexcept {
		out << real.get_integer() << ".";
		for(auto it : real.blocks) {
			out << std::bitset<sizeof(random_real::block_type)*8>(it);
		}
		return out;
	}
};


/** \relates random_real
 * True if and only if both numbers are the same object.
 *
 *
 * @param lhs left hand-side
 * @param rhs right hand-side
 * @return `true` if `&lhs == &rhs`
 */
template <class T>
bool operator==(const random_real<T>& lhs, const random_real<T>& rhs) noexcept {
	return &lhs == &rhs;
}


/** \relates random_real
 * Negation of equality `operator==()`, no new blocks are generated.
 *
 * @param lhs left hand-side
 * @param rhs right hand-side
 * @return `true` if `&lhs != &rhs`
 */
template <class T>
bool operator!=(const random_real<T>& lhs, const random_real<T>& rhs) noexcept {
	return &lhs != &rhs;
}


/** \relates random_real
 * Same definition for equality as `operator==()`.
 * New blocks might be generated to decide `operator<()` or `operator>()`.
 *
 * @param lhs left hand-side
 * @param rhs right hand-side
 * @return `true` if `lhs` equal or smaller than `rhs`, `false` otherwise
 */
template <class T>
bool operator<=(random_real<T>& lhs, random_real<T>& rhs) noexcept {
	return lhs.compareTo(rhs) <= 0;
}

/** \relates random_real
 * Same definition for equality as `operator==()`.
 * New blocks might be generated.
 *
 * @param lhs left hand-side
 * @param rhs right hand-side
 * @return `false` if `lhs` strictly smaller than `rhs`, `true` otherwise
 */
template <class T>
bool operator>=(random_real<T>& lhs, random_real<T>& rhs) noexcept {
	return lhs.compareTo(rhs) >= 0;
}


/** \relates random_real
 * Generates new blocks until `x < y` or `y < x`.
 * Only exception is when `this == &other` (object compared to itself),
 * then no new blocks are created and `false` is returned.
 *
 * @param lhs left hand-side
 * @param rhs right hand-side
 * @return `true` if `rhs` is larger, `false` if `rhs` is smaller; `false` if `lhs == rhs`
 */
template <class T>
bool operator<(random_real<T>& lhs, random_real<T>& rhs) noexcept {
	return lhs.compareTo(rhs) == -1;
}

/** \relates random_real
 * Similar to `operator<()`.
 *
 * @param lhs left hand-side
 * @param rhs right hand-side
 * @return `true` if `rhs` is smaller, `false` if `rhs` is larger; `false` if `lhs == rhs`
 */
template <class T>
bool operator>(random_real<T>& lhs, random_real<T>& rhs) noexcept {
	return lhs.compareTo(rhs) == 1;
}

// method implementations


template <class T>
int random_real<T>::compareTo(random_real<T>& other) noexcept {
	if(this == &other) {
		return 0;
	}
	if(integer != other.integer) {
		return integer < other.integer ? -1 : 1;
	}
	const index_type common = std::min(size(), other.size());
	for(index_type i = 0; i < common; i += 1) {
		const block_type l = blocks[i];
		const block_type r = other.blocks[i];

		if(l != r) {
			if(l < r) {
				return -1;
			}
			// l > r
			return 1;
		}
	}

	// l == r so far, so let us generate some new blocks to decide

	for(index_type i = common; true; i += 1) {
		const block_type l = (*this)[i];
		const block_type r = other[i];
		if(l != r) {
			if(l < r) {
				return -1;
			}
			// l > r
			return 1;
		}
	}
}
template <class T> thread_local T random_real<T>::r_engine{};

}  // namespace croc

#endif  // CROC_RANDOM_REAL_H
