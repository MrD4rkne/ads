#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <deque>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

using bitmask = uint16_t;

/// @brief Negates bitmask.
/// @param k number of bits in bitmask.
/// @param mask bitmask as a number.
bitmask negate_bitmask(const int k, bitmask mask) {
  bitmask anwser = 0;
  for (int i = k - 1; i >= 0; i--) {
    anwser <<= 1;
    if (!(mask & (1 << i))) {
      anwser |= 1;
    }
  }
  return anwser;
}

/// @brief Converts bitmask to negated bitmask as a number.
/// @param bitmaskAnwser bitmask as a vector of chars.
/// @return negated bitmask as a number.
bitmask get_matching_previous_bitmask(const vector<char> &bitmaskAnwser) {
  int anwser = 0;
  for (size_t i = 0; i < bitmaskAnwser.size(); i++) {
    anwser <<= 1;
    if (bitmaskAnwser[i] != 1) {
      anwser |= 1;
    }
  }
  return anwser;
}

/// @brief Converts bitmask from vector of chars to number.
/// @param mask bitmask as a vector of chars.
/// @return bitmask as a number.
bitmask get_bitmask(const vector<char> mask) {
  bitmask ans = 0;
  for (size_t i = 0; i < mask.size(); i++) {
    ans <<= 1;
    ans |= (mask[i] != 0 ? 1 : 0);
  }
  return ans;
}

/// @brief Modifies bitmaskAnwser, mask and bitmaskNegated simultaneously.
/// @param bitmaskAnwser bitmask as a vector of chars.
/// @param mask bitmask as a number.
/// @param bitmaskNegated negated bitmask as a number.
/// @param i index
/// @param j value to place from {0, 1, 2}
void alter_bitmask(vector<char> &bitmaskAnwser, bitmask &mask,
                   bitmask &bitmaskNegated, const size_t i, const int j) {
  assert(i < bitmaskAnwser.size());
  assert(j >= 0 && j <= 2);

  const size_t k = bitmaskAnwser.size();

  if (j == 0) {
    mask &= ~(1 << (k - 1 - i));
    if (bitmaskAnwser[i] == 2) {
      mask &= ~(1 << (k - 1 - (i + 1)));
    }
  } else {
    mask |= (1 << (k - 1 - i));
    if (j == 2) {
      mask |= (1 << (k - 1 - (i + 1)));
    }
  }

  bitmaskAnwser[i] = j;
  if (j != 1) {
    bitmaskNegated |= (1 << (k - 1 - i));
  } else {
    bitmaskNegated &= ~(1 << (k - 1 - i));
  }
}

enum class SlabType { Horizontal, Vertical, None };

