#include <iostream>
#include <string>
#include <array>

class HashTable{
	private:
		int  array[501];
		int M;
	public:
		// Members
		// Constructors
		HashTable()
		{
			// init
			M = 501;
			for (int i=0;i<M;i++)
			{
				array[i]=0;
			}
		}
		// Methods
		int hash(int key)
		{
			return key % M;
		}

		int get(int key)
		{
			return array[hash(key)];
		}

		void put(int key, int value)
		{
			array[hash(key)]=value;
		}
};

int main()
{
	HashTable table;

	table.put(123,1234);
	table.put(4,12345);

	std::cout << table.get(123);
	std::cout << table.get(4);
}
