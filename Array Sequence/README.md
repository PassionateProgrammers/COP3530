Time Complexity Analysis

Constructor: The constructor creates a data array of n elements so it runs in O(n) or linear time.

setAt: Since the value is accessed directly through its index, it runs in O(1) or constant time.

expandArray: Time for this depends on the size of the pre-expanded array as each element must be copied to the new array. It takes O(n) or linear time. This function only needs to run when there is no more memory, therfore the amortized time complexity is on average O(1)

insertAt/insertFirst: Worst case is insertFirst which is O(n) time because every element has to be shifted to the left. On average though, insertAt runs in O(n/2) time.

deleteFirst: Runs in O(n-1) or simply O(n) because n-1 elements are shifted to the left after the first element is deleted.

insertLast/deleteLast: Runs in O(1) or constant time because no elements have to be shifted.

printAll: Runs in O(n) time because every element is printed

Overall time complexity: O(n)

