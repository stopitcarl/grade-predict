#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>

#define MIN(a, b) (a < b ? a : b)

using namespace std;

/*
Input:
Number of students (studentNum),Number of friendships (linkNum)
studentGrade (of student 1)
studentGrade (of student 2)
studentGrade (of student 3)
...
student1 student2
student1 student3
student2 student5
...

Output
grade (of student 1)
grade (of student 2)
grade (of student 3)
grade (of student 4)
*/

// ###################### Global variables ####################################################
int studentNum;                 // Number of vertices
int linkNum;                    // Number of edges
vector<vector<uint> *> friends; // Vector of vertices
vector<uint> students;          // List of students
int *grades;                    // List of grades
bool *visited;                  // List with visited status of students

// ###################### Node ################################################################

// ###################### Input Handling ######################################################
void readInput()
{
    // Read the number of students and friendships
    if (!scanf("%u,%u", &studentNum, &linkNum))
        exit(-1);

    // Shorten the nodes list
    friends.resize(studentNum);

    // Initialize all the arrays
    grades = new int[studentNum];
    visited = new bool[studentNum];
    students = vector<uint>();
    students.resize(studentNum);

    // Initialize the nodes
    ushort grade = 0;
    for (int i = 0; i < studentNum; i++)
    {
        if (!scanf("%hu", &grade))
            exit(-1);
        else
            friends[i] = new vector<uint>();
        grades[i] = grade;
        students[i] = i;
    }

    // Update the adjacencies list of each vertex
    unsigned int id = 0;
    unsigned int friendId = 0;
    for (int i = 0; i < linkNum; i++)
        if (scanf("%u %u", &id, &friendId) > 0)
            (*friends[friendId - 1]).push_back(id - 1);
        else
            exit(-1);
}

// ###################### Algorithms  #########################################################
void propagate(uint start)
{

    stack<uint> stack;
    uint s;
    // Push the current source node.
    stack.push(start);
    int bestGrade = grades[start];

    while (!stack.empty())
    {
        // Pop a vertex from stack and print it
        s = stack.top();
        stack.pop();

        // Stack may contain same vertex twice. So
        // we need to print the popped item only
        // if it is not visited.
        if (!visited[s])
        {
            int currentGrade = grades[s];
            if (currentGrade > bestGrade)
                continue;
            else
                grades[s] = bestGrade;

            visited[s] = true;
        }

        // Get all adjacent vertices of the popped vertex s
        // If a adjacent has not been visited, then push it
        // to the stack.
        for (uint buddy : *friends[s])
            if (!visited[buddy])
                stack.push(buddy);
    }
}

// For the sorting algorithm
bool compare(const int a, const int b)
{
    return grades[a] < grades[b];
}

// ###################### Main ################################################################
int main()
{
    friends = vector<vector<uint> *>();

    // Input
    readInput();

    sort(students.begin(), students.end(), compare);
    while (!students.empty())
    {
        uint student = students.back();
        if (!visited[student])
            propagate(student);
        students.pop_back();
    }

    // Print result
    for (int i = 0; i < studentNum; i++)
        printf("%d\n", grades[i]);

    // Free allocs
    delete[] grades;
    delete[] visited;

    return 0;
}
