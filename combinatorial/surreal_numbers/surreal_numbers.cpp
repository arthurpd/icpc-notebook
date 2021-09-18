#include "../../contest/header.hpp"
/*
        General Theory for Two Player Game

        Take a perfect information game involving two players,
        Left and Right, where either one can start the game.

        This is a partial game in which the allowable moves
        depend on which of the two players is currently moving
        (e.g chess).

        There are four possible scenarios for an initial configuration:
                - Left wins (does not matter if first or second).
                - Right wins
                - First player wins.
                - Second player wins

        If a game has no "First player wins" configurations,
        the configurations of the game can be mapped to real
        numbers s(i) of the form a/2^b such that.
                - s(i) > 0 -> Left wins
                - s(i) < 0 -> Right wins
                - s(i) = 0 -> second player wins

        The union of two states i,j is mapped to s(i) + s(j)

        More formally:
        A game is a position in a contest between two players, Left and
        Right.
        Each player has a set of games called options to choose from in
        turn.
        Games are written {L|R} where L is the set of Left's options and
        R is the set of Right's options.

        At the start there are no games at all, so the empty set is the
        only set of options we can provide to the players.
        This defines the game {|}, which is called 0. We consider a
        player who must play a turn but has no options to have lost the
        game (so in game 0 second player wins). Given this game 0 there
        are now two possible sets of options, the empty set and the set
        whose only element is zero.
        The game {0|} is called 1, and the game {|0} is called -1.
        In game 1, if Right goes first, Left wins. And if Left goes
        first, he will choose game 0 to be next and win (because Right
        will have no moves).
        So game 1 is of the type Left wins, as expected.
        The game {0|0} is called * (star), and is the first game we find
        that is not a number (in this game, first player wins).

        All numbers are positive, negative, or zero, and we say that a
        game is positive if Left will win, negative if Right will win,
        or zero if the second player will win. Games that are not numbers
        have a fourth possibility: they may be fuzzy, meaning that the
        first player will win. * is a fuzzy game.[4]
*/
int main(void) {
  cin.sync_with_stdio(0);
  cin.tie(0);
  int n;
  while (cin >> n) {
    ll mult = (1ll << 40);
    // This will store the surreal number for each game times
    // 2^40 (just to avoid doubles).
    vector<ll> s(n);
    vector<int> val(n);
    for (int i = 0; i < n; i++) {
      string a;
      cin >> a;
      ll x = mult;
      bool change = false;
      for (int j = 0; j < sz(a); j++) {
        if (a[j] != a[0])  // After first different, start
                           // changing x.
          change = true;
        if (change) x /= 2;
        if (a[j] == 'B')
          s[i] += x;
        else
          s[i] -= x;
      }
      val[i] = sz(a);
    }
    // Now we have s[i] for each game.
    // If we join two games i,j we get a game x with
    // s(x) = s[i] + s[j] and val(x) = val[i] + val[i].
    // So to find a fair game with s[x] = 0 and maximum val
    // We need to find a subset with zero sum and maximum val.
    // Here onwards we just solve this problem with meet in
    // the middle.
    unordered_map<ll, int> tab;
    int mid = (n + 1) / 2;
    for (int i = 0; i < (1 << mid); i++) {
      ll x = 0;
      int y = 0;
      for (int j = 0; j < mid; j++)
        if (i & (1 << j)) {
          x += s[j];
          y += val[j];
        }
      tab[x] = max(tab[x], y);
    }
    int ans = 0;
    for (int i = 0; i < (1 << (n - mid)); i++) {
      ll x = 0;
      int y = 0;
      for (int j = 0; j < (n - mid); j++)
        if (i & (1 << j)) {
          x += s[mid + j];
          y += val[mid + j];
        }
      auto it = tab.find(-x);
      if (it != tab.end()) {
        ans = max(ans, y + it->second);
      }
    }
    cout << ans << endl;
  }
}
