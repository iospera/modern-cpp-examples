#include <memory>
#include <optional>
#include <vector>
#include <deque>
#include <functional>
#include <iostream>

using namespace std;

//
// See http://rosettacode.org/wiki/Tree_traversal
//
// We're not using pointers, just references and optional types.
// This code is mostly an exercise in how readably we can write
// modern c++ without losing efficiency.
//
// Compiled using (tested using clang):
//   c++ -std=c++17 -Wall -o tree_traversal tree_traversal.c++
//

struct Node
{
  optional<reference_wrapper<Node>> left;
  optional<reference_wrapper<Node>> right;
  int value;

  // The various (con-)/(de-)structors are only here
  // for logging purposes. They're not actually
  // necessary.
  Node()
  {
    // We should only see 9 of these
    cout << "Node constructed" << endl;
  }

  // we should see zero of these
  Node(const Node& source) :
    left(source.left),
    right(source.right),
    value(source.value)
  {
    cout << "Copy constructed" << endl;
  }

  // we should see zero of these
  Node(Node && source) :
    left(move(source.left)),
    right(move(source.right)),
    value(move(source.value))
  {
    cout << "Move constructed" << endl;
  }

  ~Node()
  {
    // We should only see 9 of these
    cout << "Node deleted" << endl;
  }
};


void preorder(optional<reference_wrapper<Node>> current, vector<reference_wrapper<Node>> &output)
{
  if (current)
    {
      Node &node = *current; // Using a local variable reference enables the vector to understand what we're adding
                             // otherwise we'd have to use something like current.value().get().left to extract the
                             // Node object from the optional and reference_wrapper
      output.push_back(node);
      preorder(node.left, output);
      preorder(node.right, output);
    }
}

void inorder(optional<reference_wrapper<Node>> current, vector<reference_wrapper<Node>> &output)
{
  if (current)
    {
      Node &node = *current;
      inorder(node.left, output);
      output.push_back(node);
      inorder(node.right, output);
    }
}

void postorder(optional<reference_wrapper<Node>> current, vector<reference_wrapper<Node>> &output)
{
  if (current)
    {
      Node &node = *current;
      postorder(node.left, output);
      postorder(node.right, output);
      output.push_back(node);
    }
}

void levelorder(optional<reference_wrapper<Node>> root, vector<reference_wrapper<Node>> &output)
{
  if (root)
    {
      deque<reference_wrapper<Node>> queue;
      queue.push_back(*root);

      while (!queue.empty())
        {
          Node &node = queue.front(); queue.pop_front();
          output.push_back(node);
          if (node.left)
            {
              queue.push_back(*node.left); // Note: the '.' in (*node.left) has higher operator precedence than the '*'
                                           // so we're equivalent to (*(node.left))
            }
          if (node.right)
            {
              queue.push_back(*node.right); // Note: the '.' in (*node.right) has higher operator precedence than the '*'
            }
        }
    }
}

int main(int, char**)
{
  Node nodes[9];
  int i = 1;
  for (auto &n: nodes)
    {
      n.value = i;
      i++;
    }

  Node &root = nodes[0];
  nodes[0].left = nodes[1];
  nodes[1].left = nodes[3];
  nodes[3].left = nodes[6];
  nodes[2].left = nodes[5];
  nodes[5].left = nodes[7];
  nodes[0].right = nodes[2];
  nodes[1].right = nodes[4];
  nodes[5].right = nodes[8];

  vector<reference_wrapper<Node>> pre_ordered;
  vector<reference_wrapper<Node>> in_ordered;
  vector<reference_wrapper<Node>> post_ordered;
  vector<reference_wrapper<Node>> level_ordered;

  cout << "pre-order: ";
  preorder(root, pre_ordered);
  for (Node &n: pre_ordered)
    {
      cout << n.value << " ";
    }

  cout << endl << "in-order: ";
  inorder(root, in_ordered);
  for (Node &n: in_ordered)
    {
      cout << n.value << " ";
    }

  cout << endl << "post-order: ";
  postorder(root, post_ordered);
  for (Node &n: post_ordered)
    {
      cout << n.value << " ";
    }

  cout << endl << "level-order: ";
  levelorder(root, level_ordered);
  for (Node &n: level_ordered)
    {
      cout << n.value << " ";
    }

  cout << endl;

  return EXIT_SUCCESS;
}
