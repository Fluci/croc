// Created by Felice Serena 2016

#ifndef CROC_RANDOM_REAL_H
#define CROC_RANDOM_REAL_H

#include <iostream>
#include <random>
#include <vector>

namespace croc {

/**
* Represents a random real number in [0, 1]. 
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
* Equality
* The equality of a random real number is in some way not even 
* reasonable (since you can just generate new blocks
* until the equality no longer holds). 
* Though it is an interesting exercise to define a somewhat
* reasonable equality and it certainly is more challenging than
* just returning false.
* The semantics of equality is 
* "equal as far as I can tell without generating new blocks".
*/
template <class random_engine = std::mt19937>
class random_real{

public:
	/// the single bits are stored in blocks, they have type block_type
	typedef uint32_t block_type;
	/// type of index that is used to access blocks
	typedef size_t index_type;
	
	/**
	* All random reals use the same random number generator to get their 
	* random bits. Use this function to set a new one. A random number
	* generator needs to support operator().
	* 
	* @param re The new random engine to use.
	*/
	static void set_random_engine(const random_engine re) throw() {
		r_engine = re;
	}

private:
	static random_engine r_engine;
	std::vector<block_type> blocks;

public:
	/**
	* creates all blocks with random_engine until block at i exists
	*
	* @param i requested block index
	* @return block at index i
	*/
	block_type operator[](const index_type i) throw() {
		for(int j = blocks.size(); j <= i; j += 1) {
			blocks.push_back(r_engine());
		}
		return blocks[i];
	}

	/**
	* @return how many blocks are already computed and stored
	*/
	index_type size() const throw() {
		return blocks.size();
	}

	/**
	* Generates new blocks until x < y or y < x.
	*
	* @param other random_real to compare against
	* @return true if other is larger, false if other is smaller
	*/
	bool operator<(random_real &other) throw() {
		// I'm not totally sure about the implementation.
		// Possible, that there is a massively more efficient implementation than this.

		const int res = compareTo(other);
		
		if(res != 0) {
			if(res == -1) {
				// l < r
				return true;
			}
			// l > r
			return false;
		}
		
		// l == r so far, so let us generate some new blocks to decide
		
		const int common = std::min(size(), other.size());
		
		for(index_type i = common; true; i += 1) {
			const block_type l = (*this)[i];
			const block_type r = other[i];
			if(l != r) {
				if(l < r) {
					return true;
				}
				// l > r
				return false;
			}
		}
	}

	/**
	* As operator<(), but inverts result.
	*
	* @param other This is compared to random_real.
	* @return true if other is smaller, false if other is larger
	*/
	bool operator>(random_real &other) throw() {
		return other < (*this);
	}

	/**
	* compares the first min(size(), other.size()) blocks.
	*
	* @param other The random_real this random_real should be compared to.
	* @return
	* -1: (*this) < other\n 
	* 0: (*this) == other\n
	* 1: (*this) > other
	*/
	int compareTo(const random_real &other) const throw() {
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
		// l == r
		return 0;
	}

	/**
	* Same definition for equality as operator==(). 
	* If their size() is unequal, 
	* then operator<() is applied and new blocks might be generated.
	*
	* @param other The other random_real to compare against.
	* @return true if equal or this smaller than other, false otherwise
	*/
	bool operator<=(random_real &other) throw() {
		if(size() != other.size()) {
			return (*this) < other;
		}
		return compareTo(other) <= 0;
	}

	/**
	* Same definition for equality as operator==().
	* If their size() is unequal,
	* then (*this) > other is performed 
	* and new blocks might be generated.
	*
	* @param other random_real to compare against
	* @return false if this strictly smaller than other, true otherwise
	*/
	bool operator>=(random_real &other) throw() {
		if(size() != other.size()) {
			return other < (*this);
		}
		return compareTo(other) >= 0;
	}

	/**
	* True if and only if both numbers have same size 
	* and all existing blocks are equal. No new blocks are generated.
	*
	* @param other random_real to check
	* @return true if equal
	*/
	bool operator==(const random_real &other) const throw() {
		if(size() != other.size()) {
			return false;
		}
		return compareTo(other) == 0;
	}

	/**
	* negation of equality, no new blocks are generated
	* 
	* @param other Other random_real
	* @return true if size() != other.size() or there is any unequal bits
	*/
	bool operator!=(const random_real &other) const throw() {
		return !(other == (*this));
	}

	/**
	* Print all available bits as "0.01010101".
	* 
	* @param out output stream to write to
	* @param real random_real to write
	* @return the output stream
	*/
	friend std::ostream&
    operator<< (std::ostream &out, const random_real &real) throw() {
		out << "0.";
		for(auto it : real.blocks) {
			out << std::bitset<sizeof(block_type)*8>(it);
		}
		return out;
	}
};

template <class T>
T random_real<T>::r_engine = T();

}  // namespace croc

#endif  // CROC_RANDOM_REAL_H
