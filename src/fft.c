#include "../include/fft.h"

const int fpga_sin90[1023] = {
    0,6,13,19,25,31,38,44,50,57,63,69,75,82,88,94,100,107,
    113,119,126,132,138,144,151,157,163,170,176,182,188,195,
    201,207,213,220,226,232,239,245,251,257,264,270,276,282,
    289,295,301,308,314,320,326,333,339,345,351,358,364,370,
    376,383,389,395,401,408,414,420,426,433,439,445,451,458,
    464,470,476,483,489,495,501,508,514,520,526,532,539,545,
    551,557,564,570,576,582,588,595,601,607,613,619,626,632,
    638,644,651,657,663,669,675,682,688,694,700,706,712,719,
    725,731,737,743,750,756,762,768,774,780,787,793,799,805,
    811,817,824,830,836,842,848,854,860,867,873,879,885,891,
    897,903,909,916,922,928,934,940,946,952,958,965,971,977,
    983,989,995,1001,1007,1013,1019,1025,1032,1038,1044,1050,
    1056,1062,1068,1074,1080,1086,1092,1098,1104,1110,1116,
    1122,1128,1135,1141,1147,1153,1159,1165,1171,1177,1183,
    1189,1195,1201,1207,1213,1219,1225,1231,1237,1243,1249,
    1255,1261,1267,1273,1279,1285,1290,1296,1302,1308,1314,
    1320,1326,1332,1338,1344,1350,1356,1362,1368,1374,1380,
    1385,1391,1397,1403,1409,1415,1421,1427,1433,1439,1444,
    1450,1456,1462,1468,1474,1480,1485,1491,1497,1503,1509,
    1515,1521,1526,1532,1538,1544,1550,1555,1561,1567,1573,
    1579,1584,1590,1596,1602,1608,1613,1619,1625,1631,1636,
    1642,1648,1654,1659,1665,1671,1677,1682,1688,1694,1700,
    1705,1711,1717,1722,1728,1734,1739,1745,1751,1757,1762,
    1768,1774,1779,1785,1790,1796,1802,1807,1813,1819,1824,
    1830,1836,1841,1847,1852,1858,1864,1869,1875,1880,1886,
    1891,1897,1903,1908,1914,1919,1925,1930,1936,1941,1947,
    1952,1958,1964,1969,1975,1980,1986,1991,1997,2002,2007,
    2013,2018,2024,2029,2035,2040,2046,2051,2057,2062,2067,
    2073,2078,2084,2089,2094,2100,2105,2111,2116,2121,2127,
    2132,2137,2143,2148,2154,2159,2164,2170,2175,2180,2186,
    2191,2196,2201,2207,2212,2217,2223,2228,2233,2238,2244,
    2249,2254,2259,2265,2270,2275,2280,2285,2291,2296,2301,
    2306,2311,2317,2322,2327,2332,2337,2343,2348,2353,2358,
    2363,2368,2373,2378,2384,2389,2394,2399,2404,2409,2414,
    2419,2424,2429,2434,2439,2444,2449,2454,2460,2465,2470,
    2475,2480,2485,2490,2495,2500,2504,2509,2514,2519,2524,
    2529,2534,2539,2544,2549,2554,2559,2564,2569,2573,2578,
    2583,2588,2593,2598,2603,2608,2612,2617,2622,2627,2632,
    2636,2641,2646,2651,2656,2660,2665,2670,2675,2679,2684,
    2689,2694,2698,2703,2708,2713,2717,2722,2727,2731,2736,
    2741,2745,2750,2755,2759,2764,2769,2773,2778,2782,2787,
    2792,2796,2801,2805,2810,2815,2819,2824,2828,2833,2837,
    2842,2846,2851,2855,2860,2864,2869,2873,2878,2882,2887,
    2891,2896,2900,2904,2909,2913,2918,2922,2927,2931,2935,
    2940,2944,2948,2953,2957,2961,2966,2970,2974,2979,2983,
    2987,2992,2996,3000,3004,3009,3013,3017,3022,3026,3030,
    3034,3038,3043,3047,3051,3055,3059,3064,3068,3072,3076,
    3080,3084,3088,3093,3097,3101,3105,3109,3113,3117,3121,
    3125,3129,3133,3137,3141,3145,3149,3153,3157,3161,3165,
    3169,3173,3177,3181,3185,3189,3193,3197,3201,3205,3209,
    3213,3217,3221,3224,3228,3232,3236,3240,3244,3248,3251,
    3255,3259,3263,3267,3270,3274,3278,3282,3285,3289,3293,
    3297,3300,3304,3308,3311,3315,3319,3322,3326,3330,3333,
    3337,3341,3344,3348,3352,3355,3359,3362,3366,3370,3373,
    3377,3380,3384,3387,3391,3394,3398,3401,3405,3408,3412,
    3415,3419,3422,3426,3429,3433,3436,3439,3443,3446,3450,
    3453,3456,3460,3463,3466,3470,3473,3476,3480,3483,3486,
    3490,3493,3496,3499,3503,3506,3509,3512,3516,3519,3522,
    3525,3528,3532,3535,3538,3541,3544,3547,3551,3554,3557,
    3560,3563,3566,3569,3572,3575,3578,3581,3584,3588,3591,
    3594,3597,3600,3603,3606,3609,3611,3614,3617,3620,3623,
    3626,3629,3632,3635,3638,3641,3644,3646,3649,3652,3655,
    3658,3661,3663,3666,3669,3672,3675,3677,3680,3683,3686,
    3688,3691,3694,3696,3699,3702,3705,3707,3710,3713,3715,
    3718,3720,3723,3726,3728,3731,3733,3736,3739,3741,3744,
    3746,3749,3751,3754,3756,3759,3761,3764,3766,3769,3771,
    3774,3776,3778,3781,3783,3786,3788,3790,3793,3795,3798,
    3800,3802,3805,3807,3809,3811,3814,3816,3818,3821,3823,
    3825,3827,3830,3832,3834,3836,3838,3841,3843,3845,3847,
    3849,3851,3854,3856,3858,3860,3862,3864,3866,3868,3870,
    3872,3874,3876,3878,3880,3882,3884,3886,3888,3890,3892,
    3894,3896,3898,3900,3902,3904,3906,3908,3909,3911,3913,
    3915,3917,3919,3920,3922,3924,3926,3928,3929,3931,3933,
    3935,3936,3938,3940,3942,3943,3945,3947,3948,3950,3952,
    3953,3955,3957,3958,3960,3961,3963,3965,3966,3968,3969,
    3971,3972,3974,3975,3977,3978,3980,3981,3983,3984,3986,
    3987,3989,3990,3991,3993,3994,3996,3997,3998,4000,4001,
    4002,4004,4005,4006,4008,4009,4010,4011,4013,4014,4015,
    4016,4018,4019,4020,4021,4022,4023,4025,4026,4027,4028,
    4029,4030,4031,4033,4034,4035,4036,4037,4038,4039,4040,
    4041,4042,4043,4044,4045,4046,4047,4048,4049,4050,4051,
    4052,4053,4053,4054,4055,4056,4057,4058,4059,4059,4060,
    4061,4062,4063,4063,4064,4065,4066,4066,4067,4068,4069,
    4069,4070,4071,4071,4072,4073,4073,4074,4075,4075,4076,
    4076,4077,4078,4078,4079,4079,4080,4080,4081,4081,4082,
    4082,4083,4083,4084,4084,4085,4085,4086,4086,4087,4087,
    4087,4088,4088,4088,4089,4089,4089,4090,4090,4090,4091,
    4091,4091,4091,4092,4092,4092,4092,4093,4093,4093,4093,
    4093,4094,4094,4094,4094,4094,4094,4094,4095,4095,4095,
    4095,4095,4095,4095,4095,4095
};

