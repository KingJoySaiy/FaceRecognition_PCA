#include "CreateDatabase.h"
#include "EigenFaceCore.h"
#include "Recognition.h"

const string& trainRoot = "TrainDatabase";
const string& testRoot = "TestDatabase";
const string validSelect[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

int main() {

    //select an image
    cout << "Enter test image name (a number between 1 to 10): ";
    string select;
    while (true) {
        cin >> select; 
        bool isValid = false;
        for (auto& p : validSelect) {
            if (select == p) {
                isValid = true;
                break;
            }
        }
        if (isValid) {
            break;
        }
        cout << "Invalid input! Try again please! ";
    }

    //match image
    string selectPath = testRoot + "\\" + select + ".jpg";
    Mat T = createDatabase(trainRoot);
    auto M_A_EigenFaces = EigenFaceCore(T);
    string res = recognition(selectPath, M_A_EigenFaces), resPath = trainRoot + "\\" + res + ".jpg";
    cout << "Result image is: " << res << ".jpg" << endl;

    //show image
    Mat selectImage = imread(selectPath), resImage = imread(resPath);
    imshow("selectedImage", selectImage);
    imshow("resImage", resImage);
    waitKey(0);
    destroyAllWindows();

    return 0;
}