
#include <iostream>
#include <cmath>
using namespace std;

const double EPS = 1e-9;
const double H = 0.0001;
const double PI = 3.141592653589793;

// ==================================================
// SECTION 1: VECTOR STRUCTURE AND BASIC OPERATIONS
// ==================================================

struct Vector {
    double x, y, z;
};

Vector inputVector(char name) {
    Vector a;
    cout << "Enter vector " << name << " (x y z): ";
    cin >> a.x >> a.y >> a.z;
    return a;
}
     
void display(Vector a) {
    cout << "(" << a.x << ", " << a.y << ", "<< a.z << ")\n";
}

Vector add(Vector a, Vector b) {
    Vector r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    r.z = a.z + b.z;
    return r;
}

Vector subtract(Vector a, Vector b) {
    Vector r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    return r;
}

Vector multiply(Vector a, double k) {
    Vector r;
    r.x = a.x * k;
    r.y = a.y * k;
    r.z = a.z * k;
    return r;
}

Vector divide(Vector a, double k) {
    Vector r = {0, 0, 0};

    if (fabs(k) == 0) {
        cout << "Division by zero is not allowed.\n";
        return r;
    }

    r.x = a.x / k;
    r.y = a.y / k;
    r.z = a.z / k;
    return r;
}

double dot(Vector a, Vector b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

Vector cross(Vector a, Vector b) {
    Vector r;
    r.x = a.y*b.z - a.z*b.y;
    r.y = a.z*b.x - a.x*b.z;
    r.z = a.x*b.y - a.y*b.x;
    return r;
}

double magnitude(Vector a) {
    return sqrt(dot(a, a));
}

double distance(Vector a, Vector b) {
    return magnitude(subtract(a, b));
}

Vector unit(Vector a) {
    double m = magnitude(a);
    Vector r = {0, 0, 0};

    if (m == 0) {
        cout << "Zero vector has no unit vector.\n";
        return r;
    }

    return divide(a, m);
}

// ==================================================
// SECTION 2: VECTOR PRODUCTS AND PROJECTIONS
// ==================================================

double angle(Vector a, Vector b) {
    double ma = magnitude(a);
    double mb = magnitude(b);

    if (ma < EPS || mb < EPS)
        return -1;

    double c = dot(a, b) / (ma * mb);

    if (c > 1) c = 1;
    if (c < -1) c = -1;

    return acos(c) * 180.0 / PI;
}

double scalarProjection(Vector a, Vector b) {
    double m = magnitude(b);

    if (m < EPS) {
        cout << "Projection onto zero vector is undefined.\n";
        return 0;
    }

    return dot(a, b) / m;
}

Vector vectorProjection(Vector a, Vector b) {
    double d = dot(b, b);
    Vector r = {0, 0, 0};

    if (d < EPS * EPS) {
        cout << "Projection onto zero vector is undefined.\n";
        return r;
    }

    return multiply(b, dot(a, b) / d);
}

Vector perpendicularComponent(Vector a, Vector b) {
    return subtract(a, vectorProjection(a, b));
}


//=================================================
// SECTION 3: PARALLELISM AND PERPENDICULARITY
//=================================================




bool parallel(Vector a, Vector b) {
    double ma = magnitude(a);
    double mb = magnitude(b);

    if (ma < EPS || mb < EPS)
        return false;

    return magnitude(cross(a, b)) < EPS * ma * mb;
}

bool perpendicular(Vector a, Vector b) {
    double ma = magnitude(a);
    double mb = magnitude(b);

    if (ma < EPS || mb < EPS)
        return false;

    return fabs(dot(a, b)) < EPS * ma * mb;
}
// ==================================================
// SECTION 4: SCALAR AND VECTOR TRIPLE PRODUCTS, AREAS, AND VOLUMES
// ==================================================
double scalarTriple(Vector a, Vector b, Vector c) {
    return dot(a, cross(b, c));
}

Vector vectorTriple(Vector a, Vector b, Vector c) {
    return cross(a, cross(b, c));
}

double parallelogramArea(Vector a, Vector b) {
    return magnitude(cross(a, b));
}

double triangleArea(Vector a, Vector b) {
    return parallelogramArea(a, b) / 2.0;
}

double volume(Vector a, Vector b, Vector c) {
    return fabs(scalarTriple(a, b, c));
}



// ==================================================
// SECTION 5: MAIN MENU
// ==================================================

int main() {
    int choice;
    double k, result;
    Vector A, B, C;

    do {
        cout << "\n==================================================================================================\n";
cout << "                              VECTOR OPERATIONS TOOLKIT\n";
cout << "==================================================================================================\n\n";

cout << "BASIC VECTOR OPERATIONS\n ";                     
cout << "------------------------------\n";               
cout << "1. Addition"<<endl;                                  
cout << "2. Subtraction"<<endl;                              
cout << "3. Scalar multiplication"<<endl;                     
cout << "4. Scalar division"<<endl;                           
cout << "5. Magnitude"<<endl;                                 
cout << "6. Unit vector"<<endl;                               
cout << "7. Dot product"<<endl;                               
cout << "8. Cross product"<<endl;                             
cout << "9. Angle between vectors"<<endl;                     
cout << "10. Distance between points"<<endl;
cout << "11. Scalar projection"<<endl;
cout << "12. Vector projection"<<endl;
cout << "13. Perpendicular component"<<endl;
cout << "14. Check parallel vectors"<<endl;
cout << "15. Check perpendicular vectors"<<endl;
cout << "16. Scalar triple product"<<endl;
cout << "17. Vector triple product"<<endl;
cout << "18. Parallelogram area"<<endl;
cout << "19. Triangle area"<<endl; 
cout << "20. Parallelepiped volume"<<endl;


cout << "\n0. Exit\n";
cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Restart the program and enter a number.\n";
            return 1;
        }

        switch (choice) {
        case 1:
            A = inputVector('A');
            B = inputVector('B');
            display(add(A, B));
            break;

        case 2:
            A = inputVector('A');
            B = inputVector('B');
            display(subtract(A, B));
            break;

        case 3:
            A = inputVector('A');
            cout << "Enter scalar: ";
            cin >> k;
            display(multiply(A, k));
            break;

        case 4:
            A = inputVector('A');
            cout << "Enter divisor: ";
            cin >> k;
            if (fabs(k) == 0)
                cout << "Cannot divide by zero.\n";
            else
                display(divide(A, k));
            break;

        case 5:
            A = inputVector('A');
            cout << "Magnitude = " << magnitude(A) << "\n";
            break;

        case 6:
            A = inputVector('A');
            if (magnitude(A) == 0)
                cout << "Unit vector is undefined.\n";
            else
                display(unit(A));
            break;

        case 7:
            A = inputVector('A');
            B = inputVector('B');
            cout << "Dot product = " << dot(A, B) << "\n";
            break;

        case 8:
            A = inputVector('A');
            B = inputVector('B');
            display(cross(A, B));
            break;

        case 9:
            A = inputVector('A');
            B = inputVector('B');
            result = angle(A, B);
            if (result < 0)
                cout << "Angle is undefined.\n";
            else
                cout << "Angle = " << result << " degrees\n";
            break;

        case 10:
            A = inputVector('A');
            B = inputVector('B');
            cout << "Distance = " << distance(A, B) << "\n";
            break;

        case 11:
            A = inputVector('A');
            B = inputVector('B');
            if (magnitude(B) < EPS)
                cout << "Projection is undefined.\n";
            else
                cout << scalarProjection(A, B) << "\n";
            break;

        case 12:
            A = inputVector('A');
            B = inputVector('B');
            if (magnitude(B) < EPS)
                cout << "Projection is undefined.\n";
            else
                display(vectorProjection(A, B));
            break;

        case 13:
            A = inputVector('A');
            B = inputVector('B');
            if (magnitude(B) < EPS)
                cout << "Projection is undefined.\n";
            else
                display(perpendicularComponent(A, B));
            break;

        case 14:
            A = inputVector('A');
            B = inputVector('B');
            if (parallel(A, B))
                cout << "Parallel.\n";
            else
                cout << "Not parallel.\n";
            break;

        case 15:
            A = inputVector('A');
            B = inputVector('B');
            if (perpendicular(A, B))
                cout << "Perpendicular.\n";
            else
                cout << "Not perpendicular.\n";
            break;

        case 16:
            A = inputVector('A');
            B = inputVector('B');
            C = inputVector('C');
            cout << scalarTriple(A, B, C) << "\n";
            break;

        case 17:
            A = inputVector('A');
            B = inputVector('B');
            C = inputVector('C');
            display(vectorTriple(A, B, C));
            break;

        case 18:
            A = inputVector('A');
            B = inputVector('B');
            cout << parallelogramArea(A, B) << "\n";
            break;

        case 19:
            A = inputVector('A');
            B = inputVector('B');
            cout << triangleArea(A, B) << "\n";
            break;

        case 20:
            A = inputVector('A');
            B = inputVector('B');
            C = inputVector('C');
            cout << volume(A, B, C) << "\n";
            break;

        

       

        case 0:
            cout << "Calculator closed.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
    }