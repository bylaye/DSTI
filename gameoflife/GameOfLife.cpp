#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <chrono>
#include <thread>


enum STATE
{
	ALIVE='+',
	DEAD = '-',
	WAS_ALIVE = '=',
};


const std::string ALIVE_COLOR = "\033[32m";
const std::string DIED_COLOR = "\033[34m";
const std::string WAS_ALIVE_COLOR = "\033[31m";
const std::string COLOR_RESET = "\033[0m";

const int SIMULATION_SECOND = 2; 


using Position = std::pair<int, int>;

class Board
{
	private:
		int rows;
		int cols;
		std::vector<std::vector<STATE>> cells;
	
	public:
		Board(int r, int c): 
			rows(r), 
			cols(c),
			cells(rows, std::vector<STATE>(cols, STATE::DEAD)) {}
		

		void display() const {
		    for (const auto &row : cells) {
		        for (STATE val : row) {
		            std::cout << "\033[32m" << static_cast<char>(val) << "";
		        }
		        std::cout << std::endl;
		    }
		}
		

		void displayColor() 
		{
			for (const auto &row : cells) {
		        for (STATE val : row) {
					char cast_val = static_cast<char>(val);
					if(val == STATE::ALIVE)
						std::cout << ALIVE_COLOR << "*";
					else if (val == STATE::WAS_ALIVE)
						std::cout << WAS_ALIVE_COLOR << "*";
					else if (val == STATE::DEAD)
						std::cout << DIED_COLOR << "*";
		            //std::cout << "\033[32m" << static_cast<char>(val) << "";
		        }
		        std::cout << std::endl;
		    }
		}

		void initialize(int numAliveCells) {
		    srand(time(0)); 
		    for (int i = 0; i < numAliveCells; i++) {
		        int randRow = rand() % rows;
		        int randCol = rand() % cols;
		        cells[randRow][randCol] = STATE::ALIVE;
		    }
		}


		std::vector<Position> getNeighbor(int r, int c)
		{
			std::vector<Position> neighbors;
			for(int i=-1; i<=1; i++)
			{
				if((i+r >= 0 ) && (i+r)< rows)
				{
					for (int j=-1; j<=1; j++)
					{
						if((j+c >= 0 ) && (j+c)< cols)
						{
							if(i==0 && j==0)
								continue;
							else
								neighbors.push_back({r+i, c+j});
						}
					}
				}
			}
			return neighbors;
		}


		STATE updateAliveCell(int r, int c)
		{
			int aliveNeighbor = 0;
			std::vector<Position> neighbors = getNeighbor(r, c);
			for(const auto& pos : neighbors)
			{
				if (cells[pos.first][pos.second] == STATE::ALIVE)
					aliveNeighbor++;
			}
			return (aliveNeighbor == 3 || aliveNeighbor == 2) ? STATE::ALIVE : STATE::WAS_ALIVE;
		}


		STATE updateDeadCell(int r, int c)
		{
			int aliveNeighbor = 0;
			std::vector<Position> neighbors = getNeighbor(r, c);
			for(const auto& pos : neighbors)
			{
				if (cells[pos.first][pos.second] == STATE::ALIVE)
					aliveNeighbor++;
			}
			return (aliveNeighbor == 3 ) ? STATE::ALIVE : STATE::DEAD;
		}


		std::map<Position, STATE> updateCells()
		{	
			Position pos ;
			std::map<Position, STATE> newStateCells;
			for (int r=0; r< rows; r++){
				for (int c=0; c < cols; c++)
				{
					pos = {r,c};
					if(cells[r][c] == STATE::ALIVE)
					{
						if(updateAliveCell(r, c) != STATE::ALIVE)
							newStateCells[pos] = STATE::WAS_ALIVE;
					}
					if(cells[r][c] == STATE::DEAD)
					{
						if(updateDeadCell(r, c) == STATE::ALIVE)
							newStateCells[pos] = STATE::ALIVE;
					}
				}
			}
			return newStateCells;
		}
		

		void updateBoard(std::map<Position, STATE> newUpdateCell)
		{
			for(const auto& pos : newUpdateCell)
				cells[pos.first.first][pos.first.second] = pos.second;
		}

		void run()
		{
			updateBoard(updateCells());
			displayColor();
		}
};

void clearConsole() {
    // Utilisation de "clear" pour Linux/macOS et "cls" pour Windows
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main(){
	Board board(15,60);
	clearConsole();
	std::cout << "Initialisation" << std::endl;
	board.initialize(120);
	//board.display();
	board.displayColor();
	std::this_thread::sleep_for(std::chrono::seconds(SIMULATION_SECOND));
	std::cout << std::endl;
	
	int interation =0;
	while (true)
	{
		clearConsole();
		std::cout << COLOR_RESET << "Iteration : " << ++interation << std::endl;
		board.run();
		std::this_thread::sleep_for(std::chrono::seconds(SIMULATION_SECOND));
	}
	
}
