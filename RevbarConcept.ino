#define MaxLed 32 //32 LED Max now

int AnimationType = 1, LedNumbers = 15, Pixels = 0, animationDirection = 0,iPixel=0;
//Direction 0: 0->7
//Direction 1: 7->0

int rpmNow = 3700, rpmMin = 1000, rpmMax = 8000;
float Percentage = 0;

//Bar Color
int LEDColor[3][MaxLed] = 0, iLED = 0; 
//0,1,2=R,G,B

// GREEN - ColorStageGreen | ORANGE | ColorStageRed - RED
// numbers are all in "iPixel" address
int ColorStageGreen = 1, ColorStageRed = 6;
int GreenColor[3] = {0, 255, 0};
int OrangeColor[3] = {255, 165, 0};
int RedColor[3] = {255, 0, 0};

void setAnimationType()
{
    //example 15LEDs
    //1 - left to right 0->14
    //2 - right to left 14->0
    //3 - center to out 7<-0->7
    //4 - out to center 0<-7->0
    switch (AnimationType)
    {
    case 1:
        animationDirection = 0;
        Pixels = LedNumbers;

        break;
    case 2:
        animationDirection = 1;
        Pixels = LedNumbers;
        break;
    case 3:
        animationDirection = 0;
        Pixels = LedNumbers / 2;
        break;
    case 3:
        animationDirection = 1;
        Pixels = LedNumbers / 2;
        break;
    default:
        break;
    }
}

void rpmToPercentage()
{

    //calculate Percentage!
    //(3700-1000)/(8000-1000)

    Percentage = (rpmNow - rpmMin) / (rpmMax - rpmMin);


}

/* function to generate and return each Pixel*/
void PercentageToPixels()
{
    // Percentage = 0.3857;
    // Pixels = 0 -> 7
    static float PixelValues[MaxLed];
    int iPixel;
    float everyPixelPercentage = 1 / (Pixels + 1); //0.125

    for (iPixel = 0; iPixel <= Pixels; ++iPixel) // Pixels = 0 -> 7
    {
        int LitPixel = Percentage / everyPixelPercentage; //LitPixel=3 - 3.0856
        if (iPixel < LitPixel) //0,1,2
        {
            PixelValues[iPixel] = 1;
        }
        else
        {
            if (iPixel > LitPixel) //4,5,6,7
            {
                PixelValues[iPixel] = 0;
            }
            else //3
            {
                PixelValues[iPixel] = Percentage / everyPixelPercentage - iPixel;
            }
        }
    }
}

void setBarColor()
{
}

void PixelsToColor()
{
    iPixel = 0;
    while (iPixel < Pixels)
    {
        if (iPixel < ColorStageGreen) //Green
        {
            for (int iRGB = 0; iRGB <= 3; iRGB++)
            {
                LEDColor[iRGB][iLED] = GreenColor[iRGB] * Percentage;
            }
        }
        else //orange or red
        {
            if (iPixel >= ColorStageRed) //red
            {
                for (int iRGB = 0; iRGB <= 3; iRGB++)
                {
                    LEDColor[iRGB][iLED] = OrangeColor[iRGB] * Percentage;
                }
            }
            else //Orange
            {
                for (int iRGB = 0; iRGB <= 3; iRGB++)
                {
                    LEDColor[iRGB][iLED] = RedColor[iRGB] * Percentage;
                }
            }
        }
        iPixel++;
    }
}

int main()
{

    return 0;
}