#include "pbPlot/pbPlots.hpp"
#include "pbPlot/supportLib.hpp"
#include <vector>
using namespace std;

int main (){
    
    RGBABitmapImageReference *imageRef;// = CreateRGBABitmapImageReference ();
    StringReference *errorMessage; //= new StringReference();

    //dynamical arrays of x and y
    vector <double> x {-2, -1, 0, 1, 2};
    vector <double> y {-2, -1, 0, 1, 2};

    //ploating function
    DrawScatterPlot(imageRef, 600, 400, &x, &y, errorMessage);

    vector <double> *pngData = ConvertToPNG(imageRef->image);
    WriteToFile(pngData, "plot.png");
    DeleteImage(imageRef->image);

    
    return 0;

}
