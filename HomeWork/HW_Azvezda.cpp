{
	...
    bool field[9][9];

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            field[i][j] = false;
        }
    }
	...
}

char getDir(int i)
{
	switch (i)
	{
	case (0):
		dir = 'l';
		break;
	case (1):
		dir = 'u';
		break;
	case (2):
		dir = 'r';
		break;
	case (3):
		dir = 'd';
		break;
	default:
		assert(false);
		break;
	}
}

bool aZvezda(int x, int y, int pole[17][17], bool field[9][9], int p)
{
    queue<pair<int, int>> frontier; //1
    frontier.push(make_pair(x / 2, y / 2)); //2
    field[x / 2][y / 2] = true; //3
    pair<int, int> current; //4
    pair<int, int> next; //5

    while (!frontier.empty()) //6--
    {
        current = frontier.front(); //7

        x = current.first; //8
        y = current.second; //9

        char dir; //10
        for (int i = 0; i < 4; ++i) //11--
        {
            dir = getDir(i)//12 
           
			next = step(x * 2, y * 2, dir, 2); //13
			if (!field[next.first / 2][next.second / 2] && !isWall(x * 2, y * 2, next.first, next.second, pole) && next.first >= 0) //14
			{
				frontier.push(make_pair(next.first / 2, next.second / 2)); //15
				field[next.first / 2][next.second / 2] = true; //16
			}
        }

        frontier.pop(); //17

        for (int j = 0; j < 9; j++) //18--
            if (field[8 - 8 * p][j]) //19
            {
                return true; //20
            }
    }
    return false; //21
}