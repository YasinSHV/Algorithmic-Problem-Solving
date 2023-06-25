#include <iostream>
#include <vector>

using namespace std;

vector<int> conquerPlanet(int n, const vector<int>& colors) {
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;

    for (int k = 1; k <= n; ++k) {
        int maxColor = 0;
        int currentGroups = 0;

        for (int i = 0; i < n; ++i) {
            if (colors[i] > maxColor)
                maxColor = colors[i];

            if (maxColor - k > 0)
                currentGroups += dp[maxColor - k];

            if (dp[maxColor] > currentGroups)
                dp[maxColor] = currentGroups;
        }
    }

    return dp;
}

int main() {
    int n;
    cin >> n;

    vector<int> colors(n);
    for (int i = 0; i < n; ++i) {
        cin >> colors[i];
    }

    vector<int> result = conquerPlanet(n, colors);

    for (int group : result) {
        cout << group << " ";
    }
    cout << endl;

    return 0;
}