/// @brief Optimizes anwser for current column.
/// @param a 2D array of slabs.
/// @param previousColumnAnwsers best anwsers for previous column by bitmask.
/// @param column current column.
/// @param currMask current mask.
/// @return best anwser for current column.
long long optimize_anwser(const vector<vector<long long>> &a,
                          const vector<long long> &previousColumnAnwsers,
                          const int column, const vector<char> &currMask) {
  const int k = a.size();

  vector<char> mask(k, 0);
  bitmask negatedMask = negate_bitmask(k, 0);
  // Sum of slabs on cells from current column (also includes slabs from
  // previous column if horizontal slab).
  long long sumFromCurrentColumn = 0;
  bitmask temp = 0;

  // Fill current mask and calculate sums.
  for (int i = 0; i < k; i++) {
    if (currMask[i] != 0) {
      alter_bitmask(mask, temp, negatedMask, i, currMask[i]);
      sumFromCurrentColumn += a[i][column];

      if (currMask[i] == 2) {
        sumFromCurrentColumn += a[i + 1][column];
      } else {
        sumFromCurrentColumn += a[i][column - 1];
      }
    }
  }

  long long previousBestMatchingResult = previousColumnAnwsers[negatedMask];
  long long bestAnwser = previousBestMatchingResult + sumFromCurrentColumn;

  stack<pair<int, SlabType>> pairStack;
  // Find first possible pair.
  for (int i = 1; i < k; i++) {
    if (mask[i] == 1 && mask[i - 1] == 1) {
      pairStack.push({i, SlabType::None});
      break;
    }
  }

  // Iterate over all possible combinations of pairs and find the best anwser.
  while (!pairStack.empty()) {
    auto &p = pairStack.top();

    switch (p.second) {
    case SlabType::None: {
      int firstPairIndex = -1;
      for (int i = p.first; i < k; i++) {
        if (mask[i] == 1 && mask[i - 1] == 1) {
          firstPairIndex = i;
          break;
        }
      }

      // If there is no possible pair, pop the stack and continue.
      if (firstPairIndex == -1) {
        pairStack.pop();
        break;
      }

      p.first = firstPairIndex;

      // Place slab vertically.
      p.second = SlabType::Vertical;
      alter_bitmask(mask, temp, negatedMask, p.first, 0);
      alter_bitmask(mask, temp, negatedMask, p.first - 1, 2);
      sumFromCurrentColumn -=
          a[p.first][column - 1] + a[p.first - 1][column - 1];
      previousBestMatchingResult = previousColumnAnwsers[negatedMask];

      // Next possible pair starts 2 rows below the current one.
      pairStack.push({p.first + 2, SlabType::None});
      break;
    }

    case SlabType::Vertical: {
      // Place slab horizontally.
      p.second = SlabType::Horizontal;
      alter_bitmask(mask, temp, negatedMask, p.first, 1);
      alter_bitmask(mask, temp, negatedMask, p.first - 1, 1);
      sumFromCurrentColumn +=
          a[p.first][column - 1] + a[p.first - 1][column - 1];
      previousBestMatchingResult = previousColumnAnwsers[negatedMask];

      // Next possible pair starts 2 rows below the current one.
      pairStack.push({p.first + 1, SlabType::None});
      break;
    }
    case SlabType::Horizontal: {
      // Stab was placed vertically and horizontally, so we need to remove it.
      pairStack.pop();
      break;
    }
    }

    bestAnwser =
        max(bestAnwser, sumFromCurrentColumn + previousBestMatchingResult);
  }

  return bestAnwser;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  /// @brief 2D array of slabs.
  vector<vector<long long>> a(k, vector<long long>(n + 1));

  // Fill first column with -10000000 to avoid checking if we are at the edge of
  // the array.
  for (int i = 0; i < k; i++) {
    a[i][0] = -10000000;
  }

  for (int row = 0; row < k; row++) {
    for (int column = 0; column < n; column++) {
      cin >> a[row][column + 1];
    }
  }

  // Remembers the best anwser for each column and bitmask.
  vector<vector<long long>> dp(n + 1, vector<long long>((1 << k), 0));
  for (int column = 1; column <= n; column++) {
    for (int onesCount = 0; onesCount <= k; onesCount++) {
      vector<char> currentBitmask(k, 0);
      for (int i = 0; i < onesCount; i++) {
        currentBitmask[k - 1 - i] = 1;
      }

      do {
        long long bestAnwser =
            optimize_anwser(a, dp[column - 1], column, currentBitmask);

        bitmask currentMaskAsNumber = get_bitmask(currentBitmask);
        bitmask negatedMasksNumber = negate_bitmask(k, currentMaskAsNumber);

        for (int i = 0; i < k; i++) {
          if (currentBitmask[i] == 0) {
            continue;
          }

          alter_bitmask(currentBitmask, currentMaskAsNumber, negatedMasksNumber,
                        i, 0);
          bestAnwser = max(bestAnwser, dp[column][currentMaskAsNumber]);
          alter_bitmask(currentBitmask, currentMaskAsNumber, negatedMasksNumber,
                        i, 1);
        }

        dp[column][currentMaskAsNumber] = bestAnwser;

      } while (next_permutation(currentBitmask.begin(), currentBitmask.end()));
    }
  }

  long long bestAnwser = *max_element(dp[n].begin(), dp[n].end());
  cout << bestAnwser << "\n";

  // Clear memory.
  for (auto &r : dp) {
    r.clear();
  }
  dp.clear();

  for (auto &r : a) {
    r.clear();
  }
  a.clear();

  return 0;
}