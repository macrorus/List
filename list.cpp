#include <iostream>
#include "string.h"
 
using namespace std;
 
ostream& operator<<(ostream& o, string& s)
{
    o << s.c_str();
    return o;
}
 
istream& operator>>(istream& i, string& s)
{
    char buf[256];
    i >> buf;
    string tmp(buf);
    s = tmp;
   
    return i;
}
 
 
template<typename T>
class AbstractList
{
protected:
    T _default;
public :
	
    virtual void sort(bool (*f) (T* first, T* second)) = 0;
    virtual T get(int index) = 0;
    virtual void set(int index, T data) = 0;
    virtual void insert(int index, T data) = 0;
    virtual T remove(int index) = 0;
    virtual int len() = 0;
    void push(T data)
    {
        insert(0, data);
    }
    virtual T pop()
    {
        if (empty())
            return _default;
        else
            return remove(0);
    }
 
    virtual bool empty()
    {
        return len() == 0;
    }
 
    virtual ostream& print(ostream& o)
    {
        for (int i = 0; i < len(); i ++)
        {
            o << get(i) << endl;
        }
        return o;
    }
 
    virtual istream& read(istream& in)
    {
        int count;
        in >> count;
        for (int i = 0 ; i < count ; i ++)
        {
            T tmp;
            in >> tmp;
            insert(len(), tmp);
        }
        return in;
    }
 
};

template<typename T>
class SingleList : public AbstractList<T>
{
    T _data;
    int count;
    SingleList* next;
	void swap(SingleList* a, SingleList* b)
	{
		SingleList c(a->_default, a->_data);
		a->_data = b->_data;
		a->_default = b->_default;
		b->_data = c._data;
		b->_default = c._default;
	}
protected:
    T _default;
public :
    SingleList(T def, T data)
    {
        _default = def;
        _data = data;
        next = NULL;
        count = 0;   
    }

    void sort(bool (*f) (T* first, T* second))
    {	
		SingleList* point = this;
        for (int i = 0; i < len()-1; i++) 
		{        
			for (int j = 0; j < len()-i-1; j++)
			{
				if (f(&point->_data, &point->next->_data))
					swap(point, point->next);
				point = point->next;
			}
			point = this;
		}
		return;   
    }
    T get(int index)
    {
        if (count == 0)
                return _default;
        if ((index <= 0) || (next == NULL))
                return _data;
        return next->get(index - 1);
    }
    void set(int index, T data)
    {
        if (count == 0)         
        {
                _data = data;
                count = 1;
                return;
        }
        if ((index <= 0) || (next == NULL))
                _data = data;
        else
                next->set(index - 1, data);
        return;
    }       
    void insert(int index, T data)
    {
        if (count == 0)
        {
            set(index, data);
            return;
        }
        if ((index <= 0) || (next == NULL))
        {
                T tmp1 = _default;
                T tmp2 = _data;
                if (index <= 0)
                        set(0, data);
                else
                        tmp2 = data;
                SingleList* L = new SingleList(tmp1, tmp2);
                L->set(0, tmp2);
                L->next = next;
                next = L;
                return;
        }
        next->insert(index - 1, data);
        return;
    }
    T remove(int index)
    {
        if (next == NULL)
        {
                count = 0;
                return _data;
        }
        if (index <= 0)
        {
                T tmp1 = _data;
                _data = next->_data;
                _default = next->_default;
                SingleList* tmp2 = next->next;
				delete next;
                next = tmp2;     
                return tmp1;
        }
        if (next->next == NULL)
        {
                T tmp = next->_data;
                		delete next;				
                next = NULL;
                return tmp;
        }
        return next->remove(index - 1);
    }
    int len()  
    {
        if (count == 0)
                return 0;
        if (next == NULL)
                return 1;
        return next->len() + 1;
    }
};
 
 
 
AbstractList<string>* get_init()
{
    string e("EMPTY!");
    string d("Hello world!");
    SingleList<string>* s = new SingleList<string>(e, d);
    return s;
}



