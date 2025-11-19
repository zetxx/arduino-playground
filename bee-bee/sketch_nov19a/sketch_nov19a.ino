#include <arduinoFFT.h>

#define SAMPLES             256
#define SAMPLING_FREQUENCY  4000     // Hz
#define NUM_FRAMES          64        // Number of frames for median <<-- Adjusting time window: Increase NUM_FRAMES for longer smoothing, decrease for faster updates.
#define ADC_PIN             32       // GPIO32 on TTGO T7

ArduinoFFT<double> FFT;             // FFT object

double vReal[SAMPLES];
double vImag[SAMPLES];
double allFrames[NUM_FRAMES][SAMPLES/2]; // store magnitude of each frame
double median[SAMPLES/2];

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
  Serial.println("FFT with median (magnitude) ready");
}

void loop() {
  unsigned long sampling_period_us = 1000000UL / SAMPLING_FREQUENCY;

  // --- 1. Acquire NUM_FRAMES frames ---
  for (int f = 0; f < NUM_FRAMES; f++) {
    for (int i = 0; i < SAMPLES; i++) {
      unsigned long t_start = micros();
      vReal[i] = analogRead(ADC_PIN);
      vImag[i] = 0;
      while (micros() - t_start < sampling_period_us) {}
    }

    FFT.windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.complexToMagnitude(vReal, vImag, SAMPLES);

    // Store magnitudes for this frame
    for (int i = 0; i < SAMPLES/2; i++) {
      allFrames[f][i] = vReal[i];
    }
  }

  // --- 2. Compute median for each frequency bin ---
  for (int i = 0; i < SAMPLES/2; i++) {
    double temp[NUM_FRAMES];
    for (int f = 0; f < NUM_FRAMES; f++) temp[f] = allFrames[f][i];

    // Simple bubble sort to get median
    for (int a = 0; a < NUM_FRAMES-1; a++)
      for (int b = a+1; b < NUM_FRAMES; b++)
        if (temp[a] > temp[b]) { double t=temp[a]; temp[a]=temp[b]; temp[b]=t; }

    // Median value
    if (NUM_FRAMES % 2 == 0)
      median[i] = (temp[NUM_FRAMES/2 - 1] + temp[NUM_FRAMES/2]) / 2.0;
    else
      median[i] = temp[NUM_FRAMES/2];
  }

  // --- 3. Print magnitudes (raw) ---
  for (int i = 0; i < SAMPLES/2; i++) {
    double freq = i * ((double)SAMPLING_FREQUENCY / (double)SAMPLES);
    if (freq >= 50 && freq <= 1000) {
      Serial.print(freq, 2);
      Serial.print(" Hz: ");
      Serial.println(median[i], 2); // raw magnitude
    }
  }

  Serial.println("---\n");
}