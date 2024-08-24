# Data Structures and Algorithms: Analysis and Design
### Author: Zane Milo Deso
### Date: 8/21/2024


## Problem Statement

As a computer science student at Southern New Hampshire University, I was tasked with designing a command-line interface (CLI) application to assist a fictional university's academic advisors in accessing course information for students. The core problem was to identify the most suitable data structure to manage and retrieve course data efficiently.

## Approach to the Problem

To address the problem, I first evaluated how the data was being provided—in this case, through a CSV file. I then analyzed various data structures, including vectors, linked lists, hash maps, and binary search trees, to determine which would best meet the needs of the advisors.

I ultimately chose a binary search tree due to its robustness and efficiency. As the course list grows, advisors benefit from consistently fast access times, which would not be as optimized with other data structures. To support this decision, I included a runtime analysis of the data structures within the project's use case. By thoroughly understanding both the use case and the data structures, I was able to design a solution that was optimized from the outset and capable of maintaining high performance as the course list expands.

## Overcoming Roadblocks

During the development process, I encountered several roadblocks:

Debugging Errors: I frequently encountered errors while developing the program. To overcome these, I regularly consulted resources such as Stack Overflow, YouTube, GeeksforGeeks, and W3Schools to troubleshoot and debug the issues.

Tracking Data Flow: Initially, I struggled to follow the flow of where courses were being stored. To resolve this, I slowed down and mapped out how each data structure worked within the program and interacted with one another. This helped me realize that I needed to store the course structure in a node before inserting it into the binary search tree, rather than directly storing pointers to the course structure.

## Expansion of Software Design Approach

Working on this project has significantly expanded my approach to software design. It provided me with a concrete understanding of how to apply the appropriate data structures and algorithms to real-world problems. I now have the ability to evaluate which data structure would be most effective for a given problem, and I can recognize the trade-offs involved—often in terms of time or space complexity.

This newfound insight has boosted my confidence in my software design skills.

## Evolution of Coding Practices

The experience has also evolved the way I write programs that are maintainable, readable, and adaptable:

Maintainability and Readability: I have learned how class objects interact to form the foundation of data structures that are not only highly efficient but also easily readable. Since these data structures are standard practices in the industry, anyone reviewing my code can easily understand the data flow and logic of the processes.

Adaptability: My software has become more adaptable as these data structures can be applied to various common use cases. This knowledge has provided me with a strong foundation for designing and implementing highly optimized, clean code.

## Code Example within ProjectTwo.cpp

The following code is the portion of the project responsible for sorting the courses into alphanumeric order and displaying those results:

```
void BinarySearchTree::inOrder(Node* node) {

    if (node == nullptr) {  // Base Case
        return;
    }

    inOrder(node->left);  // Recurse down all the way left
    displaycourse(node->course);

    inOrder(node->right);  // Then Recurse all the way right
}

void BinarySearchTree::displaycourse(Course course) {
    cout << course.courseId << ": " << course.title  << endl;
    return;
}

```

Runtime analysis can be located within the CS_300_Project_One.docx file.

     
