import java.util.Scanner;
public class MethodPractice {

	public static void main(String[] args) {
		int x=0;
		int y=0;
		System.out.println("Input two numbers:");
		Scanner myScan=new Scanner(System.in);
		x=myScan.nextInt();
		y=myScan.nextInt();
		System.out.println("The max of 34 and 92 is:"+max(x,y));
		System.out.print("Input a radius:");
		int r=myScan.nextInt();
		System.out.print("The area of a sphere with this radius is "+area(r));
		System.out.println("Input a string:");
		Scanner myScanner=new Scanner(System.in);
		String str=myScanner.nextLine();
		System.out.print("How many times do you want to print it?: ");
		x=myScan.nextInt();
		printWord(str,x);
}
	public static int max(int x,int y)
	{
		int max=0;
		if (x>y)
			{max=x;}
		else
			{max=y;}
		return(max);
	}
	public static double area(int r)
	{
			double area=0;
			area=3.14159*r*r;
			return(area);
	}
	public static void printWord(String str,int x)
	{
		for(int i=1;i<=x;i++)
		{
			System.out.println(str);
		}
	}
}
