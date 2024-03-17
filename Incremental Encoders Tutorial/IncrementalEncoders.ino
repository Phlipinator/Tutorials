const int pinA = 2; // Encoder pin A
const int pinB = 3; // Encoder pin B

volatile int encoderPos = 0; // Encoder position
int lastEncoded = 0;         // Last encoded state
bool processInput = true;

void setup()
{
    Serial.begin(9600);          // Start serial communication
    pinMode(pinA, INPUT_PULLUP); // Set pinA as input with pull-up resistor
    pinMode(pinB, INPUT_PULLUP); // Set pinB as input with pull-up resistor

    // Read the initial state
    lastEncoded = (digitalRead(pinA) << 1) | digitalRead(pinB);
}

void loop()
{
    int MSB = digitalRead(pinA);            // Most significant bit
    int LSB = digitalRead(pinB);            // Least significant bit
    int encoded = (MSB << 1) | LSB;         // Combining the two bits
    int sum = (lastEncoded << 2) | encoded; // Adding it to the previous encoded value

    // Detect if the Encoder has been moved at all
    if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011 || sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
    {
        if (processInput)
        {
            // Determine direction and increment or decrement encoderPos accordingly
            if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
                encoderPos++;
            else if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
                encoderPos--;

            // Only process this input, next one will be skipped
            processInput = false;

            Serial.println(encoderPos);
        }
        else
        {
            // Skip this input, next one will be processed
            processInput = true;
        }
    }

    lastEncoded = encoded; // Store this value for next time

    delay(2); // Simple debounce
}
