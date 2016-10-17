#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

    template <typename T>
    class Vector
    {
    private:
        //Keeps track of actual physical size of our array
        int _physical_size;

        //Keeps track of the number of items in our array
        int _logical_size;

        //A pointer to our array
        T *_data;
    protected:
        //Alter physical size of our array
        virtual void requestResize(int new_size)
        {
            //Allocate space for new array
            T *new_data = new T{new_size};

            //Figure out which is smaller: logical size or new size

            int smallest_size = _logical_size;
            if(smallest_size > new_size)
            {
                //Logical size cannot exceed new physical size
                _logical_size = new_size;
                smallest_size = new_size;
            }
            //Copy curernt data into new space
            for (int i = 0; i < _logical_size; i++)
            {

            }
            //assume ownership of new array
            delete[] _data;
            _data = new_data;
            _physical_size = new_size;
        }
        //This functiona ensures that our vector stays efficient
        //at least half full. If completely full we will resize
        virtual void checkSize()
        {
            //Are we less than half full?
            if(_logical_size < _physical_size / 2)
            {
                requestResize(_physical_size / 2);
            }
            //are we full?
            else if(_logical_size >= _physical_size)
            {
                requestResize(_physical_size * 2 + 1);

            }
        }

    public:
        Vector (int size =0)
        {
            //By default vector is empty
            _logical_size = size;

            //base physical size off of logical size
            _physical_size = size * 2 + 1;
            //allocate memory for array
            _data = new T{_physical_size};
        }

        //Returns logical size of vector
        const int& getSize() const
        {
            return _logical_size;
        }

        void push(const T& item)
        {
            checkSize();
            _data[_logical_size] = item;
            _logical_size++;
        }

        const T& pop()
        {
            //grab last value
            const T& last = _data[_logical_size - 1];

            //make it look like the vector is smaller
            _logical_size--;
            checkSize();
        }


    };



#endif // VECTOR_H_INCLUDED
