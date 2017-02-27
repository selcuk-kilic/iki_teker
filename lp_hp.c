#if LOW_PASS 
{
    float RC = 1.0/(CUTOFF*2*3.14);
    float dt = 1.0/SAMPLE_RATE;
    float alpha = dt/(RC+dt);
    float output[numSamples];
    output[0] = input[0];
    for(i=1; i<numSamples; i++){
        output[i] = output[i-1] + (alpha*(input[i] - output[i-1]));
    }
}
#endif
#if HIGH_PASS
{
    float RC = 1.0/(CUTOFF*2*3.14);
    float dt = 1.0/SAMPLE_RATE;
    float alpha = RC/(RC + dt);
    float output[numSamples];
    output[0] = input[0];
    for (i = 1; i<numSamples; i++){
        output[i] = alpha * (output[i-1] + input[i] - input[i-1]);
    }
}
#endif