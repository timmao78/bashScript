#pragma once

#include "grid.h"
#include <vector>

class Board
{
public:
    Board()
    {
        /* NCURSES START */
        initscr();
        noecho();
        cbreak();

        int yMax, xMax;
        getmaxyx(stdscr, yMax, xMax);
        if (yMax < 25 || xMax < 55)
        {
            endwin();
            std::cout << "Terminal Window Not Big Enough!" << std::endl;
            initSuccess = false;
            initscr();
        }
        else
        {
            int yStart = (yMax - 22)/2;
            int xStart = (xMax - 51)/2;
            
            // Create a window for the game
            playWin =  newwin(17, 33, yStart, xStart);
            refresh();
            box(playWin, 0, 0);
            wrefresh(playWin);

            for (int i=0; i<=16; i+=1)
                for (int j=0; j<=32; j+=1)
                {
                    if (i%4==0 && j%8==0)
                        mvwprintw(playWin, i, j, "*");
                    else if ((i!=0 && i!=16 && i%4==0) && j%8!=0)
                        mvwprintw(playWin, i, j, "-");
                    else if (i%4!=0 && j%8==0 && j!=0 && j!=32)
                        mvwprintw(playWin, i, j, "|");
                }
                
            // Initialize grids
            for(int i=0; i<4; i++)
                for(int j=0; j<4; j++)
                {
                    grids[i][j].setNum(0);
                    grids[i][j].setIndex(i, j);
                    grids[i][j].printGrid(playWin);
                }   

            wrefresh(playWin);

            usrInput = 0;
            score = 0;
            gameOver = false;
            moved = true;

            infoWin =  newwin(17, 17, yStart, xStart+34);
            // box(infoWin, 0, 0);
            printScore(0);
            refresh();
            wrefresh(infoWin);

            statsWin =  newwin(6, 51, yStart+17, xStart);
            box(statsWin, 0, 0);
            refresh();
            wrefresh(statsWin);

            initSuccess = true;
        }

    }

    bool success() { return initSuccess; }

    void printGrids()
    {
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
            {
                grids[i][j].printGrid(playWin);
            }   
    }

    bool cantMerge()
    {
        for(int i=1; i<3; i++)
            for(int j=1; j<3; j++)
                if (grids[i][j].getNum()==0)
                {
                    analyzeMerge(std::to_string(i)+" "+std::to_string(j)+" is empty.");
                    return false;
                }
                else if (grids[i][j].getNum()==grids[i+1][j].getNum())
                {
                    analyzeMerge(std::to_string(i)+" "+std::to_string(j)+" is euqal to " + std::to_string(i+1)+" "+std::to_string(j));
                    return false;
                }
                else if (grids[i][j].getNum()==grids[i-1][j].getNum())
                {
                    analyzeMerge(std::to_string(i)+" "+std::to_string(j)+" is euqal to " + std::to_string(i-1)+" "+std::to_string(j));
                    return false;
                }
                else if (grids[i][j].getNum()==grids[i][j+1].getNum())
                {
                    analyzeMerge(std::to_string(i)+" "+std::to_string(j)+" is euqal to " + std::to_string(i)+" "+std::to_string(j+1));
                    return false;
                }
                else if (grids[i][j].getNum()==grids[i][j-1].getNum())
                {
                    analyzeMerge(std::to_string(i)+" "+std::to_string(j)+" is euqal to " + std::to_string(i)+" "+std::to_string(j-1));
                    return false;
                }
        
        if (grids[0][0].getNum()==grids[0][1].getNum())
        {
            analyzeMerge("00 is equal to 01");
            return false;
        } 
        else if (grids[0][0].getNum()==grids[1][0].getNum())
        {
            analyzeMerge("00 is equal to 10");
            return false;
        } 
        else if (grids[0][3].getNum()==grids[0][2].getNum())
        {
            analyzeMerge("03 is equal to 02");
            return false;
        } 
        else if (grids[0][3].getNum()==grids[1][3].getNum())
        {
            analyzeMerge("03 is equal to 13");
            return false;
        }
        else if (grids[3][0].getNum()==grids[3][1].getNum())
        {
            analyzeMerge("30 is equal to 31");
            return false;
        }
        else if (grids[3][0].getNum()==grids[2][0].getNum())
        {
            analyzeMerge("30 is equal to 20");
            return false;
        }
        else if (grids[3][3].getNum()==grids[3][2].getNum())
        {
            analyzeMerge("33 is equal to 32");
            return false;
        }
        else if (grids[3][3].getNum()==grids[2][3].getNum())
        {
            analyzeMerge("33 is equal to 23");
            return false;
        }

        for(int i=0; i<4; i++)
            if (grids[i][0].getNum()==0)
            {
                analyzeMerge(std::to_string(i)+" 0 is empty");
                return false;
            }

        for(int i=0; i<4; i++)
            if (grids[i][3].getNum()==0)
            {
                analyzeMerge(std::to_string(i)+" 3 is empty");
                return false;
            }

        for(int j=0; j<4; j++)
            if (grids[0][j].getNum()==0)
            {
                analyzeMerge("0"+std::to_string(j)+" is empty");
                return false;
            }

        for(int j=0; j<4; j++)
            if (grids[3][j].getNum()==0)
            {
                analyzeMerge("3"+std::to_string(j)+" is empty");
                return false;
            }

        analyzeMerge("CANT MERGE");
        return true;
    }