void fpga_FFT(int *inputR,int *inputI,int N,int type);
int  fpga_cos(int angle,int inverse);
int  fpga_sin(int angle,int inverse);
int  fpga_log2(int n,int v);
int  fpga_pwd2(int n,int v);
int  fpga_valid_FFT_size(int N);
void fpga_rearrange_input(int *InputR, int *InputI, int *BufferR, int *BufferI, int *RevBits, int N);
void fpga_fill_Wn(int *TwiddleR, int *TwiddleI, int N, int type);
int  fpga_required_FFT_size(int NumPts);
void fpga_tranform(int *InputR, int *InputI, int *BufferR, int *BufferI, int *TwiddleR, int *TwiddleI, int N);

int fpga_cos(int angle,int inverse)
{
    return fpga_sin(angle + A_90,inverse);
}

int fpga_sin(int angle,int inverse)
{
    angle /= A_360;
    if(angle > A_180)
    {
        return fpga_sin(angle - A_180,(inverse == 1) ? 0 : 1);
    } else {
        if(angle > A_90)
        {
            return fpga_sin(angle - A_90,inverse);
        } else { 
            return fpga_sin90[angle];
        }
    }
}

int fpga_log2(int n,int v)
{
    if(n > 1)
    {
        return fpga_log2(n/2,v + 1);
    } else {
        return v;
    }
}

