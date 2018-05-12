import java.util.Scanner;
public class SumOfDigits {

	public static void main(String[] args) {
		System.out.println("Please enter a No: ");
		Scanner myScan=new Scanner(System.in);
		int x=myScan.nextInt();
		do
		{
			System.out.println("The sum of the digits is: "+sum(x));
			System.out.println("want to try again?(y=1/n=0");
			x=myScan.nextInt();
			System.out.println("Please enter a No: ");
			x=myScan.nextInt();
			System.out.print(sum(x));
		}while(x==1);

	}
	public static int sum(int x)
		{
		int s=0;
		int sum=0;
		int y=x%10;
			do
			{
				x=x/10;
				sum=sum+y;
			}
			while(x>=10);
			return(sum);
}
}
