/*
  Low level precision floating point lib
  Author: Henrik Schiøler

*/

//low precision floating pt type
typedef struct myfloat
{
        signed char mantissa;
        signed char exponent;
} myfloat_type;


//convert from double to low precision type
void doub2mydouble(double arg, myfloat_type *res)
{
   int exponent;
   double temp;

   exponent = ceil(log(abs(arg))/log(2)); //base 2 logarithm
   temp=arg*pow(2,7-exponent);
   res->mantissa = (signed char)temp;
   res->exponent = exponent-7;
}

//convert from low precision type to double
double myfloat2double(myfloat_type *arg1)
{
  double res = (double)(arg1->mantissa) * pow(2,arg1->exponent);
   return res;
}

//multiply to low precision types
void mult_float(myfloat_type *arg1,myfloat_type *arg2,myfloat_type *result)
{
  int temp;
  unsigned char sign;
  
  sign=0x80 & ((unsigned char)arg1-> mantissa ^ (unsigned char)arg2-> mantissa); //find sign of result 
  
  char i=0;
   temp = (int)(arg1-> mantissa) * (int)(arg2-> mantissa);
   
   temp = temp & 0x7f00; //take away sign from product
  
   while(abs(temp)>128)
   {
      i++;
      temp=temp>>1;
   }
   
   result->mantissa = (unsigned char) temp;
   
   result->mantissa = result->mantissa | sign; //add recorded sign
   
   result->exponent = arg1->exponent + arg2->exponent + i;
   
}


void setup() { 
  Serial.begin(9600);

    double da[100];
    myfloat_type mda[100];
    myfloat_type mda2[100];
    double da2[100];
    double mean_relative_error = 0.0;
    double mean_relative_error_squared = 0.0;

    unsigned long start_time, end_time;
    double execution_time_multiply = 0.0;
    double execution_time_convert = 0.0;
    myfloat_type f1;

    // Initialize random seed
    randomSeed(analogRead(0));

    // Generate random array 'da' of doubles uniformly distributed in [5,10]
    for (int i = 0; i < 100; i++)
    {  
        da[i] = random(5,10); // Random number between 5 and 10 
       
    }
    
    // Convert 'da' into 'mda'
    for (int i = 0; i < 100; i++)
    {
        doub2mydouble(da[i], &mda[i]);
    } 

    // Compute mean relative error between da and mda
    for (int i = 0; i < 100; i++)
    {
        mean_relative_error += abs(da[i] - myfloat2double(&mda[i])) / da[i];
    }
    mean_relative_error /= 100;

    // Compute da2=da^2
    for (int i = 0; i < 100; i++)
    {
        da2[i] = da[i] * da[i];
    }

    // Compute mda2=mda^2
    for (int i = 0; i < 100; i++)
    {
        mult_float(&mda[i], &mda[i], &mda2[i]);
    }

    // Compute the mean relative error between da2 and mda2
    for (int i = 0; i < 100; i++)
    {
        mean_relative_error_squared += abs(da2[i] - myfloat2double(&mda2[i])) / da2[i];
    }
    mean_relative_error_squared /= 100;

    // Measure execution time for multiplication
    start_time = micros();
    for (int i = 0; i < 100; i++)
    {
        f1 = mda[i];
        mult_float(&f1, &mda[i], &f1);
    }
    end_time = micros();
    execution_time_multiply = (double)(end_time - start_time) / 100.0; // Average execution time per multiplication

    // Measure execution time for conversion
    start_time = micros();
    for (int i = 0; i < 100; i++)
    {
        f1 = mda[i];
    }
    end_time = micros();
    execution_time_convert = (double)(end_time - start_time) / 100.0; // Average execution time per conversion
    
    // Compute relative difference between results from multiplication and conversion
    double relative_difference = abs(execution_time_multiply - execution_time_convert) / execution_time_convert;


    Serial.println("Mean Relative Error between da and mda:");
    Serial.println(mean_relative_error);
    Serial.println("Mean Relative Error between da2 and mda2:");
    Serial.println(mean_relative_error_squared);
    Serial.println("Execution time for multiplication");
    Serial.println(execution_time_multiply);
    Serial.println("Execution time for conversion");
    Serial.println(execution_time_convert);
    Serial.println("Relative Difference between Multiplication and Conversion:");
    Serial.println(relative_difference); 
    
}
   


void loop() {

  
}
  
