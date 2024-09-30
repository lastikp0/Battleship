#include <iostream>
#include <memory>
#include <vector>
#include <utility>

class Ship
{
public:
	Ship(int n)
	{
		id = n;
		std::cout << "Ship(" << id <<")" << std::endl;
	}
	
	void printID()
	{
		std::cout << "ID: " << id << std::endl;
	}
	
	~Ship()
	{
		std::cout << "~Ship(" << id << ")" << std::endl;
	}
private:
	int id;
};

class Field
{
public:
	Field(int x, int y)
	{
		std::cout << "Field()" << std::endl;
		size_x = x;
		size_y = y;
		field.resize(x);
		for(int i = 0; i < x; i++)
		{
			field[i].resize(y);
			for(int j = 0; j < y; j++)
			{
				field[i][j] = nullptr;
			}
		}
	}
	
	void placeShip(std::shared_ptr<Ship> ship, int x, int y)
	{
		std::cout << "placeShip()_Field" << std::endl;
		for (int i = 0; i < 3; i++)
		{
			field[x + i][y] = ship;
		}
	}
	
	void printShipID(int x, int y)
	{
		field[x][y]->printID();
	}
	
	~Field()
	{
		std::cout << "~Field()" << std::endl;
		
		for (int i = 0; i < size_x; i++)
		{
			field[i].clear();
		}
		
		field.clear();
	}
	
private:
	std::vector<std::vector<std::shared_ptr<Ship>>> field;
	int size_x;
	int size_y;
};


class ShipManager
{
public:
	ShipManager()
	{
		std::cout << "ShipManager()" << std::endl;
		Ship ship(2);
		ships.push_back({std::make_shared<Ship>(ship), false});
	}
	
	void placeShip(Field& field)
	{
		std::cout << "placeShip()_ShipManager" << std::endl;
		field.placeShip(ships[0].first, 0, 0);
		ships[0].second = true;
	}
	
	void printShipID()
	{
		ships[0].first->printID();
	}
	
	void addShip()
	{
		std::cout << "addShip()" << std::endl;
		Ship ship(3);
		ships[0].first = std::make_shared<Ship>(ship);
	}
	
	~ShipManager()
	{
		std::cout << "~ShipManager()" << std::endl;
		ships.clear();
	}
	
private:
	std::vector<std::pair<std::shared_ptr<Ship>, bool>> ships;
};

int main()
{
	ShipManager ship_manager;
	
	ship_manager.printShipID();
	
	Field field(5, 5);
	
	ship_manager.placeShip(field);
	field.printShipID(0, 0);
	field.printShipID(1, 0);
	field.printShipID(2, 0);
	
	ship_manager.addShip();
	ship_manager.printShipID();
	field.printShipID(0, 0);
	field.printShipID(1, 0);
	field.printShipID(2, 0);
	
	return 0;
}