int fpga_pwd2(int n,int v)
{
    if(n = 0)
    {
        return 1;
    } else {
        if(n = 1)
        {
            return v;
        } else { 
            return fpga_pwd2(n - 1,v * 2);
        }
    }
}

int fpga_valid_FFT_size(int N)
{
    if(N < MINIMUM_FFT_SIZE || N > MAXIMUM_FFT_SIZE || (N & (N - 1) != 0))
    {
        return 0;
    }
    return (fpga_log2(N,0) + 1);
}

void fpga_FFT(int *inputR,int *inputI,int N,int type)
{
    int *WnR, *WnI;
    int *bufferR, *bufferI; // Buffer
    int *revBits;
    int j = 0, OneOverN, log2ofN = fpga_log2(N,0);
    // Verify the FFT size and type
    if(fpga_valid_FFT_size(N) == 0)
    {
        exit(EXIT_FAILURE);
        return;
    }
    { // Allocate memory space
        WnR     = malloc(N/2 * sizeof(int)); WnI     = malloc(N/2 * sizeof(int));
        bufferR = malloc(  N * sizeof(int)); bufferI = malloc(  N * sizeof(int));
        revBits = malloc(  N * sizeof(int));
    }
    if // verify if malloc allocate memory
    (
        bufferI == NULL || bufferR == NULL || 
        WnR     == NULL || WnI     == NULL || 
        revBits == NULL
    )
    {
        printf("FFT Memory allocation Error\n");
        exit(EXIT_FAILURE);
        return;
    }
    fpga_rearrange_input(inputR,inputI,bufferR,bufferI,revBits,N);
    fpga_fill_Wn(WnR,WnI,N,type);
    fpga_tranform(inputR,inputI,bufferR,bufferI,WnR,WnI,N);
    if(log2ofN % 2 == 1)
    {
        for(j = 0;j < N;j++)
        {
            if(type == FORWARD)
            {
                inputR[j] = inputR[j]/N;
                inputI[j] = inputI[j]/N;
            } else {
                inputR[j] = inputR[j];
                inputI[j] = inputI[j];
            }
        } 
    } else {
        for(j = 0;j < N;j++)
        {
            if(type == FORWARD)
            {
                inputR[j] = bufferR[j] / N;
                inputI[j] = bufferI[j] / N;
            } else {
                inputR[j] = bufferR[j] / N;
                inputI[j] = bufferI[j] / N;
            }
        }
    }
    free(bufferR); free(bufferI);
    free(WnR);     free(WnI);
    free(revBits);
}

/* This puts the input arrays in bit reversed order.
// The while loop generates an array of bit reversed numbers for butterfly. e.g.
// N=8: 0,4,2,6,1,5,3,7  N=16: 0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15 */
void fpga_rearrange_input(int *InputR, int *InputI, int *BufferR, int *BufferI, int *RevBits, int N)
{
    int j, k, J, K;
    J = N/2;
    K = 1;
    RevBits[0] = 0;
    while(J >= 1)
    {
        for(k=0; k<K; k++)
        {
            RevBits[k+K] = RevBits[k] + J;
        }
        K *= 2;
        J /= 2;
    }
    // Move the rearranged input values to Buffer.
    // Take note of the pointer swaps at the top of the fpga_tranform algorithm.
    for(j=0; j<N; j++)
    {
        BufferR[j] = InputR[ RevBits[j] ];
        BufferI[j] = InputI[ RevBits[j] ];
    }
}

