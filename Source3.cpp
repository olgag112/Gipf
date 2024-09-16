
#include <iostream>
#include <string>
#include <vector>

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
	char active_player = 'W';

	char** board = NULL;
	int size = 0;

	string row;
	int row_max = 0;

	string** index = nullptr;

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
			correct_row_length = true;
			cin >> size >> k >> allW >> allB;

			cin >> reserveW >> reserveB >> active_player;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			int length = size;
			int start = size + 1;
			char c;
			string line;
			board = new char* [2 * size + 1];

			for (int i = 0; i < 2 * size + 1; i++)
			{
				filled_cells = 0;
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
					cin >> c;
					line = "";
					while (c != '\n' && c != '\xff')
					{
						line = line + c;
						if (c == '_' || c == 'W' || c == 'B') filled_cells++;
						c = getchar();
					}

					if (filled_cells != length)
					{
						correct_row_length = false;
					}
					else 
					{
						filled_cells = length;

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

			}

			if (playingW + reserveW > allW)
			{
				correct_whites_num = false;
			}
			else
				correct_whites_num = true;
			if (playingB + reserveB > allB)
			{
				correct_blacks_num = false;
			}
			else
				correct_blacks_num = true;


			char cell;
			int chain = 0;
			int num_chains = 0;
	
			for (int i = 1; i < 2 * size + 1; i++)		//horizontal
			{
				chain = 0;
				for (int j = 2; j < 4 * size + 1; j++)
				{
					if (board[i][j] != ' ' && board[i][j] != '+')
					{
						if (board[i][j] == 'B' || board[i][j] == 'W')		
						{
							if (chain == 0)
							{
								cell = board[i][j];
								chain++;
							}
							else if (chain > 0)
							{
								if (board[i][j] == cell)
								{
									chain++;
								}
								else
								{
									cell = board[i][j];
									chain = 1;
								}
							}
						}
						else if (board[i][j] == '_')
						{
							chain = 0;
						}
					}
					if (chain == k)
					{
						num_chains++;
						break;					
					}
				}
			}

		
			int rightx = 2, righty = size;
			int temp_x = 0, temp_y = 0;
			
			for (int i = 0; i < 2 * size - 1; i++)		//od dolu do gory w prawo
			{
				temp_x = rightx;
				temp_y = righty;
				chain = 0;

				while (board[temp_y][temp_x] != '+' && temp_y > 0)
				{
					if (board[temp_y][temp_x] != '_')
					{
						if (chain == 0)
						{
							cell = board[temp_y][temp_x];
							chain++;
						}
						else if (chain > 0)
						{
							if (board[temp_y][temp_x] == cell)
							{
								chain++;
							}
							else
							{
								cell = board[temp_y][temp_x];
								chain = 1;
							}
						}
					}
					else
						chain = 0;

					if (chain == k)
					{
						num_chains++;
						break;
					}
					temp_x++;
					temp_y--;
				}

				if (righty < 2 * size - 1)
				{
					rightx++;
					righty++;
				}
				else
					rightx += 2;
			}

			int leftx = 4 * size - 2, lefty = size;
			temp_y = 0, temp_x = 0;
			for (int i = 0; i < 2 * size - 1; i++)		//od dolu do gory w lewo
			{
				temp_x = leftx;
				temp_y = lefty;
				chain = 0;

				while (board[temp_y][temp_x] != '+' && temp_y > 0)
				{
					if (board[temp_y][temp_x] != '_')
					{
						if (chain == 0)
						{
							cell = board[temp_y][temp_x];
							chain++;
						}
						else if (chain > 0)
						{
							if (board[temp_y][temp_x] == cell)
							{
								chain++;
							}
							else
							{
								cell = board[temp_y][temp_x];
								chain = 1;
							}
						}
					}
					else
						chain = 0;		

					if (chain == k)
					{
						num_chains++;
						break;
					}
					
					temp_x--;
					temp_y--;
				}

				if (lefty < 2 * size - 1)
				{
					leftx--;
					lefty++;
				}
				else 
					leftx -= 2;
			}

			
				
			if (num_chains == 1)
			{
				cout << "ERROR_FOUND_" << num_chains << "_ROW_OF_LENGTH_K" << endl;
			}
			else if (num_chains > 1)
			{
				cout << "ERROR_FOUND_" << num_chains << "_ROWS_OF_LENGTH_K" << endl;
			}
			else if (correct_row_length == false)
			{
				cout << "WRONG_BOARD_ROW_LENGTH" << "\n";
				playingW = 0;
				playingB = 0;
			}
			else if (correct_blacks_num == false)
			{
				cout << "WRONG_BLACK_PAWNS_NUMBER" << "\n";
				playingB = 0;
				playingW = 0;
			}
			else if (correct_whites_num == false)
			{
				cout << "WRONG_WHITE_PAWNS_NUMBER" << "\n";
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
			int letter_start = size - 1;
			int letter_index = 0;
			int number_index = 0;
			index = new string * [(2 * size) + 1];


			for (int y = 0; y < 2 * size + 1; y++)
			{
				index[y] = new string[(4 * size) + 1];

				if (y < size)
				{
					number_index = letter_start;
				}
				else
				{
					number_index = 0;
				}

				for (int x = 0; x < 4 * size + 1; x++)
				{
					if (x == 4 * size)
					{
						same_num_start--;
					}
					if (x > 0 && x < 4 * size + 1 - letter_start)
					{
						if (y < size)
						{
							if (x > letter_start)
							{
								if (index[y][x - 1] == " ")
								{
									cell_name = string(1, alphabet[letter_index]) + string(1, numbers[number_index+1]);
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
							else
							{
								index[y][x] = " ";
							}

						}
						else if (y == size)
						{
							if (x % 2 == 1)
							{
								cell_name = string(1, alphabet[letter_index]) + string(1, numbers[number_index]);
								index[y][x - 1] = cell_name;

								letter_index++;
								if (x < same_num_start)
									number_index++;
								else
									continue;
							}
							else
							{
								index[y][x-1] = " ";
							}
						}
						else if (y > size)
						{
							if (x > letter_start)
							{
								if (index[y][x - 1] == " ")
								{

									cell_name = string(1, alphabet[letter_index+1]) + string(1, numbers[number_index]);
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
							else
							{
								index[y][x] = " ";
							}
						}

					}
					else 
					{
						index[y][x] = " ";
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

			index[size][4*size] = string(1, alphabet[2 * size]) + string(1, numbers[size]);
			
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
				for (int j = 0; j < 4 * size + 1; j++)
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
						
					}
				}
				if (start_exist && end_exist)
				{
					break;
				}
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


			
			if ((start_exist == false && end_exist == false) || start_exist == false)
			{
				cout << "BAD_MOVE_" << start_cord << "_IS_WRONG_INDEX" << endl;
				continue;
			}
			else if (end_exist == false)
			{
				cout << "BAD_MOVE_" << end_cord << "_IS_WRONG_INDEX" << endl;
				continue;
			}
			else if (start_exist == true && end_exist == true)
			{
				if (start_letter_index != end_letter_index && start_letter_index != end_letter_index + 1 && start_letter_index != end_letter_index - 1
					|| start_cord[1] != end_cord[1] && start_cord[1] != end_cord[1] + 1 && start_cord[1] != end_cord[1] - 1)
				{
					wrong_index = true;
					cout << "UNKNOWN_MOVE_DIRECTION" << endl;
					continue;
				}
			}
			if (board[start_cords[0]][start_cords[1]] != '+')
			{
				cout << "BAD_MOVE_" << start_cord << "_IS_WRONG_STARTING_FIELD" << endl;
				continue;
			}
			if (board[end_cords[0]][end_cords[1]] == '+')
			{
				cout << "BAD_MOVE_" << end_cord << "_IS_WRONG_DESTINATION_FIELD" << endl;
				continue;
			}
			else 
			{
				int direction[2]; 
				bool opposite_player = false;
				bool full_row = false;
				
				direction[0] = end_cords[0] - start_cords[0];
				direction[1] = end_cords[1] - start_cords[1];
				int tempy = end_cords[0];
				int tempx = end_cords[1];
				
				if (board[tempy][tempx] == '_')
				{
					board[tempy][tempx] = active_player;
				}
				else
				{
					char c = board[tempy][tempx];
					while (board[tempy + direction[0]][tempx + direction[1]] != '_')
					{
						if (board[tempy + direction[0]][tempx + direction[1]] == '+')
						{
							full_row = true;
							break;
						}
						tempy += direction[0];
						tempx += direction[1];
						c = board[tempy][tempx];
					}
				}

				int blacks_in_line = 0; 
				int whites_in_line = 0;

				if (full_row == false)
				{
					do
					{
						board[tempy + direction[0]][tempx + direction[1]] = board[tempy][tempx];

						if (board[tempy + direction[0]][tempx + direction[1]] == 'B')
							blacks_in_line++;
						else
							whites_in_line++;

						tempy -= direction[0];
						tempx -= direction[1];

					} while (board[tempy][tempx] != '+');
					board[tempy + direction[0]][tempx + direction[1]] = active_player;
					opposite_player = true;

					if (opposite_player == true)
					{
						if (active_player == 'W')
						{
							active_player = 'B';
							reserveW--;
						}
						else
						{
							active_player = 'W';
							reserveB--;
						}
					}
					cout << "MOVE_COMMITTED" << endl;

					
					char cell1;
					int chain1 = 0;
					bool adt_cell = false;

					vector<int> horiz_y;
					vector<int> horiz_x;

					for (int i = 1; i < 2 * size + 1; i++)		//horizontal
					{
						horiz_y.clear();
						horiz_x.clear();
						chain1 = 0;
						adt_cell = false;
						for (int j = 2; j < 4 * size + 1; j++)
						{
							if (board[i][j] != ' ' && board[i][j] != '+')
							{
								if (board[i][j] == 'B' || board[i][j] == 'W')		
								{
									if (chain1 == 0)
									{
										cell1 = board[i][j];
										chain1++;

										horiz_y.push_back(i);
										horiz_x.push_back(j);
									}
									else if (chain1 > 0)
									{
										if (board[i][j] == cell1)
										{
											chain1++;

											horiz_y.push_back(i);
											horiz_x.push_back(j);
										}
										else if (board[i][j] == '_')
										{
											horiz_y.clear();
											horiz_x.clear();
											chain1 = 0;
										}
										else
										{
											if (chain1 == 1 || chain1 >= k)
											{
												adt_cell = true;
												cell1 = board[i][j];

												horiz_y.push_back(i);
												horiz_x.push_back(j);
											}
											else
											{
												horiz_y.clear();
												horiz_x.clear();

												cell1 = board[i][j];

												horiz_y.push_back(i);
												horiz_x.push_back(j);

												chain1 = 1;
											}
										}
									}
								}
								else if (board[i][j] == '_' &&chain1>=k)
								{
									break;
								}
							}
							if (chain1 >= k)
							{
								for (int k = 0; k < horiz_y.size(); k++)
								{
									if (board[horiz_y[k]][horiz_x[k]] == 'B')
									{
										if (adt_cell == true)
										{
											playingB--;
											adt_cell = false;
										}
										else
										{
											playingB--;
											reserveB++;
										}
									}
									else if (board[horiz_y[k]][horiz_x[k]] == 'W')
									{
										if (adt_cell == true)
										{
											playingW--;
											adt_cell = false;
										}
										else
										{
											playingW--;
											reserveW++;
										}
									}
									board[horiz_y[k]][horiz_x[k]] = '_';
								}
							}
						}
					}

					
					int rightx1 = 2, righty1 = size;
					int temp_x1 = 0, temp_y1 = 0;
					
					for (int i = 0; i < 2 * size - 1; i++)		//right diagonal to the top from end_cord
					{
						temp_x1 = rightx1;
						temp_y1 = righty1;
						chain1 = 0;
						horiz_y.clear();
						horiz_x.clear();
						adt_cell = false;

						while (board[temp_y1][temp_x1] != '+' && temp_y1 > 0)		
						{
							if (board[temp_y1][temp_x1] != '_')
							{
								if (chain1 == 0)
								{
									cell1 = board[temp_y1][temp_x1];
									chain1++;

									horiz_y.push_back(temp_y1);
									horiz_x.push_back(temp_x1);
								}
								else if (chain1 > 0)
								{
									if (board[temp_y1][temp_x1] == cell1)
									{
										chain1++;
										horiz_y.push_back(temp_y1);
										horiz_x.push_back(temp_x1);
									}
									else
									{
										if (chain1 == 1 || chain1 >= k)
										{
											adt_cell = true;
											cell1 = board[temp_y1][temp_x1];

											horiz_y.push_back(temp_y1);
											horiz_x.push_back(temp_x1);
										}
										else
										{
											horiz_y.clear();
											horiz_x.clear();
											cell1 = board[temp_y1][temp_x1];
											horiz_y.push_back(temp_y1);
											horiz_x.push_back(temp_x1);
											chain1 = 1;
										}
									}
								}
							}
							else if (board[temp_y1][temp_x1] == '_' && chain1 < k)
							{
								chain1 = 0;
								horiz_y.clear();
								horiz_x.clear();
							}
							else if(board[temp_y1][temp_x1] == '_' && chain1 >= k)
							{ 
								break;
							}
							temp_x1++;
							temp_y1--;
						}

						if (chain1 >= k)
						{
							for (int a = 0; a < horiz_y.size(); a++)
							{
								if (board[horiz_y[a]][horiz_x[a]] == 'B')
								{
									if (adt_cell == true)
									{
										playingB--;
										adt_cell = false;
									}
									else
									{
										playingB--;
										reserveB++;
									}
								}
								else if (board[horiz_y[a]][horiz_x[a]] == 'W')
								{
									if (adt_cell == true)
									{
										playingW--;
										adt_cell = false;
									}
									else
									{
										playingW--;
										reserveW++;
									}
								}
								board[horiz_y[a]][horiz_x[a]] = '_';
							}
						}

						if (righty1 < 2 * size - 1)
						{
							rightx1++;
							righty1++;
						}
						else
							rightx1 += 2;
					}


					int leftx1 = 4 * size - 2, lefty1 = size;
					temp_y1 = 0, temp_x1 = 0;

					for (int i = 0; i < 2 * size - 1; i++)		//od dolu do gory w lewo
					{
						temp_x1 = leftx1;
						temp_y1 = lefty1;
						chain1 = 0;
						horiz_y.clear();
						horiz_x.clear();
						adt_cell = false;

						while (board[temp_y1][temp_x1] != '+' && temp_y1 > 0)
						{
							if (board[temp_y1][temp_x1] != '_')
							{
								if (chain1 == 0)
								{
									cell1 = board[temp_y1][temp_x1];
									chain1++;

									horiz_y.push_back(temp_y1);
									horiz_x.push_back(temp_x1);
								}
								else if (chain1 > 0)
								{
									if (board[temp_y1][temp_x1] == cell1)
									{
										chain1++;
										horiz_y.push_back(temp_y1);
										horiz_x.push_back(temp_x1);
									}
									else
									{
										if (chain1 == 1 || chain1 >= k)
										{
											adt_cell = true;
											cell1 = board[temp_y1][temp_x1];

											horiz_y.push_back(temp_y1);
											horiz_x.push_back(temp_x1);
										}
										else
										{
											horiz_y.clear();
											horiz_x.clear();
											cell1 = board[temp_y1][temp_x1];
											horiz_y.push_back(temp_y1);
											horiz_x.push_back(temp_x1);
											chain1 = 1;
										}
									}
								}
							}
							else if (board[temp_y1][temp_x1] == '_' && chain1 < k)
							{
								chain1 = 0;
								horiz_y.clear();
								horiz_x.clear();
							}
							else if (board[temp_y1][temp_x1] == '_' && chain1 >= k)
							{
								break;
							}
							
							temp_x1--;
							temp_y1--;
						}

						if (chain1 >= k)
						{
							for (int a = 0; a < horiz_y.size(); a++)
							{
								if (board[horiz_y[a]][horiz_x[a]] == 'B')
								{
									if (adt_cell == true)
									{
										playingB--;
										adt_cell = false;
									}
									else
									{
										playingB--;
										reserveB++;
									}
								}
								else if (board[horiz_y[a]][horiz_x[a]] == 'W')
								{
									if (adt_cell == true)
									{
										playingW--;
										adt_cell = false;
									}
									else
									{
										playingW--;
										reserveW++;
									}
								}
								board[horiz_y[a]][horiz_x[a]] = '_';
							}
						}

							
						if (lefty1 < 2 * size - 1)
						{
							leftx1--;
							lefty1++;
						}
						else
							leftx1 -= 2;
					}
				}
				else
					cout << "BAD_MOVE_ROW_IS_FULL" << endl;
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
			if (correct_row_length == false || correct_whites_num == false || correct_blacks_num == false)
			{
				cout << "EMPTY_BOARD" << endl;
			}
			else if(correct_row_length == true && correct_whites_num == true && correct_blacks_num == true)
			{
				cout << size << " " << k << " " << allW << " " << allB << endl;

				cout << reserveW << " " << reserveB << " " << active_player << endl;

				for (int i = 1; i < 2 * size; i++)
				{
					for (int j = 2; j < 4 * size + 1; j++)
					{
						if (board[i][j] == '+') cout << " ";
						else cout << board[i][j];
					}
					cout << "\n";
				}
			}
			commands.clear();
		}
	}
	return 0;
}