#ifndef MAZE_H
#define MAZE_H


class Maze {
    public:
        Maze(int w, int h);
        virtual ~Maze();

        void generate();
        int field(int x, int y);
        int getWidth();
        int getHeight();
        int getEndX();
        int getEndY();


    protected:

    private:
        int width;
        int height;
        int endX;
        int endY;
        int **board;
};

#endif // MAZE_H
