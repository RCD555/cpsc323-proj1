#include <iostream>

using namespace std;


// Function to calculate the sum of two integers
int calculate_sum(int a, int b) {
    // This function calculates the sum of two numbers
    return a + b;
}


// Main function
int main() {
    int num1 = 10;
    int num2 = 20;

    // Calculate the sum
    int result = calculate_sum(num1, num2);

    // Print the result
    cout << "Sum: " << result << endl;

    return 0;
}
