#include "../include/list.h"
#include <iostream>
#include<cassert>
int main (){


        // Aux arrays.
        sc::list<int> seq1 { 1, 2, 3, 4, 5 };
        sc::list<int> seq2 { 1, 2, 3, 4, 5 };
        sc::list<int> source { 6, 7, 8, 9, 10 };

        std::cout << ">>> seq1 size is: " << seq1.size() << '\n';
        // Insert at the begining.
        seq1.insert( seq1.begin(), source.begin(), source.end() );
        std::cout << ">>> Seq1 == " << seq1 << std::endl;
        std::cout << ">>> seq1 size is: " << seq1.size() << '\n';
        assert( seq1 == ( sc::list<int>{ 6, 7, 8, 9, 10, 1, 2, 3, 4, 5 } ) );
        std::cout << ">>> Ok\n\n";

        // In the middle
        seq1 = seq2;
        seq1.insert(  seq1.begin() + 2 , source.begin(), source.end() );
        std::cout << ">>> Midele Seq1 == " << seq1 << std::endl;
        std::cout << ">>> seq1 size is: " << seq1.size() << '\n';
        assert( seq1 == ( sc::list<int>{ 1, 2, 6, 7, 8, 9, 10, 3, 4, 5 } ) );
        std::cout << ">>> Ok2\n\n";

        // At the end
        seq1 = seq2;
        seq1.insert( seq1.end(), source.begin(), source.end() );
        std::cout << ">>> Seq1 == " << seq1 << std::endl;
        std::cout << ">>> seq1 size is: " << seq1.size() << '\n';
       
        assert( seq1 == ( sc::list<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } ) );
        std::cout << ">>> Ok3\n\n";


        std::cout << ">>> Passed!\n\n";

        {
        std::cout <<"Erase" << std::endl;
        // Initial vector.
        sc::list<int> seq { 1, 2, 3, 4, 5 };

        // removing a segment from the beginning.
        std::cout <<"entrando na função" << std::endl;

        auto past_last = seq.erase( seq.begin());
        assert( seq == ( sc::list<int>{ 4, 5 } ) );
        assert( seq.begin() == past_last );
        assert( seq.size() == 2 );

        // removing at the middle.
        seq = { 1, 2, 3, 4, 5 };
        past_last = seq.erase( seq.begin() + 1, seq.begin() + 4 );
        assert( seq.begin() + 1 == past_last );
        assert( seq == ( sc::list<int>{ 1, 5 } ) );
        assert( seq.size() == 2 );

        // removing a segment that reached the end.
        seq = { 1, 2, 3, 4, 5 };
        past_last = seq.erase( seq.begin() + 2 , seq.end() );
        assert( seq.end() == past_last );
        assert( seq == ( sc::list<int>{ 1, 2 } ) );
        assert( seq.size() == 2 );

        // removing the entire vector.
        seq = { 1, 2, 3, 4, 5 };
        past_last = seq.erase( seq.begin(), seq.end() );
        assert( seq.end() == past_last );
        assert( seq.empty() );

        std::cout << ">>> Passed!\n\n";
    }
}