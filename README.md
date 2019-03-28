# modern-cpp-examples
## Playing with C++17

### tree_traversal.c++
See [Rosetta Code](http://rosettacode.org/wiki/Tree_traversal)

We're not (directly) using pointers, just references and optional types.
This code is mostly an exercise in how readably we can write
modern c++ without losing efficiency.

Compiled using (for clang):
`c++ -std=c++17 -Wall -o tree_traversal tree_traversal.c++`

`$ ./tree_traversal`
```
Node constructed
Node constructed
Node constructed
Node constructed
Node constructed
Node constructed
Node constructed
Node constructed
Node constructed
pre-order: 1 2 4 7 5 3 6 8 9 
in-order: 7 4 2 5 1 8 6 9 3 
post-order: 7 4 5 2 8 9 6 3 1 
level-order: 1 2 3 4 5 6 7 8 9 
Node deleted
Node deleted
Node deleted
Node deleted
Node deleted
Node deleted
Node deleted
Node deleted
Node deleted
```

I'm not fond of std::reference_wrapper, because I find it too easy to keep hold of something beyond the original
object lifetime. Effectively it is using a pointer under the covers, and shared_ptr would probably be
safer more of the time. Return-value-optimization and move constructors are wonderful, but it's still possible to shoot
yourself in the foot returning references to objects.
