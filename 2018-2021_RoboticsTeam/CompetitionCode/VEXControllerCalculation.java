public class VEXControllerCalculation
{
    public static void main(String [] args)
	{
		// i2 left side of drivetrain, j2 right side of drivetrain
		// joystick moves around circumference of upper semi-circle from x-axis is -127 to +127, which is "i". "j" is y-value of circle formula
        for(int i = -127; i <= 127; i++)
        {
			//i^2+j^2=127
			double j = Math.sqrt(16129-(i*i));
			
			double i1 = (double)i/127.0;
			double j1 = (double)j/127.0;
			
			double i2 = ((int)(i1*i1*i1*10000))/100.0;
			double j2 = ((int)(j1*j1*j1*10000))/100.0;
			
			double sum = ((int)((i2+j2)*100))/100.0;
			double diff = ((int)((j2-i2)*100))/100.0;

			System.out.println(i+ "\t" + i2 + "\t" + j2 + "\t" + sum + "\t" + diff);
        }
    }
}