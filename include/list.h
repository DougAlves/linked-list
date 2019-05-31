
#define LINKED_LIST

#include <cstdlib> // size_t
#include <ostream>
#include <initializer_list>
#include<iostream>
namespace sc
{
    template <typename T>
    class list
    {
        private:
        struct node
        {
            T data;
            node* next;
            node* prev;

            bool operator==(node & rhs){
                return data==rhs.data & next == rhs.next && rhs.prev == prev;
            }
        };

        public:
        class iterator
            {
                public:
                    typedef T& reference; //!< Alias para uma referência.
                    typedef std::ptrdiff_t difference_type;
                    //! Identificar a categoria do iterador para algoritmos do STL.
                    typedef std::bidirectional_iterator_tag iterator_category;
                    //=== Private data
                private:
                    //=== Interface pública.
                public:
                    node* ptr;
                    iterator( node * pt = nullptr ) : ptr{ pt }
                    { /* empty */ }
                    /// it1 = it2;
                    iterator(const iterator & other){
                        this->ptr = other.ptr;
                    }
                    iterator& operator=( const iterator& rhs )
                    {
                        ptr = rhs.ptr;
                        return *this;
                    }
                    /// *it = x;
                    T& operator*(void)
                    {
                        return ptr->data;
                    }
                    /// x = *it;
                    const T& operator*(void) const
                    {
                        return ptr->data;
                    }
                    /// ++it pré incremento.
                    iterator operator++(void)
                    {
                        //++ptr;
                        //return *this;
                        // Retorna um novo iterador que aponta para o próximo endereço.

                        ptr = ptr->next;

                        return iterator(ptr);
                    }
                    /// it++ pós incremento.
                    iterator operator++(int)
                    {
                        ptr = ptr->next;
                        return ptr->prev ;
                    }
                    /// --it pré decremento.
                    iterator operator--(void)
                    {
                        return iterator ( ptr->prev );
                    }
                    /// it-- pós decremento.
                    iterator operator--(int)
                    {
                        // Opção 1:
                        iterator temp( ptr ); // Cria um iterator temporário com o endereço atual.
                        ptr = ptr->prev;
                        return temp;
                    }
                    
                    /// Comparação it == it2
                    bool operator==( const iterator &it ) const
                    { 
                        //std::cout <<"ENDEREÇO DO THIS: "<< this->ptr<<std::endl;
                        //std::cout <<"ENDEREÇO DO PARAMETRO : "<<it.ptr << std::endl;
                        return this->ptr == it.ptr ; /* Devem apontar pro mesmo endereço. */ 
                    }
                    /// Comparação it != it2
                    bool operator!=( const iterator &it ) const
                    { 
                        bool equal = *this == it;
                        //std::cout << equal << std::endl;
                        //std::cout << !equal <<std::endl;
                        return  !equal ; /* Não Devem apontar pro mesmo endereço. */ 
                    }
                    /// it = it1 - it2;
                    
                    iterator operator+( int a  )
                    {
                        iterator aux (ptr);
                        int i = 0;
                        while (i < a){
                            aux++;
                            i++;
                        }
                        return aux;
                    }
                    iterator operator-( int a  )
                    {
                        iterator aux (ptr);
                        int i = 0;
                        while (i < a){
                            aux--;
                            i++;
                        }
                        return aux;
                    }
            };
                
        private:
        node* tail;
        size_t SIZE;
        public:
        node* head;
        list()
        {
            head = new node();
            tail = new node();
            head->next = tail;
            tail->prev = head;
            head->prev = tail->next = nullptr;
            SIZE = 0;
        }
        list( const list &other){
            head = new node();
            tail = new node();
            head->next = tail;
            tail->prev = head;
            head->prev = tail->next = nullptr;
            SIZE = 0;
            node* it = other.tail->prev;
            
            while (it != other.head){
                this->push_front(it->data);
                it = it->prev;
            }
        }

        list(const std::initializer_list<T>& ilist)
        {
            head = new node();
            tail = new node();
            head->next = tail;
            tail->prev = head;
            SIZE = 0;
            head->prev = tail->next = nullptr;
            auto it = ilist.begin();
            for (; it != ilist.end() ; it++){
                push_back( *it );
            }
        }
        
