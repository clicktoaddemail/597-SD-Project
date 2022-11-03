import pandas as pd

def demodulate(deviceAddress, freq, sampleRate, bufferSize, bitTime, windowSize):
    enabled = False
    ctx = setupContext(deviceAddress)
    rxbuf = setupRxBuf(ctx, freq, sampleRate, bufferSize)
    samples = []
    while True:
        rxbuf.refill()
        buffer = rxbuf.read()
        windows = splitToWindows(buffer, windowSize)
        for window in windows:
            spectrum = welch(window)
            sampleValue = spectrum[0]
            sample = [getCurrentTime(), sampleValue]
            samples.append(sample)
        if enabled == False:
            thresh, enabled

#def detectEnable(samples, bitTime):
    
