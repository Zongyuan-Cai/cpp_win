// Fig. 16.5~16.7: Processing new failures.
// Three ways to handle memory allocation failure.

#include <iostream>
#include <new>       // standard operator new, bad_alloc, set_new_handler
#include <cstdlib>   // abort
using std::cout;
using std::cerr;
using std::endl;
using std::bad_alloc;
using std::set_new_handler;
using std::abort;

// -------- Example 1: Pre-standard new returning 0 --------
void demoOldStyleNew()
{
    cout << "\n--- Old-style: new returning 0 ---\n";
    double *ptr[50];

    for (int i = 0; i < 50; i++) {
        ptr[i] = new double[50000000];

        if (ptr[i] == 0) {  // did new fail to allocate memory?
            cerr << "Memory allocation failed for ptr[" << i << "]\n";
            // Clean up previously allocated memory
            for (int j = 0; j < i; j++)
                delete[] ptr[j];
            break;
        }
        else {  // successful memory allocation
            cout << "Allocated 50000000 doubles in ptr[" << i << "]\n";
        }
    }
}

// -------- Example 2: Standard new throwing bad_alloc --------
void demoStandardNew()
{
    cout << "\n--- Standard: new throwing bad_alloc ---\n";
    double *ptr[50];

    try {
        for (int i = 0; i < 50; i++) {
            ptr[i] = new double[50000000];  // may throw exception
            cout << "Allocated 50000000 doubles in ptr[" << i << "]\n";
        }
    }
    catch (bad_alloc &memoryAllocationException) {
        cerr << "Exception occurred: "
             << memoryAllocationException.what() << endl;
    }
}

// -------- Example 3: set_new_handler --------
void customNewHandler()
{
    cerr << "customNewHandler was called";
    abort();
}

void demoNewHandler()
{
    cout << "\n--- set_new_handler ---\n";
    double *ptr[50];

    // Register customNewHandler to handle failed memory allocations
    set_new_handler(customNewHandler);

    for (int i = 0; i < 50; i++) {
        ptr[i] = new double[50000000];  // customNewHandler called on failure
        cout << "Allocated 50000000 doubles in ptr[" << i << "]\n";
    }
}

int main()
{
    // Note: These demos are designed to show the concept.
    // On modern systems with lots of RAM, they may succeed many times
    // before actually failing.

    cout << "Note: These examples allocate large amounts of memory.\n"
         << "They demonstrate the concepts from the textbook.\n";

    demoOldStyleNew();
    // Uncomment to test standard new (will crash intentionally):
    // demoStandardNew();
    // demoNewHandler();

    return 0;
}
