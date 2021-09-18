#include "../../contest/header.hpp"
/*
        Aho-Corasick: O(alpha_size * string_sum)
                In general, multiple pattern string matching
   tree/automaton.

                Keep in mind that find_all can be O(N*sqrt(N)) if no
   duplicate patterns. (N is total string length)

        Constraints:
                chars in the string are all in the interval
                [first, first + alpha_size - 1].
                This will not free some memory on object destruction.
                Duplicate patterns are allowed, empty patterns are not.

        Usage:
                Set alpha_size and the first char in the alphabet.
                Call constructor passing the list of pattern strings.
                Use one of find, find_all ... to process a text or do your
   own thing. To find the longest words that start at each position,
   reverse all input. Bottleneck in this code is memory allocation. For
   10^6 total string size, memory usage can be up to 300 Mb.

                You can save time:
                        list_node, match_list, match_list_last are only
   needed to list all matches. atm automaton table can be cut to reduce
   memory usage. The text processing stuff is also optional. Node memory
   can be one big array instead of vector.

        Author: Arthur Pratti Dadalto
*/
struct aho_corasick {
  enum {
    alpha_size = 26,  // Number of chars in the alphabet.
    first = 'a'       // First char.
  };
  struct list_node  // Simple linked list node struct.
  {
    int id;
    list_node *next;
    explicit list_node(int id, list_node *next) : id(id), next(next) {}
  };
  struct node {
    int fail = -1;         // node failure link (aka suffix link).
    int nmatches = 0;      // Number of matches ending in this
                           // node.
    int next[alpha_size];  // Next node in trie for each letter.
                           // Replace with unordered_map or list
                           // if memory is tight.
    int atm[alpha_size];   // Optional: Automaton state
                           // transition table. Simpler text
                           // processing.
    // Pointer to first node in linked list of matches.
    // List ends with null pointer.
    list_node *match_list = nullptr;
    // Internal: pointer to last node in list of matches
    // (before bfs), or null if empty list.
    list_node *match_list_last = nullptr;
    // Start with all invalid transitions.
    node() { memset(next, -1, sizeof(next)); }
  };
  vector<node> nodes;
  aho_corasick(const vector<string> &pats) {
    nodes.emplace_back();  // Make root node 0.
    for (int i = 0; i < sz(pats); i++) {
      int cur = 0;  // Start from root.
      for (int j = 0; j < sz(pats[i]); j++) {
        int k = pats[i][j] - first;
        if (nodes[cur].next[k] <= 0) {
          // Make new node if needed.
          nodes[cur].next[k] = sz(nodes);
          nodes.emplace_back();
        }
        cur = nodes[cur].next[k];
      }
      // Add logic here if additional data is needed on matched
      // strings.
      nodes[cur].nmatches++;
      // Add string to node list of matches.
      nodes[cur].match_list = new list_node(i, nodes[cur].match_list);
      if (nodes[cur].nmatches == 1)
        nodes[cur].match_list_last = nodes[cur].match_list;
    }
    queue<int> q;
    // Define fail for first level.
    for (int i = 0; i < alpha_size; i++) {
      // Invalid transitions from 0 now become valid self
      // transitions.
      if (nodes[0].next[i] == -1) nodes[0].next[i] = 0;
      // Automaton state transition table.
      nodes[0].atm[i] = nodes[0].next[i];
      // Single letter nodes have fail = 0 and go in the queue.
      if (nodes[0].next[i] > 0) {
        q.push(nodes[0].next[i]);
        nodes[nodes[0].next[i]].fail = 0;
      }
    }
    while (!q.empty())  // Use bfs to compute fail for next level.
    {
      int cur = q.front();
      q.pop();
      for (int i = 0; i < alpha_size; i++)
        if (nodes[cur].next[i] > 0)  // Don't use -1 and don't
                                     // use transition to root.
        {
          // Unrelated to code below, filling automaton.
          nodes[cur].atm[i] = nodes[cur].next[i];
          // Computing fail for next node and putting it in
          // the queue.
          int prox = nodes[cur].next[i];
          q.push(prox);
          int state = nodes[cur].fail;
          while (nodes[state].next[i] == -1) state = nodes[state].fail;
          nodes[prox].fail = nodes[state].next[i];
          // Add logic here if additional data is needed on
          // matched strings.
          nodes[prox].nmatches += nodes[nodes[prox].fail].nmatches;
          // Add in O(1) list from fail link to next node's
          // list.
          // Operation: a->b->null c->null to a->b->c->null.
          (nodes[prox].match_list_last ? nodes[prox].match_list_last->next
                                       : nodes[prox].match_list) =
              nodes[nodes[prox].fail].match_list;
        } else {
          nodes[cur].atm[i] = nodes[nodes[cur].fail].atm[i];
        }
    }
  }
  // Optional
  // Returns a vector retv such that, for each text position i:
  // retv[i] is the index of the largest pattern ending at position
  // i in the text.
  // If retv[i] == -1, no pattern ends at position i.
  vector<int> find(const string &text) {
    vector<int> retv(sz(text));
    int cur = 0;
    for (int i = 0; i < sz(text); i++) {
      cur = nodes[cur].atm[text[i] - first];
      retv[i] = (nodes[cur].match_list ? nodes[cur].match_list->id : -1);
    }
    return retv;
  }
  // Optional
  // Returns a vector retv such that, for each text position i:
  // retv[i] is the number of pattern matches ending at position i
  // in the text.
  vector<int> count(const string &text) {
    vector<int> retv(sz(text));
    int cur = 0;
    for (int i = 0; i < sz(text); i++) {
      cur = nodes[cur].atm[text[i] - first];
      retv[i] = nodes[cur].nmatches;
    }
    return retv;
  }
  // Optional
  // Returns a vector retv such that, for each text position i:
  // retv[i] is a list of indexes to the patterns ending at position
  // i in the text.
  // These lists will be sorted from largest to smallest pattern
  // length.
  // Keep in mind that find_all can be O(N*sqrt(N)) if no duplicate
  // patterns. (N is total string length)
  vector<vector<int>> find_all(const string &text) {
    vector<vector<int>> retv(sz(text));
    int cur = 0;
    for (int i = 0; i < sz(text); i++) {
      cur = nodes[cur].atm[text[i] - first];
      for (auto n = nodes[cur].match_list; n != nullptr; n = n->next)
        retv[i].push_back(n->id);
    }
    return retv;
  }
  // Optional
  // Returns a vector retv such that:
  // retv is a list of indexes to the patterns ending at position
  // pos in the text.
  // This list will be sorted from largest to smallest pattern
  // length.
  vector<int> find_all_at_pos(const string &text, int pos) {
    vector<int> retv;
    int cur = 0;
    for (int i = 0; i < sz(text); i++) {
      cur = nodes[cur].atm[text[i] - first];
      if (i == pos)
        for (auto n = nodes[cur].match_list; n != nullptr; n = n->next)
          retv.push_back(n->id);
    }
    return retv;
  }
};
