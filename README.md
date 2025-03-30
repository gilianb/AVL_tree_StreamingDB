

# AVL Tree Streaming Database

## Overview

This repository contains an implementation of an AVL Tree optimized for streaming database applications. The AVL Tree is a self-balancing binary search tree that ensures efficient data operations, making it ideal for dynamic datasets.

## Features

- **Self-Balancing**: Automatically maintains balance to ensure O(log n) operations.
- **Efficient Operations**: Supports fast insertions, deletions, and lookups.
- **Stream Processing**: Designed to handle continuous data streams effectively.
- **Robust and Scalable**: Suitable for large-scale applications.

## Technologies

- **Language**: C++
- **Build System**: CMake


### Prerequisites

- C++ Compiler (e.g., GCC 9.0+)
- CMake 3.10 or higher

### Steps

1. Clone the repository:
   ```bash
   git clone https://github.com/gilianb/AVL_tree_StreamingDB.git
   cd AVL_tree_StreamingDB
   ```

2. Build the project:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

## Usage

Here's a simple example to get started with the AVL Tree:

```cpp
#include "AVLTree.h"

int main() {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.remove(10);
    bool exists = tree.search(20);  // Returns true
    return 0;
}
```

## Performance

- **Time Complexity**:
  - Insert: O(log n)
  - Delete: O(log n)
  - Search: O(log n)

## Testing

To run the tests, execute the following command in the build directory:

```bash
./run_tests
```

## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Commit your changes.
4. Push to your fork and submit a pull request.


## Contact

For questions or suggestions, please contact:

- **Gilian B.**
- GitHub: [@gilianb](https://github.com/gilianb)
- email: gilian.bns@gmail.com

---

Feel free to star the repository if you find it useful! 🌟

---
