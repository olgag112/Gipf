/*#include <iostream>
#include <string>

using namespace std;

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
	char startingG;

	char** board = NULL;
	int size = 0;
	int height = 2 * size - 1;
	int width = 4 * size - 3;
	string row;

	string** index;

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

			cin >> reserveW >> reserveB >> startingG;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			int length = size;

			board = new char* [2 * size - 1];

			for (int i = 0; i < 2 * size - 1; i++)
			{
				filled_cells = 0;
				getline(cin, row);

				board[i] = new char[row.length()];

				for (int j = 0; j < row.length(); j++)
				{
					board[i][j] = row[j];

					if (board[i][j] == 'B')
					{
						playingB++;
						filled_cells++;
					}
					else if (board[i][j] == 'W')
					{
						playingW++;
						filled_cells++;
					}
					else if (board[i][j] == '_')
					{
						filled_cells++;
					}

					if (j == row.length() - 1)
					{
						if (length != filled_cells)
						{
							correct_row_length = false;
						}

						if (i < size - 1)
						{
							length++;
						}
						else
						{
							length--;
						}
						filled_cells = 0;
					}
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
							if (x >= letter_start)  //x < 4 * size + 1 - letter_start
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
						else if (y == 2 * size)
						{
							cell_name = string(1, alphabet[letter_index + size + 1]) + string(1, numbers[number_index]);
							index[y][x + letter_start] = cell_name;

							letter_index++;
						}
					}
					if (x == 4 * size + 2)
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
		}
		else if (commands == "DO_MOVE")
		{
			char c = NULL;
			string move_cords;
			string start_cord;
			string end_cord;
			bool start_written = false;

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
			cout << start_cord << endl << end_cord;

			bool start_index_dne = false;
			bool end_index_dne = false;
			string wrong_index;


			int y = 0;
			int tempy = size;
			int tempx = 0;
			while (y < 2 * size + 1)
			{
				if (index[tempy][tempx] == start_cord)		// jesli to jest true to istnieje taki index na planszy wiec jest git - break
					break;
				else if (index[tempy][tempx] == end_cord)
					break;
				else
				{
					for (int a = 0; a < 2 * size + 1; a++)
					{
						if (alphabet[a] != start_cord[0])
						{
							start_index_dne = true;
							wrong_index = start_cord;
						}
						else
						{
							for (int n = 0; n < 2 * size + 1; n++)
							{
								if (numbers[n] != start_cord[1])
								{
									start_index_dne = true;
									wrong_index = start_cord;
								}
								else
									continue;
							}
						}

						if (alphabet[a] != end_cord[0])
						{
							end_index_dne = true;
							if (wrong_index != start_cord)
								wrong_index = end_cord;
						}
						else
						{
							for (int n = 0; n < 2 * size + 1; n++)
							{
								if (numbers[n] != end_cord[1])
								{
									end_index_dne = true;
									wrong_index = end_cord;
								}
								else
									continue;
							}
						}
					}
				}
				tempy++;
				tempx++;
			}


			if (start_index_dne == true || end_index_dne == true)
			{
				cout << "BAD_MOVE_<" << wrong_index << ">_IS_WRONG_INDEX";
			}

			commands.clear();
			move_cords.clear();
			start_cord.clear();
			end_cord.clear();
			wrong_index.clear();
			start_written = false;
			start_index_dne = false;
			end_index_dne = false;
		}
		else if (commands == "PRINT_GAME_BOARD")
		{
			int row_l = row.length();
			for (int i = 0; i < 2 * size - 1; i++)
			{
				for (int j = 0; j < row_l; j++)		//jaka tu dlugosc
				{
					cout << board[i][j];

					if (j < size - 1)
					{
						row_l += 1;
					}
					else
					{
						row_l -= 1;
					}
				}
				cout << "\n";
			}
			commands.clear();
		}
	}

	return 0;
}
*/