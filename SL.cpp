#include <iostream>
#include <vector>
#include <sstream>
#include <utility>
#include <algorithm>

using namespace std;

// Structure to represent a point
struct Point {
    double x, y;
};

// Structure to represent a line segment
struct LineSegment {
    Point p1, p2;
};

// Function to check if two floating-point numbers are nearly equal (to account for floating-point precision issues)
bool nearlyEqual(double a, double b, double epsilon = 1e-9) {
    return abs(a - b) < epsilon;
}

// Function to find the orientation of the triplet (p, q, r)
// Returns 0 if collinear, 1 if clockwise, 2 if counterclockwise
int orientation(Point p, Point q, Point r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (nearlyEqual(val, 0)) return 0;  // Collinear
    return (val > 0) ? 1 : 2; // Clockwise or counterclockwise
}

// Function to check if point q lies on segment pr
bool onSegment(Point p, Point q, Point r) {
    return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
           q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);
}

// Function to check if two line segments intersect
bool doIntersect(LineSegment l1, LineSegment l2) {
    Point p1 = l1.p1, q1 = l1.p2;
    Point p2 = l2.p1, q2 = l2.p2;

    // Find the four orientations needed for the general and special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case: if the orientations are different, they intersect
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases: Check if the points are collinear and the points lie on the segment
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

// Function to read line segments from user input and check for intersections
void checkIntersections() {
    int n;
    cout << "Enter the number of line segments: ";
    cin >> n;

    vector<LineSegment> segments(n);
    cout << "Enter the line segments in the format 'x1,y1,x2,y2' (one per line):" << endl;

    for (int i = 0; i < n; ++i) {
        string line;
        cin >> ws; // Clear any leading whitespace
        getline(cin, line); // Read the full line
        stringstream ss(line);
        vector<double> coords;

        // Splitting the line by commas
        string temp;
        while (getline(ss, temp, ',')) {
            coords.push_back(stod(temp));
        }
        segments[i] = {{coords[0], coords[1]}, {coords[2], coords[3]}};
    }

    bool hasIntersection = false;

    // Checking all pairs of segments for intersections
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (doIntersect(segments[i], segments[j])) {
                cout << "Intersection found between segments: " << i << " and " << j << endl;
                hasIntersection = true;
            }
        }
    }

    if (!hasIntersection) {
        cout << "No intersecting line segments found." << endl;
    }
}

int main() {
    checkIntersections();
    return 0;
}

