# Note  :
> ` We can place the book only in the given order and not random order.
`
# Approach 1: Recursion

# Intuition
The simplest way to approach this problem is by using recursion. The idea is to `try placing each book either on a new shelf or on the current shelf`, and recursively compute the minimum height of the bookcase for each choice.


# Approach
In the recursive approach, we solve the problem by breaking it down into subproblems. `We define our state as three variables: index, remaining_width, and current_height.`

- index denotes the number of books placed so far.
- remaining_width denotes the width available on the current shelf.
- current_height denotes the maximum height of the current shelf.

`For each book, we have two options:
`

`Place on the Same Level`: We can place the book on the same level if the remaining_width is greater than or equal to the width of the current book. T`he height of the current level will then be the maximum of the heights of all the books on this level.`

`Place on a New Level`: If we place the book on a new level, the height of this level will become the height of the current book and the remaining width will be ShelfWidth - width of the current book.

# Algorithm
 1. Base Case: If we have placed all the books (index >= n), return the current height of the bookcase.
 2. Recursive Case: For each book, We have two options
    - Place on same level if remaining width is greater than width of current book and update remaining width & current_height
    - Place on new level and update remaining width

 3. Return the Minimum Height obtained from the two options.



# Code
```c++ []
class Solution {
public:
    int dfs(vector<vector<int>>& books, int shelfWidth, int index, int remaining_width, int current_height) {
        if (index == books.size()) return current_height;
        
        // Place on a new level
        int place_on_new_level = current_height + dfs(books, shelfWidth, index + 1, shelfWidth - books[index][0], books[index][1]);
        
        // Place on the same level if possible
        int place_on_same_level = INT_MAX;
        if (remaining_width >= books[index][0]) {
            place_on_same_level = dfs(books, shelfWidth, index + 1, remaining_width - books[index][0], max(current_height, books[index][1]));
        }
        
        return min(place_on_same_level, place_on_new_level);
    }

    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        return dfs(books, shelfWidth, 0, shelfWidth, 0);
    }
};

```
```Java []
class Solution {
    public int dfs(int[][] books, int shelfWidth, int index, int remaining_width, int current_height) {
        if (index == books.length) return current_height;

        // Place on a new level
        int place_on_new_level = current_height + dfs(books, shelfWidth, index + 1, shelfWidth - books[index][0], books[index][1]);

        // Place on the same level if possible
        int place_on_same_level = Integer.MAX_VALUE;
        if (remaining_width >= books[index][0]) {
            place_on_same_level = dfs(books, shelfWidth, index + 1, remaining_width - books[index][0], Math.max(current_height, books[index][1]));
        }

        return Math.min(place_on_same_level, place_on_new_level);
    }

    public int minHeightShelves(int[][] books, int shelfWidth) {
        return dfs(books, shelfWidth, 0, shelfWidth, 0);
    }
}
```
```python []
class Solution:
    def dfs(self, books, shelf_width, index, remaining_width, current_height):
        if index == len(books):
            return current_height

        # Place on a new level
        place_on_new_level = current_height + self.dfs(books, shelf_width, index + 1, shelf_width - books[index][0], books[index][1])

        # Place on the same level if possible
        place_on_same_level = float('inf')
        if remaining_width >= books[index][0]:
            place_on_same_level = self.dfs(books, shelf_width, index + 1, remaining_width - books[index][0], max(current_height, books[index][1]))

        return min(place_on_same_level, place_on_new_level)

    def minHeightShelves(self, books, shelf_width):
        return self.dfs(books, shelf_width, 0, shelf_width, 0)
```

# Complexity Analysis


Let N be the number of books.

- Time Complexity:  O(2^N)

The time complexity is O(2^N) because at each index, we are exploring two possibilities: placing the book on the current shelf or starting a new shelf. This results in a time complexity of  O(2^N), which will lead to a Time Limit Exceeded error for larger values of  N.

- Space Complexity:  O(N)

The space complexity is O(N) due to the recursion stack. The maximum depth of the recursion stack is equal to the number of books, resulting in linear space usage.

# Approach 2: Recursion + Memoization