        list(size_t sz)
        {
            head = new node();
            tail = new node();
            head->next = tail;
            tail->prev = head;
            head->prev = tail->next = nullptr;
            T e;
            for (int i =0; i< sz; i++){
                push_back(e);
            }
            SIZE = sz;
        }

        list(iterator first, iterator last)
        {
            head = new node();
            tail = new node();
            head->next = tail;
            tail->prev = head;
            head->prev = tail->next = nullptr;
            SIZE = 0;
            while (first != last){
                push_back(*first);
                first++;
            }

        }
        ~list(){
            clear();
            delete head;
            delete tail;
        }


        void push_front( const T& data)
        {
            node* target = new node();
            target->data = data;
            target->prev = head;
            target->next = head->next;
            head->next->prev = target;
            head->next = target;
            SIZE++;
        }

        void push_back( const T& data)
        {
            node* target = new node();
            target->data = data;
            target->next = tail;
            target->prev = tail->prev;
            tail->prev->next = target;
            tail->prev = target;
            SIZE++;
        }

        void clear(){
            if (head->next == tail) return;
            while (head->next != tail){
                pop_front();
            }
            SIZE = 0;
        }
        size_t size()
        {
            return SIZE;
        }

        bool empty(){
            return  head->next == tail;
        }
        
        void pop_front()
        {
            if (head->next == tail) return;
            node* target = head->next;
            head->next->next->prev = head;
            head->next = head->next->next;
            delete target;
            SIZE--;    
        }
        void pop_back()
        {
            if (head->next == tail) return;
            node* target = tail->prev;
            tail->prev->prev->next = tail;
            tail->prev = tail->prev->prev;
            delete target;
            SIZE--;
        }

        void insert(iterator pos, T value)
        {
            node* target = new node();
            target->data = value;
            
            target->prev = pos.ptr->prev;
            target->next = pos.ptr;
            pos.ptr->prev = target;
            target->prev->next = target; 
            
            SIZE++;
        }

        void insert( iterator pos, iterator first, iterator  last )
        {   
            while (first != last)
            {
                insert(pos, *first);
                first++;
            }
        }

        void insert(iterator pos, std::initializer_list<T> ilist)
        {
            auto it =  ilist.begin();
            while (it != ilist.end()){
                insert(pos, *it++);
            }

        }

        iterator erase(iterator pos)
        {
            node* to_delete = pos.ptr;
            std::cout <<"Erase" << std::endl;
            
            to_delete->prev->next = to_delete->next;
            to_delete->next->prev =  to_delete->prev;
            delete to_delete;
            SIZE--;
            return pos;
        }

        iterator erase( iterator first, iterator last)
        {
            iterator pos = first;
            while (first != last){
                erase(++first - 1 );
            }

            return last - 1;
        }

        const T& back() const{
            if (head->next == tail) 
                throw "[]";
            return tail->prev->data;
        }

        const T& front() const{
            if (head->next == tail) 
                throw "[]";
            return head->next->data;
        }

        iterator begin (){
            return iterator(head->next);
        }

        iterator end(){
            return iterator(tail);
        }

        list& operator=(list & rhs)
        {
            clear();
            node* it = rhs.head->next;
            while (it != rhs.tail){
                push_back(it->data);
                it = it->next;
            }
            return *this;

        }

        list& operator=(const std::initializer_list<T> ilist){
            clear();
            auto it = ilist.begin();
            while (it != ilist.end()){
                push_back(*it);
            }
            return *this;
        }

        bool  operator==(const list &  rhs){
            if(rhs.SIZE != SIZE) return false;
            
            iterator it (head->next);
            iterator it2( rhs.head->next) ;
            while(it != tail)
            {
                if (*it != *it2)
                {
                    return false;
                }
                it ++;
                it2 ++;
            }
            return true;
        }

        bool operator!=(const list & rhs){
            return not (*this == rhs);
        }

        friend std::ostream& operator<<(std::ostream & os, const list &list){
            node* it;
            it = list.head->next;
            os<< "[ ";
            while(it != list.tail){
                os << it->data << " ";
                it = it->next;
            }
            os<<"]";
            return os;
        };

    };

};