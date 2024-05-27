#define STOELSE 1000

//low precision floating pt type
typedef struct myfloat
{
        signed char mantissa;
        signed char exponent;
} myfloat_type;


void doub2mydouble(double arg, myfloat_type *res)
{
  int exponent;
  signed char xxp = 0;
  double temp;
  
  exponent = ceil(log(abs(arg)) / log(2)); //base 2 logarithm
  temp = arg * pow(2, 7 - exponent);
  if (abs(temp) == 128)
  {
    temp = temp / 2;
    xxp = 1;
  }
  res->mantissa = (signed char)temp;
  res->exponent = xxp + exponent - 7;
}


void mydoub2double2(double *arg, myfloat_type *res)
{ 
  unsigned long *arg_int_pointer = ( unsigned long * )arg;
  *arg_int_pointer = 0;
  if (res->mantissa < 0)
    *arg_int_pointer = (unsigned long)1 << 31;
  //*arg_int_pointer = *arg_int_pointer | (unsigned long)((unsigned char)(abs(res->exponent) + 127)) << 23;
  //*arg_int_pointer = *arg_int_pointer | (unsigned long)((unsigned char)res->mantissa) << 15 ;
  *arg_int_pointer |= ((unsigned long)(abs(res->exponent) + 127) & 0xFF) << 23;
  *arg_int_pointer |= ((unsigned long)(abs(res->mantissa)) & 0x7FFFFF) << 0;
}


void mydoub2double(double *arg, myfloat_type *res)
{
  *arg = pow(2, res->exponent)*res->mantissa;
}

void print_bit(double arg)
{
  for(unsigned long i = 0; i < 32; i++)
      Serial.print((*((unsigned long *)(&arg)) & i << i) > 0 );
}


void mult_float(myfloat_type *arg1, myfloat_type *arg2, myfloat_type *result)
{
  int temp;
  unsigned char sign;
  
  if (arg1->mantissa == 0 || arg2->mantissa == 0) //if 1 argument is 0
  {
    result->mantissa = 0;
    result->exponent = 1;
    return;
  }

  sign = 0x80 & ((unsigned char)arg1-> mantissa ^ (unsigned char)arg2-> mantissa); //find sign of result with xor operation

  char i = 0;
  temp = (int)(arg1-> mantissa) * (int)(arg2-> mantissa);

  temp = temp & 0x7f00; //take away sign from product

  while (abs(temp) > 127)
  {
    i++;
    temp = temp >> 1;
  }

  result->mantissa = (unsigned char) temp;
  result->mantissa = result->mantissa | sign; //add recorded sign
  result->exponent = arg1->exponent + arg2->exponent + i;

}

double da[STOELSE];
//double da2[STOELSE];

//double mda2da[STOELSE];
myfloat mda[STOELSE];
//myfloat mda2[STOELSE];

void setup()
{
	Serial.begin(115200);
	for(int i = 0; i < STOELSE; i++)
	{
		da[i] = ((double)rand() / (double)RAND_MAX)*0.2+0.9;
		doub2mydouble(da[i], mda+i);
    //da2[i] = da[i]*da[i];
    //mult_float(mda+i,mda+i, mda2+i);
    //mydoub2double(mda2da+i, mda2+i);
	}
}

void loop()
{
  
    unsigned long m_mid_0 = millis();
	  for(int i = 0; i < STOELSE; i++) 
      da[i] *= da[i];
    unsigned long m_mid_1 = millis();
    for(int i = 0; i < STOELSE; i++) 
      mult_float(mda+i,mda+i, mda+i);
    unsigned long m_mid_2 = millis();
    Serial.print("da[i] *= da[i] tid:");
    Serial.println(m_mid_1-m_mid_0);
    Serial.print("mult_float(mda+i,mda+i, mda2+i) tid:");
    Serial.println(m_mid_2-m_mid_1);
    /*
    Serial.print("gammel double:");
    Serial.print(da[i]);
    Serial.print("\t bin:");
    print_bit(da[i]);
    Serial.print("\tny double:");
    Serial.print(da2[i]);
    Serial.print("\t bin:");
    print_bit(da2[i]);
    Serial.print("\tny l:");
    Serial.print(mda2da[i]);
		Serial.print("  \tmantissa:");
		Serial.print((unsigned char)mda[i].mantissa);
		Serial.print("\texponent:");
		Serial.println((unsigned char)mda[i].exponent);
    Serial.print("error double:");
    Serial.println(da2[i]-mda2da[i]);
    */
  Serial.println("--------------------------------------------\n");
  delay(5000);
}
