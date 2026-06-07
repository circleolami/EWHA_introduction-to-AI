/* 
Exercise 1
Consider a simple maze with 5 rooms numbered by 1 through 5, where some of them are connected each other. 
The goal is to exit the maze, i.e., to arrive at EXIT, via room 2 or room 5. 
An agent in any room has a goal to exit (i.e., arrive at EXIT) the maze by moving to other rooms. 
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STATES 6
#define GAMMA 0.8
#define ITERATIONS 1000

// Reward Matrix
int R[STATES][STATES] = {
    {-1, -1, -1, -1, 0, -1},
    {-1, -1, -1, 0, -1, 100},
    {-1, -1, -1, 0, -1, -1},
    {-1, 0, 0, -1, 0, -1},
    {0, -1, -1, 0, -1, 100},
    {-1, 0, -1, -1, 0, 100}
};

// Print Matrix 
double Q[STATES][STATES] = { 0 };

// max Q value
double maxQ(int state) {
    double max = 0.0;

    for (int i = 0; i < STATES; i++) {
        if (max < Q[state][i])
            max = Q[state][i];
    }
    return max;
}

// choose possible action
int p_action(int state) {
    int action[STATES];
    int count = 0;

    for (int i = 0; i < STATES; i++) {
        if (R[state][i] != -1)
            action[count++] = i;
    }
    return action[rand() % count];
}

// Q-Learning
void train() {
    int state, action;

    for (int i = 0; i < ITERATIONS; i++) {
        state = rand() % STATES;
        action = p_action(state);

        Q[state][action] = R[state][action] + GAMMA * maxQ(action);
    }
}

void printQTable() {
    printf("Q_table = \n");
    for (int i = 0; i < STATES; i++) {
        for (int j = 0; j < STATES; j++)
            printf("%8.1lf", Q[i][j]);
        printf("\n");
    }
}

void OptimalPath(int start) {
    int state = start;

    // avoid infinite loop
    for (int i = 0; i < 20; i++)
        if (state == 5) 
            return;

    double max = -1.0;
    int nextState = state;

    for (int i = 0; i < STATES; i++) {
        if (Q[state][i] > max) { max = Q[state][i]; nextState = i; }
        state = nextState;
    }


}

int main() {

    srand((unsigned int)time(NULL));

    train();
    printQTable();
    printf("\nStart Room : 3\n");
    OptimalPath(2);

    return 0;

}
