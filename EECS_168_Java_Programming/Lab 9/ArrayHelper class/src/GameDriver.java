import java.util.Scanner;
public class GameDriver {

	public static void main(String[] args) {
		ArrayHelper game=new ArrayHelper();
		Scanner myScan=new Scanner(System.in);
		System.out.print("How many rows?: ");
		int x=myScan.nextInt();
		System.out.print("How many columns?: ");
		int y=myScan.nextInt();
		int[][] Array;
		Array=new int[x][y];
		for(int i=0;i<x;i++)
		{
			for(int j=0;j<y;j++)
			{
				System.out.print("Enter a value for position ("+i+","+j+"): ");
				int z=myScan.nextInt();
				Array[i][j]=z;
			}
		}
		game.print2DArray(Array);
		for(int i=0;i<Array.length;i++)
		{
			int[] newArray;
			newArray=new int[(Array[i].length)];
			for(int j=0;j<Array[i].length;j++)
			{
				newArray[j]=Array[i][j];
			}
			System.out.println("row "+i+" sum= "+game.arraySum(newArray)+","+" avg = "+game.arrayAvg(newArray));
		}
		System.out.println("The largest value in the array is = "+game.arrayMax2D(Array));
		System.out.println("The sum for the entire array is = "+game.arraySum2D(Array));
		System.out.println("The average for the entire array is = "+game.arrayAvg2D(Array));
		
			
		
		

	}

}
