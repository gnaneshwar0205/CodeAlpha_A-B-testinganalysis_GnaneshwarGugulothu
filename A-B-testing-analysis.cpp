#include<iostream>
#include<cmath>
using namespace std;
// Function to calculate the p-value for a two-sample t-test
double calculatePValue(double x, double nu) {
    double t = fabs(x);
    double k = nu / (nu + t * t);
    double w = atan(sqrt((nu + t * t) / nu)) * 2 / M_PI;
    return 1 - (0.5 + 0.5 * k * w);
}

int main() {
    // input user data for group A (old version)
    int groupAVisits;
    cout<<"groupAVisits = ";
    cin>>groupAVisits;
    int groupAClicks;
    cout<<"groupAClicks = ";
    cin>>groupAClicks;
    double groupACTR = static_cast<double>(groupAClicks) / groupAVisits;

    // input user data for group B (redesigned version)
    int groupBVisits;
    cout<<"groupBVisits = ";
    cin>>groupBVisits;
    int groupBClicks;
    cout<<"groupBClicks = ";
    cin>>groupBClicks;
    double groupBCTR = static_cast<double>(groupBClicks) / groupBVisits;

    // Calculate pooled standard error
    double pooledSE = sqrt((groupACTR * (1 - groupACTR) / groupAVisits) + (groupBCTR * (1 - groupBCTR) / groupBVisits));

    // Calculate t-statistic
    double tStatistic = (groupBCTR - groupACTR) / pooledSE;

    // Degrees of freedom
    int nu = groupAVisits + groupBVisits - 2;

    // Calculate p-value
    double pValue = calculatePValue(tStatistic, nu);

    // Set significance level by user input
    double alpha;
    cout<<"alpha = ";
    cin>>alpha;

    // Interpret results
    if (pValue < alpha) {
        cout << "Reject the null hypothesis. There is a significant difference in CTR between the two groups." << endl;
        if (groupBCTR > groupACTR) {
            cout << "The redesigned website has a higher CTR compared to the old version." << endl;
        } else {
            cout << "The old version of the website has a higher CTR compared to the redesigned version." << endl;
        }
    } else {
        cout << "Fail to reject the null hypothesis. There is no significant difference in CTR between the two groups." << endl;
    }

    return 0;
}
