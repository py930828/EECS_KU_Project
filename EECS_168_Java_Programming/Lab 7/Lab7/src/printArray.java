import java.util.Scanner;
public class printArray {

	public static void main(String[] args) {
		int x=0;
		double y=0;
		int z=0;
		Scanner myScan=new Scanner(System.in);
		System.out.print("Input an array size: ");
		x=myScan.nextInt();
		double [] numArray=new double [x];
		System.out.println("");
		System.out.println("Now please enter "+x+" numbers");
		for(int i=0;i<x;i++)
			{
				System.out.print("Input a number into your array :");
				numArray [i]=(y=myScan.nextDouble());
					while(y<0)
						{
							System.out.println("Your value has to greater than zero");
							System.out.println("Input a number into your array :");
							numArray [i]=(y=myScan.nextDouble());
						}
			}
		System.out.println("Here are all the number in your array: ");
		for(int i=0;i<x;i++)
		{
			System.out.print(numArray [i]+", ");
		}
		System.out.println("");
		System.out.print("Input a new size: ");
		z=myScan.nextInt();
		if(z<x)
		{
			do
				{
					System.out.println("Your new size should be greater than the old one");
					System.out.print("Input a new size: ");
					z=myScan.nextInt();
				}while(z<x);
			
		}
		System.out.println("You need to add "+(z-x)+" values");
		double [] newArray;
		newArray=arrayResize(numArray, z);
		System.out.println("Here are all the numbers in your new array:");
		for(int i=0;i<z;i++)
		{
			System.out.print(newArray[i]+", ");
		}
	}
		public static double[] arrayResize(double[] oldArray, int newSize) { 
			Scanner myScan= new Scanner(System.in);
			double[] arrayResize1=new double[newSize];
			int Size=oldArray.length;
			for(int i=0;i<Size;i++)
			{
				arrayResize1 [i]=oldArray [i];
			}
			for(int i=Size;i<newSize;i++)
			{
				System.out.print("Input a number to add to your array: ");
				arrayResize1 [i]=myScan.nextDouble();
			}
			return arrayResize1;
		}
}
