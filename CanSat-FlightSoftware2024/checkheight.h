#define MOVINGAVG 5
#define FIR_TAP 5
#define ERR_DIFF 1
#define FRACTION 0.6
#define ALPHA 0.9

float arr[MOVINGAVG] = {0, 0, 0, 0, 0};
float fir_coeffs[FIR_TAP] = {0.2, 0.2, 0.2, 0.2, 0.2};  // Adjust coefficients as needed
float fir_buffer[FIR_TAP] = {0};

float y = 0;

void updateAlt(float alt)
{
    // Exponential smoothing
    y = y * (1 - ALPHA) + ALPHA * alt;

    // Update circular buffer for moving average
    for (int i = 0; i < MOVINGAVG - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    arr[MOVINGAVG - 1] = alt;

    // Update FIR filter buffer
    for (int i = FIR_TAP - 1; i > 0; i--)
    {
        fir_buffer[i] = fir_buffer[i - 1];
    }
    fir_buffer[0] = alt;
}

float getFiltered()
{
    return y;
}

float getFIRFiltered()
{
    float result = 0;
    for (int i = 0; i < FIR_TAP; i++)
    {
        result += fir_coeffs[i] * fir_buffer[i];
    }
    return result;
}

bool checkAlt(float lessthanAlti)
{
    float mean = getFiltered();
    if (mean > lessthanAlti)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool movingUp()
{
    int j = 0;
    for (int i = 1; i < MOVINGAVG; i++)
    {
        if (arr[i] > arr[i - 1])
        {
            j++;
        }
    }
    if (j > FRACTION * MOVINGAVG)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool movingDown()
{
    int j = 0;
    for (int i = 1; i < MOVINGAVG; i++)
    {
        if (arr[i] < arr[i - 1])
        {
            j++;
        }
    }
    if (j > FRACTION * MOVINGAVG)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool notMoving()
{
    int j = 0;
    float filtered_alt = getFiltered();
    for (int i = 0; i < MOVINGAVG; i++)
    {
        if (arr[i] < filtered_alt + ERR_DIFF && arr[i] > filtered_alt - ERR_DIFF)
        {
            j++;
        }
    }
    if (j == MOVINGAVG - 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
