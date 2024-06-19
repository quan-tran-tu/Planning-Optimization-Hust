#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    int N, M, b;
    cin >> N >> M >> b;

    // Reading the list of willing reviewers for each paper
    vector<vector<int>> willingReviewers(N);
    for (int i = 0; i < N; ++i) {
        int k;
        cin >> k;
        willingReviewers[i].resize(k);
        for (int j = 0; j < k; ++j) {
            cin >> willingReviewers[i][j];
        }
    }

    // Reviewer load tracking
    vector<int> reviewerLoad(M + 1, 0);
    vector<vector<int>> assignment(N, vector<int>(b));

    // Priority queue to keep reviewers with minimum load at the top
    auto cmp = [&reviewerLoad](int left, int right) {
        return reviewerLoad[left] > reviewerLoad[right];
    };
    priority_queue<int, vector<int>, decltype(cmp)> minLoadReviewers(cmp);

    // Initialize priority queue with all reviewers
    for (int i = 1; i <= M; ++i) {
        minLoadReviewers.push(i);
    }

    // Assign reviewers to papers
    for (int i = 0; i < N; ++i) {
        vector<pair<int, int>> loadList; // Pair of (load, reviewer)

        // Get all willing reviewers' loads
        for (int reviewer : willingReviewers[i]) {
            loadList.push_back({reviewerLoad[reviewer], reviewer});
        }

        // Sort reviewers by their current load (ascending)
        sort(loadList.begin(), loadList.end());

        // Assign top 'b' reviewers with the least load to the paper
        for (int j = 0; j < b; ++j) {
            int chosenReviewer = loadList[j].second;
            assignment[i][j] = chosenReviewer;
            reviewerLoad[chosenReviewer]++;
        }
    }

    // Output the result
    cout << N << endl;
    for (int i = 0; i < N; ++i) {
        cout << b;
        for (int j = 0; j < b; ++j) {
            cout << " " << assignment[i][j];
        }
        cout << endl;
    }

    return 0;
}
