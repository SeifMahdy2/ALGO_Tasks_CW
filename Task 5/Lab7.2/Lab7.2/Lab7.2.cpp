//#include <iostream>
//#include <set>
//#include <algorithm>
//
//using namespace std;
//
//void insertIntoSet(set<int>& s, const string& setName) {
//    int num;
//    char choice;
//    do {
//        cout << "Enter an element to insert into set " << setName << ": ";
//        cin >> num;
//        s.insert(num);
//        cout << "Do you want to insert another element? (y/n): ";
//        cin >> choice;
//    } while (choice == 'y' || choice == 'Y');
//}
//void printSet(set<int> A, set<int> B) {
//    cout << "Set A: ";
//    for (int i : A) {
//        cout << i << " ";
//    }
//    cout << endl;
//    cout << "Set B: ";
//    for (int i : B) {
//        cout << i << " ";
//    }
//    cout << endl;
//}
//
//int main() {
//    set<int> A = { 1, 2, 3, 4, 5 };
//    set<int> B = { 4, 5, 6, 7, 8 };
//
//    cout << "Set A: ";
//    for (int i : A) {
//        cout << i << " ";
//    }
//    cout << endl;
//    cout << "Set B: ";
//    for (int i : B) {
//        cout << i << " ";
//    }
//    cout << endl;
//
//
//    
//    int N = A.size();
//    int M = B.size();
//
//    set<int> unionSet;
//    set_union(A.begin(), A.end(), B.begin(), B.end(), inserter(unionSet, unionSet.begin()));
//
//    cout << "Union: ";
//    for (int elem : unionSet) {
//        cout << elem << " ";
//    }
//    cout << endl;
//
//    set<int> differenceSet;
//    set_difference(A.begin(), A.end(), B.begin(), B.end(), inserter(differenceSet, differenceSet.begin()));
//
//    cout << "Difference (A - B): ";
//    for (int elem : differenceSet) {
//        cout << elem << " ";
//    }
//    cout << endl;
//
//    set<int> intersectionSet;
//    set_intersection(A.begin(), A.end(), B.begin(), B.end(), inserter(intersectionSet, intersectionSet.begin()));
//
//    cout << "Intersection: ";
//    for (int elem : intersectionSet) {
//        cout << elem << " ";
//    }
//    cout << endl;
//
//    insertIntoSet(A, "A");
//    insertIntoSet(B, "B");
//
//    printSet(A,B);
//
//
//    return 0;
//}



//question 2

//#include <iostream>
//#include <set>
//
//using namespace std;
//
//void processQuery(set<int>& s, char queryType, int x) {
//    switch (queryType) {
//    case 'a':
//        s.insert(x);
//        break;
//    case 'b':
//        for (int elem : s) {
//            cout << elem << " ";
//        }
//        cout << endl;
//        break;
//    case 'c':
//        s.erase(x);
//        break;
//    case 'd':
//        if (s.find(x) != s.end()) {
//            cout << "1" << endl;
//        }
//        else {
//            cout << "-1" << endl;
//        }
//        break;
//    case 'e':
//        cout << "Size of set: " << s.size() << endl;
//        break;
//    default:
//        cout << "Invalid query type!" << endl;
//        break;
//    }
//}
//
//int main() {
//    set<int> S1;
//
//    char queryType;
//    int x;
//
//    cout << "Enter query type followed by parameter (if any), or 'q' to quit:" << endl;
//
//    while (cin >> queryType && queryType != 'q') {
//        if (queryType == 'a' || queryType == 'c' || queryType == 'd') {
//            cin >> x;
//        }
//
//        processQuery(S1, queryType, x);
//    }
//
//    return 0;
//}


//Question 3

//#include <iostream>
//#include <map>
//
//using namespace std;
//
//void processQuery(map<int, int>& m, char queryType, int x, int y) {
//    switch (queryType) {
//    case 'a':
//        m[x] = y;
//        break;
//    case 'b':
//        if (m.find(x) != m.end()) {
//            cout << m[x] << endl;
//        }
//        else {
//            cout << "-1" << endl;
//        }
//        break;
//    case 'c':
//        for (auto& pair : m) {
//            cout << pair.first << " " << pair.second << " ";
//        }
//        cout << endl;
//        break;
//    default:
//        cout << "Invalid query type!" << endl;
//        break;
//    }
//}
//
//int main() {
//    map<int, int> M1;
//
//    char queryType;
//    int x, y;
//
//    cout << "Enter query type followed by parameters (if any), or 'q' to quit:" << endl;
//
//    while (cin >> queryType && queryType != 'q') {
//        if (queryType == 'a') {
//            cin >> x >> y;
//        }
//        else if (queryType == 'b') {
//            cin >> x;
//        }
//
//        processQuery(M1, queryType, x, y);
//    }
//
//    return 0;
//}