    void new2()
    {
        if (cantMerge())
            gameOver = true;

        else if (moved)
        {
            std::vector<int> v1;

            for(int i=0; i<4; i++)
                for(int j=0; j<4; j++)
                    if (grids[i][j].getNum()==0)
                        v1.push_back(i*4+j);

            if(v1.size()!=0)
            {
                int r = rand();
                int j = v1[r%v1.size()]%4;
                int i = (v1[r%v1.size()]-j)/4;
                grids[i][j].setNum(2);
                grids[i][j].printGrid(playWin);
                wrefresh(playWin);
                printStatus(std::to_string(i)+" " +std::to_string(j)+" "
                +std::to_string(v1.size()));   
            }
            moved = false;
        }

    }

    void printScore(int score)
    {
        mvwprintw(infoWin, 1, 1, ("Score: "+std::to_string(score)).c_str());
        wrefresh(infoWin);
    }

    void printUsrInput(std::string s)
    {
        mvwprintw(infoWin, 15, 1, "        ");
        mvwprintw(infoWin, 15, 1, s.c_str());
        wrefresh(infoWin);
    }

    void printStatus(std::string s)
    {
        mvwprintw(statsWin, 1, 1, "                         ");
        mvwprintw(statsWin, 1, 1, s.c_str());
        wrefresh(statsWin);
    }

    void reportMove(std::string s)
    {
        mvwprintw(statsWin, 2, 1, "                         ");
        mvwprintw(statsWin, 2, 1, s.c_str());
        wrefresh(statsWin);
    }

    void reportMerge(std::string s)
    {
        mvwprintw(statsWin, 3, 1, "                         ");
        mvwprintw(statsWin, 3, 1, s.c_str());
        wrefresh(statsWin);
    }

    void analyzeMerge(std::string s)
    {
        mvwprintw(statsWin, 4, 1, "                         ");
        mvwprintw(statsWin, 4, 1, s.c_str());
        wrefresh(statsWin);
    }

    ~Board()
    {
        /* NCURSES END */
        endwin();
    }

    void loop()
    {
        keypad(playWin, true);

        while(true)
        {
            if (gameOver)
            {
                printStatus("Game Over");
                while(true)
                {}
            }
            usrInput = wgetch(playWin);
            if (usrInput=='q')
                break;    
            else if(usrInput==KEY_UP)
            {
                reportMerge("");
                reportMove("");
                printUsrInput("UP");
                moveUp(0);
                moveUp(1);
                moveUp(2);
                moveUp(3);
                mergeUp(0);
                mergeUp(1);
                mergeUp(2);
                mergeUp(3);
                moveUp(0);
                moveUp(1);
                moveUp(2);
                moveUp(3);
                printGrids();
                printScore(score);

            }
            else if(usrInput==KEY_DOWN)
            {
                                reportMerge("");
                reportMove("");
                printUsrInput("DOWN");
                moveDown(0);
                moveDown(1);
                moveDown(2);
                moveDown(3);
                mergeDown(0);
                mergeDown(1);
                mergeDown(2);
                mergeDown(3);
                moveDown(0);
                moveDown(1);
                moveDown(2);
                moveDown(3);
                printGrids();
                printScore(score);
            }
            else if(usrInput==KEY_LEFT)
            {
                reportMerge("");
                reportMove("");
                printUsrInput("LEFT");
                moveLeft(0);
                moveLeft(1);
                moveLeft(2);
                moveLeft(3);
                mergeLeft(0);
                mergeLeft(1);
                mergeLeft(2);
                mergeLeft(3);
                moveLeft(0);
                moveLeft(1);
                moveLeft(2);
                moveLeft(3);
                printGrids();
                printScore(score);

            }
            else if(usrInput==KEY_RIGHT)
            {
                reportMerge("");
                reportMove("");
                printUsrInput("RIGHT");
                moveRight(0);
                moveRight(1);
                moveRight(2);
                moveRight(3);
                mergeRight(0);
                mergeRight(1);
                mergeRight(2);
                mergeRight(3);
                moveRight(0);
                moveRight(1);
                moveRight(2);
                moveRight(3);
                printGrids();
                printScore(score);
            }
            new2();
        }
    }
    void mergeUp(int j)
    {
        if (merge(0,j, 1,j))
            merge(2,j, 3, j);
        else if(!merge(1,j,2,j))
            merge(2,j, 3,j);
    }