/*
The Pentium takes a surprifpga_sing amount of time to calculate the fpga_sine and fpga_cofpga_sine.
You may want to make the twiddle arrays static if doing repeated FFTs of the same size.
This uses 4 fold symmetry to calculate the twiddle factors. As a result, this function
requires a minimum FFT size of 8.
*/
void fpga_fill_Wn(int *TwiddleR, int *TwiddleI, int N, int type)
{
    int j;
    int Theta, TwoPiOverN;
    if(type == FORWARD)
    {
        TwiddleR[0]     =  A_360;
        TwiddleI[0]     =  0;
        TwiddleR[N/4]   =  0;
        TwiddleI[N/4]   = -A_360;
        TwiddleR[N/8]   =  SQRT_2;
        TwiddleI[N/8]   = -SQRT_2;
        TwiddleR[3*N/8] = -SQRT_2;
        TwiddleI[3*N/8] = -SQRT_2;
        for(j = 1;j < N/8; j++)
        {
            Theta = -(j * A_360) / N;
            TwiddleR[j] = fpga_cos(Theta,0);
            TwiddleI[j] = fpga_sin(Theta,0);
            TwiddleR[N/4-j] = -TwiddleI[j];
            TwiddleI[N/4-j] = -TwiddleR[j];
            TwiddleR[N/4+j] = TwiddleI[j];
            TwiddleI[N/4+j] = -TwiddleR[j];
            TwiddleR[N/2-j] = -TwiddleR[j];
            TwiddleI[N/2-j] = TwiddleI[j];
        }
    }
    else
    {
        TwiddleR[0]     =  A_360;
        TwiddleI[0]     =  0;
        TwiddleR[N/4]   =  0;
        TwiddleI[N/4]   = -A_360;
        TwiddleR[N/8]   =  SQRT_2;
        TwiddleI[N/8]   = -SQRT_2;
        TwiddleR[3*N/8] = -SQRT_2;
        TwiddleI[3*N/8] = -SQRT_2;
        for(j = 1;j < N/8; j++)
        {
            Theta           = j * TwoPiOverN;
            TwiddleR[j]     = fpga_cos(Theta,0);
            TwiddleI[j]     = fpga_sin(Theta,0);
            TwiddleR[N/4-j] = TwiddleI[j];
            TwiddleI[N/4-j] = TwiddleR[j];
            TwiddleR[N/4+j] = -TwiddleI[j];
            TwiddleI[N/4+j] = TwiddleR[j];
            TwiddleR[N/2-j] = -TwiddleR[j];
            TwiddleI[N/2-j] = TwiddleI[j];
        }
    }
}

//---------------------------------------------------------------------------
// This calculates the required FFT size for a given number of points.
int fpga_required_FFT_size(int NumPts)
{
    int N = MINIMUM_FFT_SIZE;
    while(N < NumPts && N < MAXIMUM_FFT_SIZE)
    {
        N *= 2;
    }
    return N;
}

// The Fourier Transform.
void fpga_tranform(int *InputR, int *InputI, int *BufferR, int *BufferI, int *TwiddleR, int *TwiddleI, int N)
{
    int j, k, J, K, I, T;
    int *TempPointer;
    int TempR, TempI;
    J = N/2;     // J increments down to 1
    K = 1;       // K increments up to N/2
    while(J > 0) // Loops Log2(N) times.
    {
        // Swap pointers, instead doing this: for(j=0; j<N; j++) Input[j] = Buffer[j];
        // We start with a swap because of the swap in fpga_rearrange_input.
        TempPointer = InputR;
        InputR = BufferR;
        BufferR = TempPointer;
        TempPointer = InputI;
        InputI = BufferI;
        BufferI = TempPointer;
        I = 0;
        for(j=0; j<J; j++)
        {
            T = 0;
            for(k=0; k<K; k++) // Loops N/2 times for every value of J and K
            {
                TempR = (InputR[K+I] * TwiddleR[T] - InputI[K+I] * TwiddleI[T])/A_360;
                TempI = (InputR[K+I] * TwiddleI[T] + InputI[K+I] * TwiddleR[T])/A_360;
                BufferR[I]   = InputR[I] + TempR;
                BufferI[I]   = InputI[I] + TempI;
                BufferR[I+K] = InputR[I] - TempR;
                BufferI[I+K] = InputI[I] - TempI;
                I++;
                T += J;
            }
            I += K;
        }
        K *= 2;
        J /= 2;
    }
}