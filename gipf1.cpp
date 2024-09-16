/*#include <iostream>
#include <string>

using namespace std;

void find_coord(string** index, string pos, int size, int* x, int* y) {
	for (int i = 0; i < 2 * size + 1; i++) {
		for (int j = 0; j < 4 * size + 3; j++) {
			if (index[i][j] == pos) {
				*x = j;
				*y = i;
				return;
			}
		}
	}
}

int main()
{
	string commands;

	int k = 0;			//liczba pionow w linii potrzebnych do ich zebrania, k>2 && k < 2s-1
	int allW = 0;
	int allB = 0;
	int playingW = 0;
	int playingB = 0;
	int reserveW = 0;
	int reserveB = 0;
	char active_player = 'W';

	char** board = NULL;
	int size = 0;

	string row;
	int row_max = 0;

	string** index = nullptr;
	string* edge_indexes = nullptr;
	int edge_indexes_index = 0;

	int filled_cells = 0;
	bool correct_row_length = true;
	bool correct_whites_num = true;
	bool correct_blacks_num = true;

	char alphabet[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g','h', 'i', 'j','k', 'l', 'm', 'n', 'o', 'p', 'r', 's', 't', 'u', 'w', 'v', 'x', 'y', 'z' };
	char numbers[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', '21', '22', '23', '24', '25' };

	while (cin >> commands)
	{
		if (commands == "LOAD_GAME_BOARD")
		{
			cin >> size >> k >> allW >> allB;

			cin >> reserveW >> reserveB >> active_player;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			int length = size;
			int start = size+1;
			char c;
			string line;
			board = new char* [2 * size + 1];

			for(int i = 0; i< 2*size + 1; i++)
			{ 
				board[i] = new char[4 * size + 1];
				if (i == 0 || i == 2 * size) 
				{
					for (int j = 0; j < 4 * size + 1; j++)
					{
						if (j < size || j > 3 * size + 1) board[i][j] = ' ';
						else
						{
							board[i][j++] = '+';
							board[i][j] = ' ';
						}
					}
				}
				else 
				{
					if (i == 2) 
					{
						cout << "gfdss" << endl;
					}
					cin >> c;
					line = "";
					while (c != '\n' && c != '\xff')
					{
						line = line + c;
						if (c == '_' || c == 'W' || c == 'B') filled_cells++;
						c = getchar();
					}
				}
				if (filled_cells != length)
				{
					row = true;
				}

				filled_cells = length;
				int together = 0;
				for (int j = 0; j < 4 * size + 1; j++) 
				{
					if (j == start - 2 || j == 4 * size + 2 - start) board[i][j] = '+';
					else if (j < start || j > 4 * size - start) board[i][j] = ' ';
					else 
					{
						board[i][j] = line[j - start];
						if (board[i][j] == 'W') playingW++;
						else if (board[i][j] == 'B') playingB++;
					}
				}
				if (i < size) 
				{ 
					length++; start--; 
				}
				else 
				{ 
					length--; start++; 
				}
				
			}

			if (playingW + reserveW > allW)
			{
				correct_whites_num = false;
			}
			if (playingB + reserveB > allB)
			{
				correct_blacks_num = false;
			}

			if (correct_row_length == false)
			{
				cout << "WRONG_BOARD_ROW_LENGTH" << "\n";
				correct_row_length = true;
				playingW = 0;
				playingB = 0;
			}
			else if (correct_blacks_num == false)
			{
				cout << "WRONG_BLACK_PAWNS_NUMBER" << "\n";
				correct_blacks_num = true;
				playingB = 0;
				playingW = 0;
			}
			else if (correct_whites_num == false)
			{
				cout << "WRONG_WHITE_PAWNS_NUMBER" << "\n";
				correct_whites_num = true;
				playingW = 0;
				playingB = 0;
			}
			else
			{
				cout << "BOARD_STATE_OK" << '\n';
				playingW = 0;
				playingB = 0;
			}
			commands.clear();

			string cell_name;
			int same_num_start = 3 * size;
			int letter_start = size;
			int letter_index = 0;
			int number_index = 0;

			index = new string * [(2 * size) + 1];
			int edge_size = 6 * size;
			edge_indexes = new string[edge_size];



			for (int y = 0; y < 2 * size + 1; y++)
			{
				index[y] = new string[(4 * size) + 3];

				if (y < size)
				{
					number_index = letter_start;
				}
				else
				{
					number_index = 0;
				}

				for (int x = 0; x < 4 * size + 3; x++)
				{
					if (x > 0 && x < 4 * size + 3 - letter_start)
					{
						if (y < size)
						{
							if (x >= letter_start)
							{
								if (index[y][x + letter_start - 1] == " ")
								{
									cell_name = string(1, alphabet[letter_index]) + string(1, numbers[number_index]);
									index[y][x + letter_start] = cell_name;

									letter_index++;
									if (x < same_num_start)
										number_index++;
									else
										continue;
								}
								else
								{
									index[y][x + letter_start] = " ";
								}
							}
							else
							{
								index[y][x] = " ";
							}

						}
						else if (y == size)
						{
							if (x % 2 == 1)
							{
								cell_name = string(1, alphabet[letter_index + letter_start]) + string(1, numbers[number_index]);
								index[y][x] = cell_name;

								letter_index++;
								if (x < same_num_start)
									number_index++;
								else
									continue;
							}
							else
							{
								index[y][x] = " ";
							}
						}
						else if (y == 2 * size)
						{
							cell_name = string(1, alphabet[letter_index + size + 1]) + string(1, numbers[number_index]);
							index[y][x + letter_start] = cell_name;

							letter_index++;
						}
						else if (y > size)
						{
							if (x >= letter_start)
							{
								if (index[y][x + letter_start - 1] == " ")
								{
									cell_name = string(1, alphabet[letter_index]) + string(1, numbers[number_index]);
									index[y][x + letter_start] = cell_name;

									letter_index++;
									if (x < same_num_start)
										number_index++;
									else
										continue;
								}
								else
								{
									index[y][x + letter_start] = " ";
								}
							}
							else
							{
								index[y][x] = " ";
							}
						}

					}
					if (x == 4 * size)
					{
						same_num_start--;
					}
				}
				if (y < size)
				{
					letter_index = 0;
					letter_start--;
				}
				else
				{
					letter_start++;
					letter_index = letter_start;
				}
				number_index = 0;
			}

			for (int i = 0; i < 2 * size + 1; i++)
			{
				for (int j = 0; j < 4 * size + 3; j++)
				{
					cout << index[i][j];
				}
				cout << "\n";
			}
		}
		else if (commands == "DO_MOVE")				//DO MOVE
		{
			char c = NULL;
			string move_cords;
			string start_cord;
			string end_cord;
			bool start_written = false;
			bool start_exist = false;
			bool end_exist = false;
			int start_letter_index = 0;
			int end_letter_index = 0;
			bool wrong_index = false;
			int start_cords[2];
			int end_cords[2];

			while (c != '\n')
			{
				c = getchar();
				move_cords += c;
			}

			for (int i = 0; i + 1 < move_cords.length(); i++)
			{
				if ((int)move_cords[i] >= 97 && (int)move_cords[i] <= 122 && i + 1 < move_cords.length())
				{
					if (start_written == false)
					{
						start_cord = string(1, move_cords[i]) + string(1, move_cords[i + 1]);
						start_written = true;
					}
					else
					{
						end_cord = string(1, move_cords[i]) + string(1, move_cords[i + 1]);
					}
				}
			}

			for (int i = 0; i < 2 * size + 1; i++)
			{
				for (int j = 0; j < 4 * size + 3; j++)
				{
					if (start_cord == index[i][j])
					{
						start_exist = true;
						start_cords[0] = i;
						start_cords[1] = j;

					}
					else if (end_cord == index[i][j])
					{
						end_exist = true;
						end_cords[0] = i;
						end_cords[1] = j;
						break;
					}
				}
				if (start_exist && end_exist)
				{
					break;
				}
			}




			if ((start_exist == false && end_exist == false) || start_exist == false)
			{
				cout << "BAD_MOVE_" << start_cord << "_IS_WRONG_INDEX" << endl;
			}
			else if (end_exist == false)
			{
				cout << "BAD_MOVE_" << end_cord << "_IS_WRONG_INDEX" << endl;
			}

			for (int i = 0; i < 25; i++)
			{
				if (start_cord[0] == alphabet[i])
				{
					start_letter_index = i;
				}
				if (end_cord[0] == alphabet[i])
				{
					end_letter_index = i;
				}
			}

			if (start_exist == true && end_exist == true)
			{
				if (start_letter_index != end_letter_index && start_letter_index != end_letter_index + 1 && start_letter_index != end_letter_index - 1
					|| start_cord[1] != end_cord[1] && start_cord[1] != end_cord[1] + 1 && start_cord[1] != end_cord[1] - 1)
				{
					wrong_index = true;
					cout << "UNKNOWN_MOVE_DIRECTION" << endl;
				}
			}

			if (board[start_cords[0]][start_cords[1]] == '+')
			{
				cout << "BAD_MOVE_" << start_cord << "_IS_WRONG_STARTING_FIELD" << endl;
			}
			if (board[end_cords[0]][end_cords[1]] == '+')
			{
				cout << "BAD_MOVE_" << end_cord << "_IS_WRONG_DESTINATION_FIELD" << endl;
			}



			int direction[2]; //= { 1, 1 };		// from start to end
			int change_dir[3][2] = { {0, -2}, {-1, 3}, {0, -4} };
			bool opposite_player = false;
			int a = 0, b = 1;
			int changed = 0;		//ile razy zmieniono direction

			direction[0] = end_cords[0] - start_cords[0];
			direction[1] = end_cords[1] - start_cords[1];
			int tempy = start_cords[0];
			int tempx = start_cords[1];

			do 
			{
				board[tempy][tempx] = active_player;
				opposite_player == true;

				tempy += direction[0];
				tempx += direction[1];
			} while (board[tempy][tempx] != '+');

			if (opposite_player == true)
			{
				if (active_player == 'W')
					active_player = 'B';
				else
					active_player = 'W';
			}

			// if start_exists && end_exists == true
			/*for (int i = 0; i < 2 * size + 1; i++)
			{
				for (int j = 0; j < 4 * size + 3; j++)
				{
					board[start_cords[0]][start_cords[1]]

						if (start_cords[0] + direction[0] == end_cords[0] && start_cords[1] + direction[1] == end_cords[1])
						{
							if (j > 2)
								board[i][j - 2] = active_player;

							opposite_player = true;
							direction[0] += change_dir[a][a];
							direction[1] += change_dir[a][b];

							changed++;
							if (changed == 4)
							{
								a--;
								b--;
							}
							else
							{
								a++;
								b++;
							}
						}
					
				}
			}

			

			commands.clear();
			move_cords.clear();
			start_cord.clear();
			end_cord.clear();
			wrong_index = false;
			start_written = false;
			start_exist = false;
			end_exist = false;
		}
		else if (commands == "PRINT_GAME_BOARD")			// PRINT GAME BOARD
		{
			for (int i = 1; i < 2 * size; i++)
			{
				for (int j = 2; j < 4 * size - 1; j++)
				{
					if (board[i][j] == '+') cout << " ";
					else cout << board[i][j];
				}
				cout << "\n";
			}
			commands.clear();
		}
	}
	return 0;
}





do
				{
					if (board[tempy][tempx] == 'B' || board[tempy][tempx] == 'W' || board[tempy][tempx] == '_')
					{
						temp1 = board[tempy][tempx];
						if (tempy + direction[0] >= 0 && tempy + direction[0] <= 2 * size && tempx + direction[1] >= 0 && tempx + direction[1] <= 4 * size + 2)
							board[tempy + direction[0]][tempx + direction[1]] = temp1;

						//board[tempy][tempx] = active_player;
						//temp2 = board[tempy - direction[0]][tempx - direction[1]];

						if (tempy - direction[0] == start_cords[0] && tempx - direction[1] == start_cords[1])
							temp2 = active_player;
						else
							temp2 = board[tempy - direction[0]][tempx - direction[1]];

						board[tempy][tempx] = temp2;

						opposite_player = true;
					}

					tempy += direction[0];
					tempx += direction[1];

				} while (board[tempy][tempx] != '+');


*/