# Intuition
To optimize the recursive approach, we can use memoization to store the results of subproblems and avoid redundant calculations. We define a helper function dfs(i, currHeight, remWidth) that returns the minimum height of the bookcase for placing books from index i to the end. We can use a 2 Dimensional array to store the result of solved subproblem .(Explained why we don't need 3-Dimensional memo array even though the dfs function has 3 states at the end, Please have a look at it to understand better)

# Approach
 We will define a memo 2 Dimensional array with dimension **`Books.size() * ShelfWidth+1`** to store the result obtained for a subproblem. If we encounter the subproblem again, we will directly return the result without computing it again, thus reducing the time complexity.

# Algorithm
 1. Base Case: If we have placed all the books (index >= n), return the current height of the bookcase.
 2. If the subproblem is already solved, return the already stored answer.
 3. Recursive Case: For each book, We have two options
    - Place on same level if remaining width is greater than width of current book
    - Place on new level and update remaining width=ShelfWidth-thickness of book[index] and height as Max(curr_height,height of book[index])

 4. Store the Minimum Height obtained from the two options and Return the same.



# Code
```c++ []
class Solution {
public:
    int dfs(vector<vector<int>>& books, int shelfWidth, int index, int remaining_width, int current_height, vector<vector<int>>& memo) {
        if (index == books.size()) return current_height;
        if (memo[index][remaining_width] != -1) return memo[index][remaining_width];

        // Place on a new level
        int place_on_new_level = current_height + dfs(books, shelfWidth, index + 1, shelfWidth - books[index][0], books[index][1], memo);
        
        // Place on the same level if possible
        int place_on_same_level = INT_MAX;
        if (remaining_width >= books[index][0]) {
            place_on_same_level = dfs(books, shelfWidth, index + 1, remaining_width - books[index][0], max(current_height, books[index][1]), memo);
        }

        memo[index][remaining_width] = min(place_on_new_level, place_on_same_level);
        return memo[index][remaining_width];
    }

    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        vector<vector<int>> memo(books.size(), vector<int>(shelfWidth + 1, -1));
        return dfs(books, shelfWidth, 0, shelfWidth, 0, memo);
    }
};



```
```Java []
class Solution {
    public int minHeightShelves(int[][] books, int shelfWidth) {
        int n = books.length;
        int[][] memo = new int[n][shelfWidth + 1];
        for (int[] row : memo) {
            Arrays.fill(row, -1);
        }
        return dfs(books, shelfWidth, 0, shelfWidth, 0, memo);
    }

    public int dfs(int[][] books, int shelfWidth, int index, int remaining_width, int current_height, int[][] memo) {
        if (index == books.length) return current_height;
        if (memo[index][remaining_width] != -1) return memo[index][remaining_width];

        // Place on a new level
        int place_on_new_level = current_height + dfs(books, shelfWidth, index + 1, shelfWidth - books[index][0], books[index][1], memo);

        // Place on the same level if possible
        int place_on_same_level = Integer.MAX_VALUE;
        if (remaining_width >= books[index][0]) {
            place_on_same_level = dfs(books, shelfWidth, index + 1, remaining_width - books[index][0], Math.max(current_height, books[index][1]), memo);
        }

        memo[index][remaining_width] = Math.min(place_on_new_level, place_on_same_level);
        return memo[index][remaining_width];
    }
}

```
```python []

class Solution(object):
    def minHeightShelves(self, books, shelfWidth):
        n = len(books)
        memo = [[-1] * (shelfWidth + 1) for _ in range(n)]
        return self.dfs(books, shelfWidth, 0, shelfWidth, 0, memo)
    
    def dfs(self, books, shelfWidth, index, remaining_width, current_height, memo):
        if index == len(books):
            return current_height
        if memo[index][remaining_width] != -1:
            return memo[index][remaining_width]
        
        # Place on a new level
        place_on_new_level = current_height + self.dfs(books, shelfWidth, index + 1, shelfWidth - books[index][0], books[index][1], memo)
        
        # Place on the same level if possible
        place_on_same_level = float('inf')
        if remaining_width >= books[index][0]:
            place_on_same_level = self.dfs(books, shelfWidth, index + 1, remaining_width - books[index][0], max(current_height, books[index][1]), memo)
        
        memo[index][remaining_width] = min(place_on_new_level, place_on_same_level)
        return memo[index][remaining_width]



```
# Complexity Analysis
### Complexity Analysis

- Time Complexity: O(N × W)
  
  The time complexity is O(N × W), where N is the number of books and W is the shelf width. This is due to storing results of subproblems in a memoization table, which reduces the overall number of computations by avoiding redundant calculations.

- Space Complexity:  O(N × W)

  The space complexity is O(N × W) due to the memoization table and the recursion stack. The memoization table stores the results of subproblems, and the recursion stack's maximum depth is determined by the number of books.

# Why 2D DP For Memoization Instead of 3D DP?

In the memoization approach, we use a 2D memo array where `memo[index][remaining_width]` stores the minimum height for a given `index` and `remaining_width`. This is because the third variable, `current_height`, does not change for each combination of `index` and `remaining_width`. The highest book on the current shelf stays the same for a given `{index, remaining_width} pair`, so we don't need to include `current_height` in our memo array. Using a 3D array for memoization would just consume extra space without giving us any extra information.

# Approach 3: Using Dynamic Programming

# Approach
The dynamic programming approach aims to minimize the height of the bookshelf by considering every possible way to place the books on the shelves.

- State Definition: dp[i] represents the minimum height required to place the first i books on the shelves.
 
- State Transition: For each book i, consider placing it on the current shelf or starting a new shelf with this book. Update the minimum height required for the first i books accordingly.


# Algorithm
1. Initialization: Create a DP array dp of size n + 1 where n is the number of books.
   - Set dp[0] = 0 because no books mean zero height.

2. DP Transition: For each book i from 1 to n:
   - Initialize the remaining_width and height of the current shelf to shelfWidth & zero respectively.
   - Iterate backward from current_book to first book(which is at index 0), adding each book to the current shelf until the remaining width of the shelf is greater than 0.
   - Update dp[i] with the minimum height by considering the height of the shelf formed by books from j to i.

3. Final Result:
`dp[n] contains the minimum height of the bookshelf with all n books placed optimally.`



# Code
```c++ []
class Solution {
public:
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int n = books.size();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;

        for (int i = 1; i <= n; i++) {
            int remaining_width = shelfWidth, current_height = 0;
            for (int j = i-1; j >= 0; j--) {
                remaining_width -= books[j][0];
                if (remaining_width <0) break;
                current_height = max(current_height, books[j][1]);
                dp[i] = min(dp[i], dp[j] + current_height);
            }
        }

        return dp[n];
    }
};





```
```Java []
class Solution {
    public int minHeightShelves(int[][] books, int shelfWidth) {
        int n = books.length;
        int[] dp = new int[n + 1];
        Arrays.fill(dp, Integer.MAX_VALUE);
        dp[0] = 0;

        for (int i = 1; i <= n; i++) {
            int remaining_width = shelfWidth, currentHeight = 0;
            for (int j = i - 1; j >= 0; j--) {
                remaining_width -= books[j][0];
                if (remaining_width<0) break;
                currentHeight = Math.max(currentHeight, books[j][1]);
                dp[i] = Math.min(dp[i], dp[j] + currentHeight);
            }
        }

        return dp[n];
    }
}





```
```python []
class Solution(object):
    def minHeightShelves(self, books, shelfWidth):

        n = len(books)
        dp = [float('inf')] * (n + 1)
        dp[0] = 0

        for i in range(1, n + 1):
            remaining_width= shelfWidth
            current_height = 0
            for j in range(i - 1, -1, -1):
                remaining_width -= books[j][0]
                if remaining_width < 0:
                    break
                current_height = max(current_height, books[j][1])
                dp[i] = min(dp[i], dp[j] + current_height)

        return dp[n]


```
# Complexity Analysis


Let N be the number of books.

- Time Complexity:  O(N^2)

The time complexity is O(N^2) due to the nested loops that iterate through the books. The outer loop runs N times, and for each iteration, the inner loop runs up to N times in the worst case.

- Space Complexity:  O(N)

The space complexity is O(N) because we use a 1D DP array of size N+1 to store the minimum heights up to each book. This results in linear space usage.

# Why 1D DP Instead of 2D or 3D DP?

Think of it like packing books on shelves in a sequence.
 For each book, you either:

1. Start a new shelf.
2. Add it to the current shelf (if there's enough space).

By only storing the minimum height needed up to each book (in dp[i]), we can efficiently keep track of the best way to arrange all the books up to that point.

`Where did Remaining Width & current_height go ?`
 For each book, we calculate the remaining width & current height of the shelf dynamically in the inner loop.


