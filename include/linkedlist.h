
#define LINKED_LIST

#include <cstdlib> // size_t
#include <ostream>
#include <initializer_list>
namespace ls
{
    template <typename T>
    class list
    {
        private:
        class node
        {
            public:
            T data;
            node* next;
            node* prev;

        };
        
        private:
        node* head;
        node* tail;
        size_t size;
        public:

        list()
        {
            head = new node();
            tail = new node();
            head->next = tail;
            tail->prev = head;
            head->prev = tail->next = nullptr;
            size = 0;
        }
        list( const list &other){
            head = new node();
            tail = new node();
            head->next = tail;
            tail->prev = head;
            head->prev = tail->next = nullptr;
            size = 0;
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
            head->prev = tail->next = nullptr;
            size = 0;
            for (size_t i = 0 ; i + ilist.begin() != ilist.end() ; i++){
                push_back( *(ilist.begin() + i) );
            }
        }

        void push_front( const T& data)
        {
            node* target = new node();
            target->data = data;
            target->prev = head;
            target->next = head->next;
            head->next->prev = target;
            head->next = target;
            size++;
        }

        void push_back( const T& data)
        {
            node* target = new node();
            target->data = data;
            target->next = tail;
            target->prev = tail->prev;
            tail->prev->next = target;
            tail->prev = target;
            size++;
        }

        void clear(){
            if (head->next == tail) return;
            node* it = head->next;
            while (head->next != tail){
                pop_front();
            }

            size = 0;
        }

        void empty(){
            return  head->next == tail;
        }
        
        void pop_front()
        {
            if (head->next == tail) return;
            node* target = head->next;
            head->next->next->prev = head;
            head->next = head->next->next;
            delete target;
            size--;    
        }
        void pop_back()
        {
            if (head->next == tail) return;
            node* target = tail->prev;
            tail->prev->prev->next = tail;
            tail->prev = tail->prev->prev;
            delete target;
            size--;
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

        list& operator=(list & rhs)
        {
            clear();
            node* it = rhs.head->next;
            while (it != rhs.tail){
                push_back(it->data);
                it  = it->next;
            }
            return *this;

        }

        bool  operator==(list & rhs){
            if(rhs.size != size) return false;
            
            node* it = head->next;
            node* it2 = rhs.head->next;
            while(it != tail)
            {
                if (it->data != it2->data)
                {
                    return false;
                }
                it = it->next;
                it2 = it2->next;
            }
            return true;
        }

        bool operator!=(list & rhs){
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