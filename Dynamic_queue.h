
/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -Alex Lui, Tewoldebrhan Hagos, Khachatur Mirijanyan
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "ece250.h"
#include <cmath>
#include "Exception.h"

template <typename Type>
class Dynamic_queue {
	private:
		int initial_capacity;
		int array_capacity;
		Type *array;
		int ihead;
		int itail;
		int entry_count;
		// other integer member variables, as necessary

	public:
		Dynamic_queue( int = 10 );
		Dynamic_queue( Dynamic_queue const & );
		~Dynamic_queue();

		Type head() const;
		int size() const;
		bool empty() const;
		int capacity() const;
        int head_position() const;
        int tail_position() const;

		void swap( Dynamic_queue & );
		Dynamic_queue &operator=( Dynamic_queue );
		void enqueue( Type const & );
		Type dequeue();
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Dynamic_queue<T> const & );
};

template <typename Type>
Dynamic_queue<Type>::Dynamic_queue( int n ):
initial_capacity( std::max( n, 1 ) ),
array_capacity( initial_capacity ),
array( new Type[initial_capacity] ),
ihead( 0 ),
itail( initial_capacity - 1 ),
entry_count( 0 ) {
	// Enter your implementation here.
    
    if (n<1)
    {
        initial_capacity=1;
    }
    else
    {
        initial_capacity=n;
    }
}

template <typename Type>
Dynamic_queue<Type>::Dynamic_queue( Dynamic_queue const &queue ):
initial_capacity( queue.initial_capacity ),
array_capacity( queue.array_capacity ),
array( new Type[array_capacity] ),
ihead( queue.ihead ),
itail( queue.itail ),
entry_count( queue.entry_count ) {
	// The above initializations copy the values of the appropriate
	// member variables and allocate memory for the data structure;
	// however, you must still copy the stored objects.

	// Enter your implementation here.
    for (int i=0; i<array_capacity; ++i)
        array[i]=queue.array[i];
    
}

template <typename Type>
Dynamic_queue<Type>::~Dynamic_queue() {
	// Enter your implementation here.
    delete [] array;
}

template <typename Type>
int Dynamic_queue<Type>::size() const {
	// Enter your implementation here.
    
	return entry_count;
}

template <typename Type>
int Dynamic_queue<Type>::capacity() const {
	// Enter your implementation here.
	return array_capacity;
}

template <typename Type>
bool Dynamic_queue<Type>::empty() const {
	// Enter your implementation here.
	return entry_count==0;
}

template <typename Type>
Type Dynamic_queue<Type>::head() const {
	// Enter your implementation here.
	if (entry_count==0)
        throw underflow();
    else
        return array[ihead];
}

template <typename Type>
void Dynamic_queue<Type>::swap( Dynamic_queue<Type> &queue ) {
	std::swap( initial_capacity, queue.initial_capacity );
	std::swap( array_capacity, queue.array_capacity );
	std::swap( array, queue.array );
	std::swap( ihead, queue.ihead );
	std::swap( itail, queue.itail );
	std::swap( entry_count, queue.entry_count );
}

template <typename Type>
Dynamic_queue<Type> &Dynamic_queue<Type>::operator=( Dynamic_queue<Type> rhs ) {
	swap( rhs );
	
	return *this;
}

template <typename Type>
void Dynamic_queue<Type>::enqueue( Type const &obj ) {
	// Enter your implementation here.

    
    if (array_capacity==entry_count)
    {
        //copy to a new array
        Type *temp = new Type[array_capacity*2];
        
        if (ihead>itail)
        {
            for (int i=0; i<=itail; ++i)
                temp[i]=array[i];
            for (int i=ihead; i<array_capacity; ++i)
                temp[i+array_capacity]=array[i];
            ihead=ihead+array_capacity;
        }
        else
        {
            for (int i=0; i<array_capacity; i++)
                temp[i]=array[i];
        }
        delete [] array;
        array=temp;
        array_capacity*=2;
    }
    
    
    ++itail;
    
    itail=itail%capacity();
    array[itail]=obj;
    ++entry_count;
    
}

template <typename Type>
int Dynamic_queue<Type>::head_position() const
{
    return ihead;
}

template <typename Type>
int Dynamic_queue<Type>::tail_position() const
{
    return itail;
}

template <typename Type>
Type Dynamic_queue<Type>::dequeue() {
	// Enter your implementation here.
    if (empty())
    {
        throw underflow();
    }
    
    Type t = array[ihead];
    ++ihead;
    --entry_count;
    if (entry_count<=array_capacity/4 && array_capacity/2>initial_capacity)
    {
        Type* temp = new Type[array_capacity / 2];
        
        for(int i = ihead; i <= itail; ++i, i = i % array_capacity)
        {
            temp[i % (array_capacity / 2)] = array[i];
        }
        
        ihead = ihead % (array_capacity / 2);
        itail = itail % (array_capacity / 2);
        
        delete[] array;
        array = temp;
        array_capacity/=2;
    }
    ihead = ihead % (array_capacity);
    itail = itail % (array_capacity);
    
    return t;
    

}

template <typename Type>
void Dynamic_queue<Type>::clear() {
	// Enter your implementation here.
    //while (!empty())
    while (entry_count>1)
    {
        dequeue();
    }
    array_capacity=initial_capacity;
}

// You can modify this function however you want:  it will not be tested

template <typename Type>
std::ostream &operator<<( std::ostream &out, Dynamic_queue<Type> const &queue ) {
	// I don't know how you are implementing your queue so I cannot print it.
	// If you want, you can print whatever you want here and then call cout
	// in the driver.

	// Remember to redirect to out, e.g.,
	//      out << "Hello!";

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
