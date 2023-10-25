#include <bits/stdc++.h>
using namespace std;
// Pf = Pb + (vacant/capacity)*(Rg*Rv) + (vacant/capacity)*(Rg*Rc) + (gamma)*(occupancy)

// GENERAL FORMULA
// Pf = Pb + (vacant/capacity)*(Rg*Rv) + (vacant/capacity)*(Rg*Rc)

// Distance grouping for the value 'R' according to distance group would be:
// R = 1 - 3;
// R = 3 - 6;
// R = 6 - 8;
// R = 8 - 10;
// R = 10 - 15;
// R = 15 - 20;
// R = 20 - 30;
// R = 30+

// Desired graph is that of a logarithmic function

void print(vector<double> temp)
{
    for (auto i : temp)
    {
        cout << i << " ";
    }
    cout << endl;
}

void print(map<double, int> mp)
{
    for (auto i : mp)
    {
        cout << i.first << " " << i.second << endl;
    }
    cout << endl;
    cout << endl;
    cout << endl;
}
int main()
{
    double Pb = 20;
    double alpha = 10;
    double beta = 40;
    double gamma = 0.6;
    double occupancy = 100;
    int viewQueueSize = 312;
    int bookQueueSize = 312;                                         // this is the number of parking spots available for the specific parking lot
    map<double, int> distance_group_TO_view_only_request_quantity;   // This contains the radius group to the number of view only requests in that group
    map<double, int> distance_group_TO_booked_only_request_quantity; // This contains the radius group to the number of booked only requests in that group

    vector<double> request_distances_VIEW_ONLY;
    vector<double> request_distances_BOOKING_ONLY;

    // int viewQueueSize = 104;
    // int viewQueueSize = 39;
    // int viewQueueSize = 3;
    // int n = 13;
    for (int i = 0; i < viewQueueSize; i++)
    {
        double input = 0;
        cin >> input;
        request_distances_VIEW_ONLY.push_back(input);
    }

    // int bookQueueSize = 39;
    // int bookQueueSize = 3;
    // int bookQueueSize = 104;
    for (int i = 0; i < bookQueueSize; i++)
    {
        double input = 0;
        cin >> input;
        request_distances_BOOKING_ONLY.push_back(input);
    }

    vector<double> radius_groupings = {1.0, 3.0, 6.0, 8.0, 10.0, 15.0, 20.0, 30.0, INT_MAX};
    int groupSize = radius_groupings.size();
    for (auto view : request_distances_VIEW_ONLY)
    {
        for (int rGroupIndex = 0; rGroupIndex < groupSize - 1; rGroupIndex++)
        {
            if (view >= radius_groupings[rGroupIndex] && view < radius_groupings[rGroupIndex + 1])
            {
                distance_group_TO_view_only_request_quantity[radius_groupings[rGroupIndex]]++;
            }
        }
    }
    for (auto view : request_distances_VIEW_ONLY)
    {
        if (view < 1.0)
        {
            distance_group_TO_view_only_request_quantity[0.75]++;
        }
    }
    print(distance_group_TO_view_only_request_quantity);

    // CALCULATION FOR VALUE OF VIEW ONLY SURGE PRICE
    double intermediateViewPrice = 0.0;

    for (auto i : distance_group_TO_view_only_request_quantity)
    {
        intermediateViewPrice += double(double(1.0 / double(i.first)) * double(double(i.second) / double(viewQueueSize)));
    }

    cout << intermediateViewPrice << endl
         << endl;

    for (auto view : request_distances_BOOKING_ONLY)
    {
        for (int rGroupIndex = 0; rGroupIndex < groupSize - 1; rGroupIndex++)
        {
            if (view >= radius_groupings[rGroupIndex] && view < radius_groupings[rGroupIndex + 1])
            {
                distance_group_TO_booked_only_request_quantity[radius_groupings[rGroupIndex]]++;
            }
        }
    }
    for (auto view : request_distances_BOOKING_ONLY)
    {
        if (view < 1.0)
        {
            distance_group_TO_booked_only_request_quantity[0.75]++;
        }
    }
    print(distance_group_TO_booked_only_request_quantity);
    double intermediateBookPrice = 0.0;

    for (auto i : distance_group_TO_booked_only_request_quantity)
    {
        intermediateBookPrice += double(double(1.0 / double(i.first)) * double(double(i.second) / double(bookQueueSize)));
    }

    cout << intermediateBookPrice << endl;

    double currentVacantSpots = 0;
    if (bookQueueSize >= occupancy)
    {
        currentVacantSpots = 0;
    }
    else
    {
        currentVacantSpots = occupancy - bookQueueSize;
    }
    double finalPrice = Pb + (((intermediateViewPrice)*alpha + (intermediateBookPrice)*beta) * double(gamma) * double(double(occupancy - currentVacantSpots) / double(occupancy)));
    cout << "FINAL PRICE IS : " << finalPrice;
    return 0;
}