    void mergeDown(int j)
    {
        if (merge(3,j, 2,j))
            merge(1,j, 0, j);
        else if(!merge(2,j,1,j))
            merge(1,j, 0,j);
    }

    void moveRight(int i)
    {
        for(int j1=3; j1>0; j1--)
            if(grids[i][j1].getNum()==0)
            {
                for(int j2=j1-1; j2>=0; j2--)
                    if (grids[i][j2].getNum()!=0)
                    {
                        grids[i][j1].setNum(grids[i][j2].getNum());
                        grids[i][j2].setNum(0);
                        moved = true;
                        reportMove("MOVE RIGHT");
                        break;
                    }

            }
    }
    void moveLeft(int i)
    {
        for(int j1=0; j1<3; j1++)
            if(grids[i][j1].getNum()==0)
            {
                for(int j2=j1+1; j2<=3; j2++)
                    if (grids[i][j2].getNum()!=0)
                    {
                        grids[i][j1].setNum(grids[i][j2].getNum());
                        grids[i][j2].setNum(0);
                        moved = true;
                        reportMove("MOVE LEFT");
                        break;
                    }

            }
    }

    void moveDown(int j)
    {
        for(int i1=3; i1>0; i1--)
            if(grids[i1][j].getNum()==0)
            {
                for(int i2=i1-1; i2>=0; i2--)
                    if (grids[i2][j].getNum()!=0)
                    {
                        grids[i1][j].setNum(grids[i2][j].getNum());
                        grids[i2][j].setNum(0);
                        moved = true;
                        reportMove("MOVE DOWN");
                        break;
                    }

            }
    }

    void moveUp(int j)
    {
        for(int i1=0; i1<3; i1++)
            if(grids[i1][j].getNum()==0)
            {
                for(int i2=i1+1; i2<=3; i2++)
                    if (grids[i2][j].getNum()!=0)
                    {
                        grids[i1][j].setNum(grids[i2][j].getNum());
                        grids[i2][j].setNum(0);
                        moved = true;
                        reportMove("MOVE UP");
                        break;
                    }

            }
    }

    void mergeRight(int i)
    {
        if (merge(i, 3, i, 2))
            merge(i, 1, i, 0);
        else if(!merge(i, 2, i, 1))
            merge(i, 1, i, 0);
    }

    void mergeLeft(int i)
    {
        if (merge(i, 0, i, 1))
            merge(i, 2, i, 3);
        else if(!merge(i, 1, i, 2))
            merge(i, 2, i, 3);
    }

    bool merge(int i1, int j1, int i2, int j2)
    {
        if (grids[i1][j1].getNum()==grids[i2][j2].getNum() && grids[i1][j1].getNum()!=0)
        {
            score+=grids[i2][j2].getNum();
            grids[i1][j1].setNum(grids[i2][j2].getNum()*2);
            grids[i2][j2].setNum(0);
            moved = true;
            reportMerge("MERGED");
            return true;
        }
        else
        {
            return false;
        }
        
    }

private:
    WINDOW * playWin;
    WINDOW * infoWin;
    WINDOW * statsWin;

    Grid grids[4][4];
    int usrInput;
    int score;
    bool gameOver;
    bool moved;
    bool initSuccess;
};
