## Documentation and Usage Rules

### General Rules

*   **Data Structures**: Use `algobox::vector` instead of `std::vector`. This is already included in `algobox::core` as the member `v`.
*   **Accessing Data**: Use `operator[]` (e.g., `v[i]`) to access elements. Avoid using `.at()` if you want the rectangles be marked.
*   **Execution**: Always call `std::cin.get()` or a similar function after `algobox::algo_search`. This keeps the program and GUI window open.

### Rules for Search Algorithms

#### Function Parameters
Your search functions must use this format:
`search_function(algobox::core<T>& c, T target, ...)`

#### Updating the Tracker
To record steps for the GUI, you must update the tracker within your loops.
*   Use `c++` at the end of each loop iteration.

**Example:**
```cpp
// c is an object of algobox::core class
for (int i = 0; i < c.v.size(); i++) {
    // algorithm logic here
    c++; // moves to the next visualization step
}
```

#### Using algobox::dict
Use the dictionary `vars` to highlight specific indices on the screen (such as "low" or "high" in binary search).
*   The current index accessed by `v[i]` is automatically highlighted with a red rectangle and an arrow.
*   Additional markers can be set manually in the `vars` dictionary.

**Example:**
```cpp
c.vars["low"] = 0;
c.vars["high"] = c.v.size() - 1;
```

### Rules for Sort Algorithms

#### Function Parameters
Your sort functions must use this format:
`sort_function(algobox::core<T>& c, ...)`

#### Using swap()
Using the `swap()` to highlight changed indices on the screen in green and red.
*   Swapping elements manually is also allowed, but the rectangles will be marked in red only.

**Example:**
```cpp
if (c.v[j] > c.v[j+1]){
    c.v.swap(j, j+1);
}
```

#### Updating the Tracker
Updating the tracker is not necessary for the sorting algorithms, because each time an element is accessed or swaped, the whole vector state will be copied (and it is expensive).

### Rules for Tree Algorithms
*(To be added)*

### Rules for Graph Algorithms
*(To be added)*
