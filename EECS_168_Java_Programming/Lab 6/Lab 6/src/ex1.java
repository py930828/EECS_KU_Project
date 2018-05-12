    import java.util.Scanner;
public class ex1 {

	public static void main(String[] args) {
		Scanner myScan=new Scanner(System.in);
		int x=0;
		int sum=0;
		int average=0;
		int max=0;
		int min=0;
		System.out.print("Input an array size: ");
		x=myScan.nextInt();
		do
		{	
			if(x<0)
		    {
			System.out.println("your value has to be greater than zero");
			System.out.println("Input an array size");
			x=myScan.nextInt();
		    }
		}while(x<0);
		System.out.println("Now please enter "+ x +" numbers");
		int [] numArray=new int[x];
		for( int i=0; i<x; i++)
		{
			System.out.print("Input a number into your array: ");
			numArray [i]=myScan.nextInt();
		}
		System.out.println("Here are all the number in your array");
		for(int i=0;i<x;i++)
		{
			System.out.println(numArray [i]);
		}
		for(int i=0;i<x;i++)
		{
			sum=sum+numArray[i];
		}
		average=sum/x;
		for(int i=1;i<x;i++) 
		{
			max=numArray[0];
			if(max<numArray[i])
				{
					max=numArray[i];
				}
		}
		for(int i=1;i<x;i++)
		{
			min=numArray[0];
			if(min>numArray[i])
			{
				min=numArray[i];
			}
		}
		String N;
		N=("The sum of all the value is: "+sum+"\n"+"The average of all the values is: "+average+"\n"+"The largest value is :"+max+"\n"+"The smallest value is: "+min);
		System.out.println(N);
	}
}
