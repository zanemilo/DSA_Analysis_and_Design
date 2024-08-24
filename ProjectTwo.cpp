//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Zane Milo Deso
// Version     : 1.0
// Description : Project Two Submission
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <string>
#include <vector>


using namespace std;


//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold course information
struct Course {
    string courseId; // unique identifier
    string title;
    vector<string> prerequisites;
    Course() {}
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string courseId);
    void deleteTree(Node* node);
    void displaycourse(Course course);
    Node* minValueNode(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(Course course);
    void Remove(string courseId);
    Course Search(string courseId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    deleteTree(root);
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {

    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    preOrder(root);
}



/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        addNode(root, course);
    }
}

/**
 * Remove a course
 */
void BinarySearchTree::Remove(string courseId) {
    removeNode(root, courseId);
}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseId) {
    // set current node equal to root
    Node* currNode = root;

    // keep looping downwards until bottom reached or matching courseId found
    while (currNode != nullptr) {
        // if match found, return current course
        if (currNode->course.courseId == courseId) {
            return currNode->course;
        }

        // if course is smaller than current node then traverse left
        if (courseId < currNode->course.courseId) {
            currNode = currNode->left;
        }
        else {  // else larger so traverse right
            currNode = currNode->right;
        }

    }

    Course course;
    return course;
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course course to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    if (course.courseId < node->course.courseId) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        else {
            addNode(node->left, course);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            addNode(node->right, course);
        }
    }
}

void BinarySearchTree::inOrder(Node* node) {

    if (node == nullptr) {  // Base Case
        return;
    }

    inOrder(node->left);  // Recurse down all the way left
    displaycourse(node->course);

    inOrder(node->right);  // Then Recurse all the way right
}

void BinarySearchTree::postOrder(Node* node) {

    if (node == nullptr) {  // Base Case
        return;
    }

    postOrder(node->left);
    postOrder(node->right);
    displaycourse(node->course);

}

void BinarySearchTree::preOrder(Node* node) {

    if (node == nullptr) {  // Base Case
        return;
    }
    displaycourse(node->course);


    postOrder(node->left);
    postOrder(node->right);
}

/**
 * Remove a course from some node (recursive)
 */
Node* BinarySearchTree::removeNode(Node* node, string courseId) {

    if (node == nullptr) {
        return node;
    }

    if (courseId < node->course.courseId) {
        node->left = removeNode(node->left, courseId);
    }
    else if (courseId > node->course.courseId) {
        node->right = removeNode(node->right, courseId);
    }
    else {  // Node with only one child or no child
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // Node with two children: Get the smallest in the right subtree
        Node* temp = minValueNode(node->right);

        // Copy the inorder successor's content to this node
        node->course = temp->course;

        // Delete the inorder successor
        node->right = removeNode(node->right, temp->course.courseId);
    }
    return node;
}

/**
 * Helper method to make recursive calls to delete BST
 */
void BinarySearchTree::deleteTree(Node* node) {

    if (node == nullptr) {  // Base case, check if curr node is empty
        return;
    }

    if (node->left != nullptr) {  // Recursive call on left nodes
        deleteTree(node->left);
    }
    if (node->right != nullptr) {  // Recursive call on left nodes
        deleteTree(node->right);
    }
    delete node;
}

/**
 * Helper method to display course information
 */
void BinarySearchTree::displaycourse(Course course) {
    cout << course.courseId << ": " << course.title  << endl;
    return;
}

/**
 * Helper method to return the smallest value node in the BST
 */
Node* BinarySearchTree::minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}



//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the course information to the console (std::out)
 *
 * @param course struct containing the course info
 */
void displayCourse(Course course) {
    cout << endl << course.courseId << ": " << course.title;

    // Check if there are any prerequisites
    if (!course.prerequisites.empty()) {
        cout << " | Prerequisites: ";
        // Iterate over the prerequisites vector and print each 
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];
            // Print a comma after each prerequisite except the last one
            if (i < course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
    }

    cout << endl; // End the line after printing the course information
}

/**
 * Load a CSV file containing courses into a BST
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the courses read
 */
void loadCourses(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file: " << csvPath << endl;

    ifstream file(csvPath);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << csvPath << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseId, title, prereq;
        vector<string> prerequisites;

        getline(ss, courseId, ',');  // First value: courseId
        getline(ss, title, ',');     // Second value: title

        // Remaining values: prerequisites
        while (getline(ss, prereq, ',')) {
            prerequisites.push_back(prereq);
        }

        // Create a Course object
        Course course;
        course.courseId = courseId;
        course.title = title;
        course.prerequisites = prerequisites;

        // Insert the course into the BST
        bst->Insert(course);
    }

    file.close();
    cout << "Courses loaded successfully." << endl;
}


/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    clock_t ticks;  // Define a timer variable
    
    BinarySearchTree* bst;  // Define a binary search tree to hold all courses
    bst = new BinarySearchTree();
    Course course;

    // Get file name
    string filename;
    cout << "Welcome to the course planner." << endl << endl;
    cout << "Input file name:" << endl;
    cin >> filename;

    string courseKey;

    int choice = 0;
    while (choice != 9) {
   
        cout << endl << "Menu:" << endl;
        cout << "  1. Load file data into Binary Search Tree" << endl;
        cout << "  2. Display all courses in alphanumerical order" << endl;
        cout << "  3. Print the title and prerequisites of an individual course given the courseId" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        // Check if the input is a valid integer
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a valid number." << std::endl;
            continue; // Skip the rest of the loop and prompt again
        }

        switch (choice) {

        case 1:

            // Initialize a timer variable before loading courses
            ticks = clock();

            //Method call to load the courses
            loadCourses(filename, bst);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            //cout << "time: " << ticks << " clock ticks" << endl;
            //cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            cout << endl;
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            // Get courseID from user
            cout << "Input course Id:" << endl;
            cin >> courseKey;
            course = bst->Search(courseKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!course.courseId.empty()) {
                
                displayCourse(course);
            }
            else {
                cout << "course Id " << courseKey << " not found." << endl;
            }

            //cout << "time: " << ticks << " clock ticks" << endl;
            //cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        default:
            std::cout << choice << " is an invalid option. Please try again." << std::endl;
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
