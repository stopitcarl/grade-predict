#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>

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
int studentNum;               // Number of vertices
int linkNum;                  // Number of edges
vector<vector<uint>> friends; // Vector of vertices
uint *students;               // List of students
ushort *grades;               // List of grades
bool *visited;                // List with visited status of students

// ###################### Input Handling ######################################################
void readInput()
{
    // Read the number of students and friendships
    if (!scanf("%u,%u", &studentNum, &linkNum))
        exit(-1);

    // Initialize all the arrays
    grades = new ushort[studentNum];
    visited = new bool[studentNum];
    students = new uint[studentNum];
    friends = vector<vector<uint>>(studentNum);

    // Read the student grades
    ushort grade = 0;
    for (int i = 0; i < studentNum; i++)
    {
        if (!scanf("%hu", &grade))
            exit(-1);
        else
            friends[i] = vector<uint>();
        grades[i] = grade;
        students[i] = i;
    }

    // Read friendship list
    unsigned int id = 0;
    unsigned int friendId = 0;
    for (int i = 0; i < linkNum; i++)
        if (scanf("%u %u", &id, &friendId) > 0)
            friends[friendId - 1].push_back(id - 1);
        else
            exit(-1);
}

// ###################### Depth-first search ##################################################
void propagate(uint start)
{

    stack<uint> stack;
    uint friendId;
    // Push the current source node.
    stack.push(start);
    int bestGrade = grades[start];

    while (!stack.empty())
    {
        friendId = stack.top();
        stack.pop();

        // if it is not visited, recalculate grade
        if (!visited[friendId])
        {
            int currentGrade = grades[friendId];
            if (currentGrade > bestGrade)
                continue;
            else
                grades[friendId] = bestGrade;

            visited[friendId] = true;
        }

        // Get all buddies of the students s
        // If a adjacent has not been visited, then push it
        // to the stack.
        for (uint buddy : friends[friendId])
            if (!visited[buddy])
                stack.push(buddy);
    }
}

// Sort student id by grades
bool compare(const int a, const int b) { return grades[a] < grades[b]; }

// ###################### Main ################################################################
int main()
{

    friends = vector<vector<uint>>();

    // Input
    readInput();

    // Sort student grades
    sort(students, students + studentNum, compare);
    
    // Recalculate grades
    for (int i = studentNum - 1; i >= 0; i--)
    {
        uint student = students[i];
        if (!visited[student])
            propagate(student);
    }

    // Print result
    for (int i = 0; i < studentNum; i++)
        printf("%d\n", grades[i]);

    // Free allocs
    delete[] grades;
    delete[] visited;
    delete[] students;
    friends.clear();

    return 0;
}
